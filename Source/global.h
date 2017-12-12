#ifndef GLOBAL_H
#define GLOBAL_H
#include "WIFI_Clock.h"

ESP8266WebServer server(80);							// Веб сервер
WiFiUDP UDPNTPClient;											// NTP Client
unsigned long Period = 0;
strConfig config;
/**************************************************************************************************************************************************************************/
//  Auxiliar function to handle EEPROM
void EEPROMWritelong(int address, long value){
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}
/**************************************************************************************************************************************************************************/
long EEPROMReadlong(long address){
  //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  //Return the recomposed long by using bitshift.
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}
/**************************************************************************************************************************************************************************/
// Check the Values is between 0-255
boolean checkRange(String Value){
  if (Value.toInt() < 0 || Value.toInt() > 255) { return false;  } else  { return true;  }
}
/**************************************************************************************************************************************************************************/
void WriteStringToEEPROM(int beginaddress, String string){
  char  charBuf[string.length() + 1];
  string.toCharArray(charBuf, string.length() + 1);
  for (int t =  0; t < sizeof(charBuf); t++)
  {
    EEPROM.write(beginaddress + t, charBuf[t]);
  }
}
/**************************************************************************************************************************************************************************/
String  ReadStringFromEEPROM(int beginaddress){
  volatile byte counter = 0;
  char rChar;
  String retString = "";
  while (1)
  {
    rChar = EEPROM.read(beginaddress + counter);
    if (rChar == 0) break;
    if (counter > 31) break;
    counter++;
    retString.concat(rChar);
  }
  return retString;
}
/**************************************************************************************************************************************************************************/
/***** CONFIGURATION HANDLING *****/
void ConfigureWifi(){
  Serial.println("Configuring Wifi");
  WiFi.begin (config.ssid.c_str(), config.password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
  }
  if (!config.dhcp)
  {
    WiFi.config(IPAddress(config.IP[0], config.IP[1], config.IP[2], config.IP[3] ),  IPAddress(config.Gateway[0], config.Gateway[1], config.Gateway[2], config.Gateway[3] ) , IPAddress(config.Netmask[0], config.Netmask[1], config.Netmask[2], config.Netmask[3] ) , IPAddress(config.DNS[0], config.DNS[1], config.DNS[2], config.DNS[3] ));
  }
}
/**************************************************************************************************************************************************************************/
void WriteConfig(){
  Serial.println("Writing Config");
  EEPROM.write(0, 'C');
  EEPROM.write(1, 'F');
  EEPROM.write(2, 'G');

  EEPROM.write(16, config.dhcp);
  EEPROM.write(17, config.isDayLightSaving);

  EEPROMWritelong(18, config.Update_Time_Via_NTP_Every); // 4 Byte
  EEPROMWritelong(22, config.timeZone); // 4 Byte

  EEPROM.write(32, config.IP[0]);
  EEPROM.write(33, config.IP[1]);
  EEPROM.write(34, config.IP[2]);
  EEPROM.write(35, config.IP[3]);

  EEPROM.write(36, config.Netmask[0]);
  EEPROM.write(37, config.Netmask[1]);
  EEPROM.write(38, config.Netmask[2]);
  EEPROM.write(39, config.Netmask[3]);

  EEPROM.write(40, config.Gateway[0]);
  EEPROM.write(41, config.Gateway[1]);
  EEPROM.write(42, config.Gateway[2]);
  EEPROM.write(43, config.Gateway[3]);
  EEPROMWritelong(44, config.Update_Weather_Every); // 4 Byte
  
  WriteStringToEEPROM(64, config.ssid);
  WriteStringToEEPROM(96, config.password);
  WriteStringToEEPROM(128, config.ntpServerName);
  WriteStringToEEPROM(160, config.DeviceName);
  WriteStringToEEPROM(192, config.email);

  EEPROM.write(230, config.DNS[0]);
  EEPROM.write(231, config.DNS[1]);
  EEPROM.write(232, config.DNS[2]);
  EEPROM.write(233, config.DNS[3]);
  EEPROM.write(234, config.volume); 
  EEPROM.write(235, config.intens1);
  EEPROM.write(236, config.intens2);
  EEPROM.write(237, config.intens3);

  int max_num=1;
  if (myDFPlayer.available()) 
  { int max_num=myDFPlayer.readFileCounts(); 
      for (int i=0; i<8; i++) 
      { if (config.alarm_param[i][3] > max_num) config.alarm_param[i][3]=max_num; }
  }
 
  for (uint16_t i=0; i<8; i++) {
    for (uint16_t j=0; j<4; j++) {
      EEPROM.write((238 + (i*4) + j), config.alarm_param[i][j]);
    }
  }
  EEPROM.commit();
}
/**************************************************************************************************************************************************************************/
void PrintEEPROM (void)
{Serial.println(F("EEPROM:"));
  Serial.printf("     ");
  for (int i=0;i<32;i++) Serial.printf(" %02d ", i);
  Serial.printf("\n");
  
  for (int i=0; i<16; i++)
    { Serial.printf("%03d: ", i*32);
      for (int j=0;j<32;j++) { Serial.printf("%03d ", EEPROM.read(i*32 + j)); }
      
      Serial.printf("\n");
    }  
}
/**************************************************************************************************************************************************************************/
boolean ReadConfig(){
  Serial.println("Reading Configuration");
  //PrintEEPROM();
  if (EEPROM.read(0) == 'C' && EEPROM.read(1) == 'F'  && EEPROM.read(2) == 'G' )
  {
    Serial.println("Configurarion Found!");
    config.dhcp = 	EEPROM.read(16);
    config.isDayLightSaving = EEPROM.read(17);
    config.Update_Time_Via_NTP_Every = EEPROMReadlong(18); // 4 Byte
    config.timeZone = EEPROMReadlong(22); // 4 Byte
    config.IP[0] = EEPROM.read(32);
    config.IP[1] = EEPROM.read(33);
    config.IP[2] = EEPROM.read(34);
    config.IP[3] = EEPROM.read(35);
    config.Netmask[0] = EEPROM.read(36);
    config.Netmask[1] = EEPROM.read(37);
    config.Netmask[2] = EEPROM.read(38);
    config.Netmask[3] = EEPROM.read(39);
    config.Gateway[0] = EEPROM.read(40);
    config.Gateway[1] = EEPROM.read(41);
    config.Gateway[2] = EEPROM.read(42);
    config.Gateway[3] = EEPROM.read(43);
    config.Update_Weather_Every=EEPROMReadlong(44);
    config.ssid = ReadStringFromEEPROM(64);
    config.password = ReadStringFromEEPROM(96);
    config.ntpServerName = ReadStringFromEEPROM(128);
    config.DeviceName = ReadStringFromEEPROM(160);
    config.email = ReadStringFromEEPROM(192);
    config.DNS[0] = EEPROM.read(230);
    config.DNS[1] = EEPROM.read(231);
    config.DNS[2] = EEPROM.read(232);
    config.DNS[3] = EEPROM.read(233);
    config.volume = EEPROM.read(234);  
    config.intens1 = EEPROM.read(235);  
    config.intens2 = EEPROM.read(236);  
    config.intens3 = EEPROM.read(237);  

    for (uint16_t i=0; i<8; i++) {
      for (uint16_t j=0; j<4; j++) {
        config.alarm_param[i][j] = EEPROM.read((238 + (i*4) + j));
      }
    }
    CheckAlarmSet();
    return true;
  }
  else
  {
#ifdef DEBUG
    Serial.println("Configurarion NOT FOUND!");
#endif    
    return false;
  }
}
/**************************************************************************************************************************************************************************/
void LoadDefaultConfig (uint8_t Param = CFG_NET)
{
#ifdef DEBUG
    Serial.println("Load default network parameters");
#endif    
    config.ssid = "CLOCK_WiFi";       // SSID of access point
    config.password = "" ;   // password of access point
    config.dhcp = true;
    config.IP[0] = 192; config.IP[1] = 168; config.IP[2] = 1; config.IP[3] = 100;
    config.Netmask[0] = 255; config.Netmask[1] = 255; config.Netmask[2] = 255; config.Netmask[3] = 0;
    config.Gateway[0] = 192; config.Gateway[1] = 168; config.Gateway[2] = 1; config.Gateway[3] = 1;
    config.DNS[0] = 192; config.DNS[1] = 168; config.DNS[2] = 1; config.DNS[3] = 1;
    
    if (Param == CFG_ALL) {
#ifdef DEBUG      
    Serial.println("Load default system parameters");
#endif    
    config.ntpServerName = "0.ru.pool.ntp.org"; // to be adjusted to PT ntp.ist.utl.pt
    config.Update_Time_Via_NTP_Every =  0;
    config.timeZone = 30;
    config.isDayLightSaving = true;
    config.DeviceName = "API ключь";
    config.email = "cityID";
    config.Update_Weather_Every=0;
    for (uint16_t i=0; i<8; i++) {
      for (uint16_t j=0; j<3; j++) {
        config.alarm_param[i][j] = 0;
      }
     }
    for (uint16_t i=0; i < 8; i++) config.alarm_param[i][3] = 1;
    config.volume=15;
    config.intens1=5;
    config.intens2=8;
    config.intens3=13; 
    }
}
/**************************************************************************************************************************************************************************/
void printConfig(){
#ifdef DEBUG
  Serial.println("Printing Config");

  Serial.printf("DHCP:%d\n", config.dhcp);
  Serial.printf("DayLight:%d\n", config.isDayLightSaving);

  Serial.printf("NTP update every %ld sec\n", config.Update_Time_Via_NTP_Every); // 4 Byte
  Serial.printf("Timezone %ld\n", config.timeZone); // 4 Byte

  Serial.printf("IP:%d.%d.%d.%d\n", config.IP[0],config.IP[1],config.IP[2],config.IP[3]);
  Serial.printf("Mask:%d.%d.%d.%d\n", config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3]);
  Serial.printf("Gateway:%d.%d.%d.%d\n", config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3]);
  Serial.printf("DNS:%d.%d.%d.%d\n", config.DNS[0],config.DNS[1],config.DNS[2],config.DNS[3]);
   
  Serial.printf("SSID:%s\n", config.ssid.c_str());
  Serial.printf("ntp ServerName:%s\n", config.ntpServerName.c_str());
  Serial.printf("Device Name:%s\n", config.DeviceName.c_str());
  
  Serial.printf("Email:%s\n", config.email.c_str());
  Serial.printf("Update every %ld minutes\n", config.Update_Weather_Every);
  Serial.printf("Volume: %ld\n", config.volume);
  
  Serial.printf("Brightness (night): %ld\n", config.intens1);
  Serial.printf("Brightness (half-light): %ld\n", config.intens2);
  Serial.printf("Brightness (day): %ld\n", config.intens3);

  for (int i=0; i<8; i++)
  {
    Serial.printf("Alert %d: %d:%d %d %d\n",i,config.alarm_param[i][0],config.alarm_param[i][1],config.alarm_param[i][2],config.alarm_param[i][3]);
  }
