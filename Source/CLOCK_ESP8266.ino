#include "WIFI_Clock.h"

SoftwareSerial mySoftwareSerial(D3, D4, false, 256); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
RtcDS3231<TwoWire> Rtc(Wire);
MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);

volatile bool NeedNowUpdate;
volatile bool NeedCheckAlert;

bool Need_Redraw_UP;
bool Need_Redraw_DOWN;
bool Alert_is_ON=false;

unsigned long AlertTime=0;
unsigned long eventTime=0;
unsigned long NTP_update_period=0;

String weatherKey;
String ipstring;
String Text;

String weatherMain = "";
String weatherDescription = "";
String weatherLocation = "";
String country;
int humidity;
int pressure;
float temp;
String tempz;

float lon;
float lat;

int clouds;
float windSpeed;
int windDeg;

String weatherString;

String date;
String date1;
String currencyRates;

String weatherString1;
String weatherStringz;
String weatherStringz1;
String weatherStringz2;

String cityID;
  
WiFiClient client;

String chipID;


bool CFG_saved = false;
int WIFI_connected = false;

RtcDateTime now;
uint8_t Intens;

byte ZoneDown_Mode;

unsigned long PeriodIntens=0;
unsigned long PeriodWeather=0;

bool ErrorWeather;
bool ErrorNTP;
bool ErrorWiFi;
bool AlarmSet;

char buf_up[10];
char buf_down[256];

