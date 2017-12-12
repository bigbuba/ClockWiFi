#ifndef WIFI_CLOCK_H
#define WIFI_CLOCK_H
  ///////////// DEBUG ////////////////////
  #define DEBUG
  ///////////// Config ////////////////////
  struct strConfig {
    boolean dhcp;                         // 1 Byte - EEPROM 16 
    boolean isDayLightSaving;             // 1 Byte - EEPROM 17
    long Update_Time_Via_NTP_Every;       // 4 Byte - EEPROM 18
    long timeZone;                        // 4 Byte - EEPROM 22
    byte  IP[4];                          // 4 Byte - EEPROM 32
    byte  Netmask[4];                     // 4 Byte - EEPROM 36
    byte  Gateway[4];                     // 4 Byte - EEPROM 40
    byte  DNS[4];                         // 4 Byte - EEPROM 230
    String ssid;                          // up to 32 Byte - EEPROM 64
    String password;                      // up to 32 Byte - EEPROM 96
    String ntpServerName;                 // up to 32 Byte - EEPROM 128
    String DeviceName;                    // up to 32 Byte - EEPROM 160
    String email;                         // up to 32 Byte - EEPROM 192
    byte alarm_param[8][4];                  //8 Byte - EEPROM 235 (to 267)
    byte volume;
    byte intens1;
    byte intens2;
    byte intens3;
    long Update_Weather_Every;
  };
  ///////////// System ////////////////////
  #define analogPIN A0
  #define CFG_NET 0
  #define CFG_ALL 1
  ///////////// Display ////////////////////
  #define MAX_DEVICES 8
  #define CLK_PIN     D5 // or SCK
  #define DATA_PIN    D7 // or MOSI
  #define CS_PIN      D8 // or SS
  #define MD_Zones 2
  #define Zone_UP 0
  #define Zone_DOWN 1
  #define SHOW_DATE 0
  #define SHOW_WEATER 1
  ///////////// Alert ////////////////////
  #define al_en 0
  #define al_pn 1
  #define al_vt 2
  #define al_sr 3
  #define al_ct 4
  #define al_pt 5
  #define al_sb 6
  #define al_vs 7
  #define MaxAlertTime 600000

  #define FAlertStop 1
  #define FAlertPlay 2
  ////////////////////////////////////////
  extern "C" { 
  #include "user_interface.h" 
  }
  #include "global.h"
  #include "NTP.h"
  #include "Page_Admin.h"
  #include "Page_Script.js.h"
  #include "Page_Style.css.h"
  #include "Page_NTPSettings.h"
  #include "Page_Information.h"
  #include "Page_General.h"
  #include "Page_NetworkConfiguration.h"
  #include "Page_Alert.h"
  #include "Page_System.h"
  #include "Page_remctrl.h"
#endif
/**************************************************************************************************************************************************************************/
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//#include <Ticker.h>
#include <EEPROM.h>
#include <RtcDS3231.h>
#include "Timer.h"
#include "Wire.h"
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include "Fonts.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#if defined(ESP8266)
  #include <pgmspace.h>
#else
  #include <avr/pgmspace.h>
#endif
/**************************************************************************************************************************************************************************/
extern unsigned long Period;

/**************************************************************************************************************************************************************************/
extern SoftwareSerial mySoftwareSerial;
extern DFRobotDFPlayerMini myDFPlayer;
extern RtcDS3231<TwoWire> Rtc;
extern MD_Parola P;
extern ESP8266WebServer server;
extern bool ErrorNTP;
extern bool ErrorWiFi;
extern bool ErrorWeather;
extern bool AlarmSet;
extern RtcDateTime now;
extern bool CFG_saved;
extern bool Need_Redraw_UP;
extern bool Need_Redraw_DOWN;
extern volatile bool NeedNowUpdate;
extern volatile bool NeedCheckAlert;
extern unsigned long NTP_update_period;
extern uint8_t Intens;
extern byte ZoneDown_Mode;
extern strConfig config;
/**************************************************************************************************************************************************************************/
void scrollIP(uint8_t);
void scrollDefaultConnect(uint8_t);
void getWeatherData();
void doAlert();
void displayClock(uint8_t);
void displayDate(uint8_t);
void scrollWeather(uint8_t);

void printConfig(void);
void LoadDefaultConfig (uint8_t);
void PrintTime (RtcDateTime);
void PrintEEPROM (void);
void MP3printDetail(uint8_t, int);
void RTC_Tick(void);
void UpdateNow (void);
void CheckAlert (void);
void ResetAll();
void CheckAlarmSet(void);

void DoAlert (bool, int);
int CheckAlertMaxNum (int);
