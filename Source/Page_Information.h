#ifndef PAGE_INFOMATION_H
#define PAGE_INFOMATION_H
/**************************************************************************************************************************************************************************/
const char PAGE_Information[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="stylesheet" href="style.css" type="text/css" />
<script src="microajax.js"></script> 
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Информация о системе</strong>
<hr>
<table border="0"  cellspacing="0" cellpadding="3" style="width:310px" >
<tr><td align="right">SSID :</td><td><span id="x_ssid"></span></td></tr>
<tr><td align="right">IP :</td><td><span id="x_ip"></span></td></tr>
<tr><td align="right">Маска :</td><td><span id="x_netmask"></span></td></tr>
<tr><td align="right">Шлюз :</td><td><span id="x_gateway"></span></td></tr>
<tr><td align="right">MAC :</td><td><span id="x_mac"></span></td></tr>
<tr><td align="right">WiFi :</td><td><span id="x_WF"></span></td></tr>
<tr><td align="right">NTP :</td><td><span id="x_NTP"></span></td></tr>
<tr><td align="right">Погода :</td><td><span id="x_Wt"></span></td></tr>
<tr><td colspan="2" align="center"><a href="javascript:GetState()" class="btn btn--m btn--blue">Обновить</a></td></tr>
</table>
<br>

<script>
function GetState()
{
  setValues("/admin/infovalues");
}

window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        GetState();
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====" ;
/**************************************************************************************************************************************************************************/
void send_information_values_html ()
{
  String values ="";
  values += "x_ssid|" + (String)WiFi.SSID() +  "|div\n";
  values += "x_ip|" +  (String) WiFi.localIP()[0] + "." +  (String) WiFi.localIP()[1] + "." +  (String) WiFi.localIP()[2] + "." + (String) WiFi.localIP()[3] +  "|div\n";
  values += "x_gateway|" +  (String) WiFi.gatewayIP()[0] + "." +  (String) WiFi.gatewayIP()[1] + "." +  (String) WiFi.gatewayIP()[2] + "." + (String) WiFi.gatewayIP()[3] +  "|div\n";
  values += "x_netmask|" +  (String) WiFi.subnetMask()[0] + "." +  (String) WiFi.subnetMask()[1] + "." +  (String) WiFi.subnetMask()[2] + "." + (String) WiFi.subnetMask()[3] +  "|div\n";
  values += "x_mac|" + GetMacAddress() +  "|div\n";
  
  values += "x_WF|";
  if (ErrorWiFi == true) values += "Проблема!"; else values += "OK";
  values += "|div\n";

  values += "x_NTP|";
  if (config.Update_Time_Via_NTP_Every == 0) values += "Запрет";
  else { if (ErrorNTP == true) values += "Проблема!"; else values += "OK"; }
  values += "|div\n";

  values += "x_Wt|";
  if (config.Update_Weather_Every == 0) values += "Запрет";
  else { if (ErrorWeather == true) values += "Проблема!"; else values += "OK"; }
  values += "|div\n";

  server.send ( 200, "text/plain", values);
#ifdef DEBUG  
  Serial.println(__FUNCTION__); 
#endif  
}
/**************************************************************************************************************************************************************************/
#endif