/**************************************************************************************************************************************************************************/
void setup() {
  Serial.begin(115200);
  mySoftwareSerial.begin(9600);
  Serial.println(F("Power ON"));
  Wire.begin(4,5);

  ErrorWeather=false;
  ErrorNTP=false;
  ErrorWiFi=false;
  AlarmSet=false;
  
  P.begin(MD_Zones);
  P.setInvert(false);
  P.setFont(fontBG);
  P.setZone(Zone_UP, 0, 3);
  P.setZone(Zone_DOWN, 4, 7);

  Rtc.Begin();
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeClock);
  Rtc.SetSquareWavePinClockFrequency(DS3231SquareWaveClock_1Hz);
    
  if (!Rtc.IsDateTimeValid()) { Serial.println("RTC lost confidence in the DateTime!"); now=RtcDateTime(2017,01,01,00,00,00); Rtc.SetDateTime(now); }
  if (!Rtc.GetIsRunning())    { Serial.println("RTC was not actively running, starting now"); Rtc.SetIsRunning(true); }
  
   //**** Network Config load 
  EEPROM.begin(512); // define an EEPROM space of 512Bytes to store data
  CFG_saved = ReadConfig();

  //  Connect to WiFi acess point or start as Acess point
  if (CFG_saved)  //if no configuration yet saved, load defaults
  {    
      // Connect the ESP8266 to local WIFI network in Station mode
      Serial.println("Booting");
      WiFi.mode(WIFI_STA);
    if (!config.dhcp)
    {
      WiFi.config(IPAddress(config.IP[0], config.IP[1], config.IP[2], config.IP[3] ),  \
                  IPAddress(config.Gateway[0], config.Gateway[1], config.Gateway[2], config.Gateway[3] ) , \
                  IPAddress(config.Netmask[0], config.Netmask[1], config.Netmask[2], config.Netmask[3] ) , \
                  IPAddress(config.DNS[0], config.DNS[1], config.DNS[2], config.DNS[3] ));
      ErrorWiFi=true;            
    }
      WiFi.begin(config.ssid.c_str(), config.password.c_str());

      WIFI_connected = WiFi.waitForConnectResult();
      printConfig();
  
    if(WIFI_connected!= WL_CONNECTED ){
      Serial.println("Connection Failed! activating to AP mode...");
      Serial.print("Wifi ip:");Serial.println(WiFi.localIP());
      Serial.print("Email:");Serial.println(config.email.c_str());
      ErrorWiFi=true;
     }
  }
  else
  {
    LoadDefaultConfig(CFG_ALL);
  }

  if ( (WIFI_connected!= WL_CONNECTED)){
    // USE DEFAULT CONFIG
  #ifdef DEBUG    
    Serial.println("Setting AP mode default parameters");
  #endif    
    LoadDefaultConfig(CFG_NET);    
    WiFi.mode(WIFI_AP);  
    WiFi.softAP(config.ssid.c_str());
    Serial.print("Wifi ip:");Serial.println(WiFi.softAPIP());
    if(P.getZoneStatus(Zone_DOWN)) scrollDefaultConnect(Zone_DOWN);
    ErrorWiFi=true;
   }


   // Start HTTP Server for configuration
    server.on ( "/", []() {
      Serial.println("admin.html");
      server.send_P ( 200, "text/html", PAGE_AdminMainPage);  // const char top of page
    }  );
  
    server.on ( "/favicon.ico",   []() {
      Serial.println("favicon.ico");
      server.send( 200, "text/html", "" );
    }  );
  
    // Network config
    server.on ( "/config.html", send_network_configuration_html );
    server.on ( "/remctrl.html", send_remctrl_html );
  
    // Info Page
    server.on ( "/info.html", []() {
      Serial.println("info.html");
      server.send_P ( 200, "text/html", PAGE_Information );
    }  );
    
    server.on ( "/ntp.html", send_NTP_configuration_html  );
    server.on ( "/general.html", send_general_html  );
    server.on ( "/alert.html", send_alert_html  );
    server.on ( "/system.html", send_system_configuration_html  );
    server.on ( "/style.css", []() {
      Serial.println("style.css");
      server.send_P ( 200, "text/plain", PAGE_Style_css );
    } );
    server.on ( "/microajax.js", []() {
      Serial.println("microajax.js");
      server.send_P ( 200, "text/plain", PAGE_microajax_js );
    } );
    server.on ( "/admin/values", send_network_configuration_values_html );
    server.on ( "/admin/connectionstate", send_connection_state_values_html );
    server.on ( "/admin/infovalues", send_information_values_html );
    server.on ( "/admin/ntpvalues", send_NTP_configuration_values_html );
    server.on ( "/admin/generalvalues", send_general_configuration_values_html);
    server.on ( "/admin/devicename",     send_devicename_value_html);
    server.on ( "/admin/alertvalues",     send_alert_values_html);
    server.on ( "/admin/systemvalues",     send_system_configuration_values_html);
  
    server.onNotFound ( []() {
      Serial.println("Page Not Found");
      server.send ( 400, "text/html", "Page not Found" );
    }  );
    
    server.begin();
    Serial.println( "HTTP server started" );

    // ***********  OTA SETUP
    ArduinoOTA.setHostname(config.DeviceName.c_str());
    ArduinoOTA.onEnd([]() { // do a fancy thing with our board led at end
        ESP.restart();
      });
  
    ArduinoOTA.onError([](ota_error_t error) { 
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
        ESP.restart(); 
      });
  
     /* setup the OTA server */
    ArduinoOTA.begin();
  
    if (config.Update_Time_Via_NTP_Every !=0 ) { UpdateRTC(getNTPtime()); NTP_update_period=millis(); }
    
    UpdateNow();
    Serial.print(F("Now ")); PrintTime (now);
  
    Serial.println("Ready");
    
    //**** Normal Sketch code here...

ipstring = (  String(WiFi.localIP()[0]) +"." +
              String(WiFi.localIP()[1]) + "." +
              String(WiFi.localIP()[2]) + "." +
              String(WiFi.localIP()[3]) );
  
if  (WiFi.status() == WL_CONNECTED) {
  if(P.getZoneStatus(Zone_DOWN)) scrollIP(Zone_DOWN);

  weatherKey = config.DeviceName.c_str();
  cityID = config.email.c_str();
  
  if (config.DeviceName != "API ключь" && config.email != "cityID" && config.Update_Weather_Every != 0) { getWeatherData(); PeriodWeather = millis(); }
  else PeriodWeather=0;
}
   
const byte interruptPin = 12;
pinMode(interruptPin, INPUT);
pinMode(D0, INPUT_PULLDOWN_16);
pinMode(D1, INPUT);
pinMode(D2, INPUT);