#endif  
}
/**************************************************************************************************************************************************************************/
String GetMacAddress(){
  uint8_t mac[6];
  char macStr[18] = {0};
  WiFi.macAddress(mac);
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],  mac[1], mac[2], mac[3], mac[4], mac[5]);
  return  String(macStr);
}
/**************************************************************************************************************************************************************************/
String GetAPMacAddress(){
  uint8_t mac[6];
  char macStr[18] = {0};
  WiFi.softAPmacAddress(mac);
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],  mac[1], mac[2], mac[3], mac[4], mac[5]);
  return  String(macStr);
}
/**************************************************************************************************************************************************************************/
// convert a single hex digit character to its integer value (from https://code.google.com/p/avr-netino/)
unsigned char h2int(char c){
  if (c >= '0' && c <= '9') { return ((unsigned char)c - '0');      }
  if (c >= 'a' && c <= 'f') { return ((unsigned char)c - 'a' + 10); }
  if (c >= 'A' && c <= 'F') { return ((unsigned char)c - 'A' + 10); }
  return (0);
}
/**************************************************************************************************************************************************************************/
String urldecode(String input) // (based on https://code.google.com/p/avr-netino/)
{
  char c;
  String ret = "";
  for (byte t = 0; t < input.length(); t++)
  { c = input[t];
    if (c == '+') c = ' ';
    if (c == '%') {
     t++; c = input[t];
     t++; c = (h2int(c) << 4) | h2int(input[t]);
   }
   ret.concat(c);
  }
 return ret;
}
/**************************************************************************************************************************************************************************/
#endif
