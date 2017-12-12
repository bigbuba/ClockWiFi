#ifndef NTP_H
#define NTP_H
#include "WIFI_Clock.h"
/**************************************************************************************************************************************************************************/
static const uint8_t monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/**************************************************************************************************************************************************************************/
#define LEAP_YEAR(Y) ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )
/**************************************************************************************************************************************************************************/
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[ NTP_PACKET_SIZE];
/**************************************************************************************************************************************************************************/
unsigned long getNTPtime(void)
{  
#ifdef DEBUG  
  Serial.println(__FUNCTION__); 
#endif   
  unsigned long _unixTime = 0;
  if (WiFi.status() == WL_CONNECTED)
  { ErrorWiFi=false;
    UDPNTPClient.begin(2390);  // Port for NTP receive
    IPAddress timeServerIP;
    WiFi.hostByName(config.ntpServerName.c_str(), timeServerIP);

#ifdef DEBUG
    Serial.println("sending NTP packet...");
#endif    
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    packetBuffer[0] = 0b11100011;   // LI, Version, Mode
    packetBuffer[1] = 0;     // Stratum, or type of clock
    packetBuffer[2] = 6;     // Polling Interval
    packetBuffer[3] = 0xEC;  // Peer Clock Precision
    packetBuffer[12]  = 49;
    packetBuffer[13]  = 0x4E;
    packetBuffer[14]  = 49;
    packetBuffer[15]  = 52;
    UDPNTPClient.beginPacket(timeServerIP, 123);
    UDPNTPClient.write(packetBuffer, NTP_PACKET_SIZE);
    UDPNTPClient.endPacket();

    delay(200);
    yield();
    
    int cb = UDPNTPClient.parsePacket();
    if (cb == 0) {
#ifdef DEBUG
      Serial.println("No NTP packet yet");
#endif      
    }
    else
    {
#ifdef DEBUG
      Serial.print("NTP packet received, length=");
      Serial.println(cb);
#endif      
      UDPNTPClient.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
      unsigned long secsSince1900 = highWord << 16 | lowWord;
      const unsigned long seventyYears = 2208988800UL;
      _unixTime = secsSince1900 - seventyYears;

    }
  } else {
    ErrorWiFi=true;
#ifdef DEBUG    
    Serial.println("Internet yet not connected");
#endif    
  }
  yield();
  return _unixTime;
}
/**************************************************************************************************************************************************************************/
void UpdateRTC (unsigned long TIME)
{ 
  #ifdef DEBUG  
    Serial.println(__FUNCTION__); 
  #endif 
  
  if (TIME != 0) {
      RtcDateTime tmp;
      tmp.InitWithEpoch32Time(TIME);
      Rtc.SetDateTime(tmp);
      ErrorNTP=false;
    #ifdef DEBUG      
      Serial.print(F("RTC updated: ")); PrintTime (Rtc.GetDateTime());
    #endif      
  }
  else
  {
  #ifdef DEBUG
  
     Serial.println(F("RTC was not updated"));
  #endif     
     ErrorNTP=true;
  }
}
/**************************************************************************************************************************************************************************/
boolean summerTime(unsigned long TIME)
{
  RtcDateTime tmp; tmp.InitWithEpoch32Time(TIME);
  
  if (tmp.Month() < 3 || tmp.Month() > 10) return false;                  // Not Summertime in Jan, Feb, Nov, Dez
  if (tmp.Month() > 3 && tmp.Month() < 10) return true;                   // Summertime in Apr, Mai, Jun, Jul, Aug, Sep
  
  if (tmp.Month() == 3 && (tmp.Hour() + 24 * tmp.Day()) >= (3 +  24 * (31 - (5 * tmp.Year() / 4 + 4) % 7)) || tmp.Month() == 10 && (tmp.Hour() + 24 * tmp.Day()) < (3 +  24 * (31 - (5 * tmp.Year() / 4 + 1) % 7))) 
      return true;
 return false;
}     
/**************************************************************************************************************************************************************************/
unsigned long adjustTimeZone(unsigned long TIME, int TimeZone, bool IsDayLightSaving) 
{
  TIME += TimeZone * 360;
  if (IsDayLightSaving && summerTime(TIME)) TIME += 3600;
  return TIME;
}
/**************************************************************************************************************************************************************************/
void UpdateNow (void)
{
  RtcDateTime tmp = Rtc.GetDateTime();
  now.InitWithEpoch32Time(adjustTimeZone(tmp.Epoch32Time(), config.timeZone, config.isDayLightSaving));
}

/**************************************************************************************************************************************************************************/
void CheckAlarmSet(void) {  AlarmSet=false; for (int i=0; i<8; i++) if (config.alarm_param[i][2] & (1 << al_en) && config.alarm_param[i][2] > 1) {AlarmSet=true; return;} }
/**************************************************************************************************************************************************************************/
void RTC_Tick(void)
{ NeedNowUpdate = true;
  NeedCheckAlert = true;
}
/**************************************************************************************************************************************************************************/
#endif