Need_Redraw_UP=true;
Need_Redraw_DOWN=true;
NeedCheckAlert=false;
attachInterrupt(digitalPinToInterrupt(interruptPin), RTC_Tick, CHANGE);
delay(50);

if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
#ifdef DEBUG
  Serial.println(F("Unable to begin:"));
  Serial.println(F("1.Please recheck the connection!"));
  Serial.println(F("2.Please insert the SD card!"));
#endif  
}
else
{ myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.volume(config.volume);
  #ifdef DEBUG  
  Serial.print(F("DFPlayer Mini online: ")); Serial.println(myDFPlayer.readState()); //read mp3 state
  //Serial.print(F("DFPlayer Volume: "));  Serial.println(myDFPlayer.readVolume()); //read current volume
  //Serial.print(F("DFPlayer EQ: ")); Serial.println(myDFPlayer.readEQ()); //read EQ setting
  //Serial.print(F("DFPlayer file counts: ")); Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  //Serial.print(F("DFPlayer current file number: "));Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
  //Serial.print(F("DFPlayer file counts in folder: "));Serial.println(myDFPlayer.readFileCountsInFolder(1)); //read fill counts in folder SD:/03
  #endif
}
ZoneDown_Mode=SHOW_DATE;
yield();

}
/**************************************************************************************************************************************************************************/
void DoAlert (bool act, int num)
{ Serial.print(__FUNCTION__);
  Serial.print("ACT: ");  Serial.print(act); Serial.print(" NUM: "); Serial.println(num);   
  Alert_is_ON=act;
  if (Alert_is_ON == true) {
       myDFPlayer.volume(config.volume);
       myDFPlayer.enableLoop();
       myDFPlayer.play(num);
       AlertTime=millis(); }
  else {
       myDFPlayer.stop(); }
  
  #ifdef DEBUG
    Serial.println(__FUNCTION__); 
  #endif  
}
/**************************************************************************************************************************************************************************/
int CheckAlertMaxNum (int num)
{ 
#ifdef DEBUG
   Serial.print(__FUNCTION__); 
#endif
  int max_alert_num=myDFPlayer.readFileCounts();
  if (num == 0) return 1;
  if (num > max_alert_num) return max_alert_num;
  return num;
}
/**************************************************************************************************************************************************************************/
void CheckAlert (void)
{ if (!CFG_saved || (now.Second() != 0 )) return;
  if (Alert_is_ON == true) 
    { if ( millis() - AlertTime < MaxAlertTime) return; 
      else
      { DoAlert(false,0); }
    }
  if (now.Second() == 0 ) {
    for (int i=0; i<8; i++)
    { 
      if (config.alarm_param[i][2] & (1 << al_en) != 0)
      { if ( config.alarm_param[i][2] & (1 << now.DayOfWeek()))
        { 
          if ( (now.Hour() == config.alarm_param[i][0]) && (now.Minute() == config.alarm_param[i][1]))
          { 
              config.alarm_param[i][3] = CheckAlertMaxNum (config.alarm_param[i][3]);
              DoAlert(true,config.alarm_param[i][3]);

              #ifdef DEBUG
              Serial.println(__FUNCTION__); 
              #endif
              break;
          }
        }
      }
    }
  } 
}
/**************************************************************************************************************************************************************************/
void PrintTime (RtcDateTime TIME)
{
  String values ="";
   values += (String)TIME.DayOfWeek() + "   ";
  if (TIME.DayOfWeek() == 1) values += "Пнд";
  else if (TIME.DayOfWeek() == 2) values += "Вт";
  else if (TIME.DayOfWeek() == 3) values += "Ср";
  else if (TIME.DayOfWeek()== 4) values += "Чт";
  else if (TIME.DayOfWeek()== 5) values += "Пт";
  else if (TIME.DayOfWeek()== 6) values += "Сб";
  else if (TIME.DayOfWeek()== 0) values += "Вс";
  values += " ";
  values += String(now.Day() < 10 ? "0" : "") + now.Day() + "."  + String(now.Month() < 10 ? "0" : "") + (String) now.Month()+ "." + (String) now.Year();
  values += " " + String(now.Hour() < 10 ? "0" : "") + (String) now.Hour() + ":" + String(now.Minute() < 10 ? "0" : "") +(String) now.Minute() + ":" + String(now.Second() < 10 ? "0" : "") + now.Second();
  Serial.println(values);
}
/**************************************************************************************************************************************************************************/
uint8_t CheckIntens (uint16_t _adc)
{   
    if (_adc <= 450) return config.intens1;
    if (_adc <= 600) return config.intens2;
    if (_adc > 600) return config.intens3;
}
/**************************************************************************************************************************************************************************/
void MP3printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
/**************************************************************************************************************************************************************************/
void loop() {
  // OTA request handling
  ArduinoOTA.handle();

  //  WebServer requests handling
  server.handleClient();
 
  //**** Normal Skecth code here ... 
//  t.update();
  P.displayAnimate();
  if(P.getZoneStatus(Zone_UP))   { displayClock(Zone_UP);  }
  if(P.getZoneStatus(Zone_DOWN)) { 
    switch (ZoneDown_Mode) {
      case SHOW_DATE:
           displayDate(Zone_DOWN);
           break;
      case SHOW_WEATER:
           scrollWeather(Zone_DOWN);
           ZoneDown_Mode=SHOW_DATE;
           break;
      default:
           ZoneDown_Mode=SHOW_DATE;
    }
  }

  delay(0);
  yield();

  if (NeedNowUpdate) { UpdateNow(); NeedNowUpdate=false;}
  if (NeedCheckAlert) {CheckAlert(); NeedCheckAlert=false;}  
  if (config.Update_Time_Via_NTP_Every != 0) {
    if (millis() - NTP_update_period >= 1000L * config.Update_Time_Via_NTP_Every)
    {
      NTP_update_period=millis();
      UpdateRTC(getNTPtime());
      UpdateNow();
    }
  }

  if (config.Update_Weather_Every != 0)
  {if (millis() - PeriodWeather  >= 1000L * config.Update_Weather_Every)
    { PeriodWeather = millis();
      getWeatherData();
    }
  }


  if (millis()-PeriodIntens >=500)
  {  Intens = CheckIntens (analogRead(A0)); P.setIntensity(Intens);
     PeriodIntens=millis();
  }

  /*
  if (millis()-Period >= 1000)
  {
    Period = millis();
    //Serial.print(F("Button: ")); Serial.println(digitalRead(D0));
    //Serial.print(millis()); Serial.print(F("  Event: ")); Serial.print(eventTime); Serial.print(F("  Button: ")); 
    //if (digitalRead(D0) == HIGH) Serial.println("HIGH");
    //else Serial.println("LOW");
    
    Serial.print(F("ADC: ")); Serial.print(analogRead(A0)); Serial.print(F("  Intens: ")); Serial.println(Intens); 

    if (myDFPlayer.available()) {
    MP3printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
    }
  }
 */
 
  if (millis() - eventTime >= 50) {
    if (digitalRead(D0) == LOW) { eventTime=millis();}
    else { 
            if(Alert_is_ON==true) {myDFPlayer.stop(); Alert_is_ON=false;} 
            ZoneDown_Mode=SHOW_WEATER; 
         } 
    //============длительное нажатие кнопки форматирует EEPROM
      if(millis() - eventTime > 15000){      // при нажатии 15 секунд - 
        ResetAll();                 // форматируем EEPROM
        Serial.println("EEPROM formatted");
        ESP.restart();
    }
   }

  if (Serial.available() > 0) {
     char serimp=Serial.read();
     if (serimp == '+' ) {if (config.volume < 30) config.volume++; 
                       Serial.print(F("DFPlayer volume: ")); 
                       Serial.println(config.volume);
                       myDFPlayer.volume(config.volume); }
     if (serimp == '-') {if (config.volume>1) config.volume--; 
                       Serial.print(F("DFPlayer volume: ")); 
                       Serial.println(config.volume);
                       myDFPlayer.volume(config.volume); 
                        }
     if (serimp >= '1' || serimp <= '9' ) { myDFPlayer.play(serimp-48); Serial.print(F("DFPlayer play #")); Serial.println(serimp); 
                                            AlertTime=millis(); Alert_is_ON=true; myDFPlayer.enableLoop();
                                             
                                          }
     if (serimp == 's') { myDFPlayer.stop(); Alert_is_ON=false; }
     if (serimp == 'w') { Serial.print(F("Weat: ")); getWeatherData(); 
                          Serial.print(F("    Str: ")); Serial.print(weatherString);
                          ZoneDown_Mode=SHOW_WEATER;
                        }
                        
  }

}
/**************************************************************************************************************************************************************************/
void ResetAll(){
  EEPROM.begin(512);
  // write a 0 to all 512 bytes of the EEPROM
  for (uint16_t i = 0; i < 512; i++){
  EEPROM.write(i, 0);
  }
  EEPROM.end();
  ESP.restart();
  //ESP.reset();
}
/**************************************************************************************************************************************************************************/
void displayDate(uint8_t Zone = Zone_DOWN){
    if (P.displayAnimate() && P.getZoneStatus(Zone)){
        
      Text = String(now.Day() < 10 ? "0" : "") + String(now.Day()) + "." + \
             String(now.Month() < 10 ? "0" : "") + String(now.Month());
      if (ErrorWiFi || ErrorNTP || ErrorWeather) Text += String("!");

      utf8rus(Text).toCharArray(buf_down, 256);
      P.displayZoneText(Zone,buf_down, PA_CENTER, 0, 200, PA_PRINT, PA_PRINT );
    }
}
/**************************************************************************************************************************************************************************/
void displayClock(uint8_t Zone = Zone_UP){
    if (P.displayAnimate() && P.getZoneStatus(Zone)){
      const char _symb_alert[1]={14};
      Text = String(now.Hour()/10) + String(now.Hour()%10) + \
             String(now.Second()%2 ? ":" : " ") + \
             String(now.Minute()/10) + String(now.Minute()%10);
      Text +=String(AlarmSet ==true ? _symb_alert : " ");
      utf8rus(Text).toCharArray(buf_up, 10);
      P.displayZoneText(Zone,buf_up, PA_CENTER, 0, 200, PA_PRINT, PA_PRINT );
    }
}
/**************************************************************************************************************************************************************************/
void scrollIP(uint8_t Zone = Zone_DOWN){
  Text = "Ваш IP: "+ipstring;
  if (P.getZoneStatus(Zone_DOWN)){
  utf8rus(Text).toCharArray(buf_down, 256);
  P.displayZoneText(Zone,buf_down, PA_LEFT, 50,1000, PA_SCROLL_LEFT, PA_PRINT);
  }
}
/**************************************************************************************************************************************************************************/
void scrollDefaultConnect(uint8_t Zone = Zone_DOWN){
  Text = "Отсутствует подключение к WIFI. Подключитесь к точке доступа 'CLOCK_WiFi' и откройте в браузере адрес http://192.168.4.1" ;
  if  (P.getZoneStatus(Zone_DOWN)){
      utf8rus(Text).toCharArray(buf_down, 256);
      P.displayZoneText(Zone,buf_down, PA_CENTER, 50,1000, PA_SCROLL_LEFT,PA_PRINT);
  }
}
/**************************************************************************************************************************************************************************/
void scrollWeather(uint8_t Zone = Zone_DOWN){
  if (ErrorWiFi == true) Text = "Проблема с подключением к сети Интернет. Проверьте настройки сети.";
  else if (ErrorNTP == true) Text = "Проблема с синхронизацией часов. Проверьте настройки NTP.";
  else if (ErrorWeather == true) Text = "Проблема с получением данных о погоде. Проверьте настройки.";
  else if (config.Update_Weather_Every == 0) Text = "Получением данных о погоде запрещено. Проверьте настройки.";
  else Text = weatherString;
  
  if  (P.getZoneStatus(Zone_DOWN)){
      utf8rus(Text).toCharArray(buf_down, 256);
      P.displayZoneText(Zone,buf_down, PA_CENTER, 50,500, PA_SCROLL_LEFT,PA_PRINT);
  }
}
/**************************************************************************************************************************************************************************/
// =======================================================================
// Берем погоду с сайта openweathermap.org
// =======================================================================
const char *weatherHost = "api.openweathermap.org";
void getWeatherData(void)
{ 
  ErrorWeather=false;
  ErrorWiFi=false;
  #ifdef DEBUG  
  Serial.println(__FUNCTION__); 
  #endif  
  
  if (WIFI_connected!= WL_CONNECTED) {
  #ifdef DEBUG    
      Serial.println("Not Internet connection");
  #endif
  ErrorWiFi=true;
  return;
  }

  #ifdef DEBUG  
  Serial.print("connecting to "); Serial.println(weatherHost);
  #endif
  if (client.connect(weatherHost, 80)) {
    client.println(String("GET /data/2.5/weather?id=") + cityID + "&units=metric&appid=" + weatherKey + "&lang=ru" + "\r\n" +
                "Host: " + weatherHost + "\r\nUser-Agent: ArduinoWiFi/1.1\r\n" +
                "Connection: close\r\n\r\n");
  } else {
    ErrorWeather=true;
    #ifdef DEBUG  
    Serial.println("connection failed");
    #endif
    return;
  }
  String line;
  int repeatCounter = 0;
  while (!client.available() && repeatCounter < 10) {
    delay(400);
    Serial.println("w.");
    repeatCounter++;
  }
  while (client.connected() && client.available()) {
    char c = client.read(); 
    //if (c == '[' || c == ']') c = ' ';
    line += c;
  }

  client.stop();
  #ifdef DEBUG
  Serial.println(line + "\n");
  #endif
  DynamicJsonBuffer jsonBuf;
  JsonObject &root = jsonBuf.parseObject(line);
  if (!root.success())
  {
    #ifdef DEBUG
    Serial.println("parseObject() failed");
    #endif
    ErrorWeather=true;
    return;
  }
  //weatherMain = root["weather"]["main"].as<String>();
  
  if (root["weather"].is<JsonArray&>()) {
      JsonArray& nestedArray = root["weather"].asArray();
      weatherDescription="";
      if (nestedArray.size() > 1) weatherDescription="местами ";

      
      for (int i=0; i < nestedArray.size(); i++)
      {
        if (i > 0) weatherDescription += " и ";
        weatherDescription += nestedArray[i]["description"].as<String>();
        
      }
  }
  else 
  {
     weatherDescription = root["weather"]["description"].as<String>();
     weatherDescription.toLowerCase();
  }
  temp = root["main"]["temp"];
  humidity = root["main"]["humidity"];
  pressure = root["main"]["pressure"];
  windSpeed = root["wind"]["speed"];
  windDeg = root["wind"]["deg"];
  clouds = root["clouds"]["all"];
  
  String deg = String(char(15));
  weatherString = "На улице: " + String(temp,0) + deg + " ";
  weatherString += weatherDescription;
  weatherString += " Влажн. " + String(humidity) + "% ";
  weatherString += "Давл. " + String(pressure/1.3332239,0) + " мм. ";
  //weatherString += "Облачность: " + String(clouds) + "% ";

  String windDegString;

  if (windDeg>=345 || windDeg<=22) windDegString = "cеверный";
  if (windDeg>=23 && windDeg<=68) windDegString = "cеверо-восточный";
  if (windDeg>=69 && windDeg<=114) windDegString = "восточный";
  if (windDeg>=115 && windDeg<=160) windDegString = "юго-восточный";
  if (windDeg>=161 && windDeg<=206) windDegString = "южный";
  if (windDeg>=207 && windDeg<=252) windDegString = "юго-западный";
  if (windDeg>=253 && windDeg<=298) windDegString = "западный";
  if (windDeg>=299 && windDeg<=344) windDegString = "северо-западный";

  weatherString += "Ветер " + windDegString + " " + String(windSpeed,1) + " м/с";
  ErrorWeather=false;
}

/**************************************************************************************************************************************************************************/
/*  void tvoday(String line){
    String s;
    int strt = line.indexOf('}');
    for (int i=1; i<=4; i++){
      strt = line.indexOf('}', strt + 1);
    }
    s = line.substring(2+strt, line.length());
    tempz=s;
}
/**************************************************************************************************************************************************************************/
String utf8rus(String source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}
