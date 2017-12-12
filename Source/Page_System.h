#ifndef PAGE_SYSTEM_H
#define PAHE_SYSTEM_H

#include "WIFI_Clock.h"
/**************************************************************************************************************************************************************************/
const char PAGE_System_configuration[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Настройки системы</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">Время:</td><td><input align="center" style="width:100%" type="time" id="time" name="time" step="1"></td></tr>
<tr><td align="right">Дата:</td><td><input align="center" style="width:100%" type="date" id="date" name="date"></td></tr>
<tr><td align="right">Летнее время:</td><td><input type="checkbox" id="dst" name="dst"></td></tr>
<tr><td align="right"> </td></tr>
<tr><td align="right">Громкость:</td><td><select  id="volume" name="volume">
  <option value="1">1(min)</option>
  <option value="2"> 2</option>
  <option value="3"> 3</option>
  <option value="4"> 4</option>
  <option value="5"> 5</option>
  <option value="6"> 6</option>
  <option value="7"> 7</option>
  <option value="8"> 8</option>
  <option value="9"> 9</option>
  <option value="10">10</option>
  <option value="11">11</option>
  <option value="12">12</option>
  <option value="13">13</option>
  <option value="14">14</option>
  <option value="15">15</option>
  <option value="16">16</option>
  <option value="17">17</option>
  <option value="18">18</option>
  <option value="19">19</option>
  <option value="20">20</option>
  <option value="21">21</option>
  <option value="22">22</option>
  <option value="23">23</option>
  <option value="24">24</option>
  <option value="25">25</option>
  <option value="26">26</option>
  <option value="27">27</option>
  <option value="28">28</option>
  <option value="29">29</option>
  <option value="30">30(max)</option>
</select></tr>
<tr><td align="right"> </td></tr>
<tr><td colspan="2" align="center">Яркость:</td></tr>
<tr><td align="right">Ночь:</td><td><select id="intens1" name="intens1">
  <option value="1">1(min)</option>
  <option value="2"> 2</option>
  <option value="3"> 3</option>
  <option value="4"> 4</option>
  <option value="5"> 5</option>
  <option value="6"> 6</option>
  <option value="7"> 7</option>
  <option value="8"> 8</option>
  <option value="9"> 9</option>
  <option value="10">10</option>
  <option value="11">11</option>
  <option value="12">12</option>
  <option value="13">13</option>
  <option value="14">14</option>
  <option value="15">15(max)</option>
</select></tr>
<tr><td align="right">Сумерки:</td><td><select id="intens2" name="intens2">
  <option value="1">1(min)</option>
  <option value="2"> 2</option>
  <option value="3"> 3</option>
  <option value="4"> 4</option>
  <option value="5"> 5</option>
  <option value="6"> 6</option>
  <option value="7"> 7</option>
  <option value="8"> 8</option>
  <option value="9"> 9</option>
  <option value="10">10</option>
  <option value="11">11</option>
  <option value="12">12</option>
  <option value="13">13</option>
  <option value="14">14</option>
  <option value="15">15(max)</option>
</select></tr>
<tr><td align="right">День:</td><td><select id="intens3" name="intens3">
  <option value="1">1(min)</option>
  <option value="2"> 2</option>
  <option value="3"> 3</option>
  <option value="4"> 4</option>
  <option value="5"> 5</option>
  <option value="6"> 6</option>
  <option value="7"> 7</option>
  <option value="8"> 8</option>
  <option value="9"> 9</option>
  <option value="10">10</option>
  <option value="11">11</option>
  <option value="12">12</option>
  <option value="13">13</option>
  <option value="14">14</option>
  <option value="15">15(max)</option>
</select></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Сохранить"></td></tr>
</table>
</form>

<script>
window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/systemvalues");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====";
/**************************************************************************************************************************************************************************/
void send_system_configuration_html()
{
  if (server.args() > 0 )  // Save Settings
  {
    String temp = "";
    uint16_t _year,_month,_day,_hour,_minute,_second;
    
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "date") 
      {
        temp=server.arg(i).substring(0,4); _year=temp.toInt();
        temp=server.arg(i).substring(5,7); _month=temp.toInt();
        temp=server.arg(i).substring(8,10); _day=temp.toInt();
      }
      if (server.argName(i) == "time") 
      {
        temp=server.arg(i).substring(0,2); _hour=temp.toInt();
        temp=server.arg(i).substring(3,5); _minute=temp.toInt();
        temp=server.arg(i).substring(6,8); _second=temp.toInt();
      }
      if (server.argName(i) == "dst") config.isDayLightSaving = true; 
      if (server.argName(i) == "volume") config.volume=server.arg(i).toInt();
      if (server.argName(i) == "intens1") config.intens1=server.arg(i).toInt();
      if (server.argName(i) == "intens2") config.intens2=server.arg(i).toInt();
      if (server.argName(i) == "intens3") config.intens3=server.arg(i).toInt();
    }
    RtcDateTime _tmp_clock = RtcDateTime(_year,_month,_day,_hour,_minute,_second);
    unsigned long _tmp = _tmp_clock.Epoch32Time();
    _tmp -= config.timeZone * 360;
    if (config.isDayLightSaving && summerTime(_tmp)) _tmp -= 3600;
    _tmp_clock.InitWithEpoch32Time(_tmp);
    Rtc.SetDateTime(_tmp_clock);
    if (config.Update_Time_Via_NTP_Every !=0 ) {  UpdateRTC(getNTPtime()); NTP_update_period=millis();  }   
    UpdateNow();   
  }
  WriteConfig();
  server.send_P ( 200, "text/html", PAGE_System_configuration ); 
#ifdef DEBUG
  Serial.println(__FUNCTION__); 
#endif  
}
/**************************************************************************************************************************************************************************/
void send_system_configuration_values_html()
{
  String values ="";
  values += "time|" + String(now.Hour() < 10 ? "0" : "") + (String) now.Hour() + ":" + String(now.Minute() < 10 ? "0" : "") +(String) now.Minute() + ":" + String(now.Second() < 10 ? "0" : "") + now.Second() + "|input\n";
  values += "date|" + (String) now.Year() + "-" + String(now.Month() < 10 ? "0" : "") + (String) now.Month() + "-" + String(now.Day() < 10 ? "0" : "") + now.Day() + "|input\n";
  values += "dst|" +  (String) (config.isDayLightSaving ? "checked" : "") + "|chk\n";
  values += "volume|" + (String) (config.volume) + "|input\n";
  values += "intens1|" + (String) (config.intens1) + "|input\n";
  values += "intens2|" + (String) (config.intens2) + "|input\n";
  values += "intens3|" + (String) (config.intens3) + "|input\n";
  server.send ( 200, "text/plain", values);
#ifdef DEBUG  
  Serial.println(__FUNCTION__); 
#endif  
}
/**************************************************************************************************************************************************************************/
#endif
