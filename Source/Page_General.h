#ifndef PAGE_GENERAL_H
#define PAGE_GENERAL_H
/**************************************************************************************************************************************************************************/
const char PAGE_AdminGeneralSettings[] PROGMEM =  R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Настройки прогноза погоды</strong>
<hr>
<form action="" method="post">
<table border="0"  cellspacing="0" cellpadding="2" >
<tr><td align="right">API ключь: </td><td><input id="devicename" name="devicename" size="32" value=""></td></tr>
<tr><td align="right">Город (cityID): </td><td><input type="text" id="email" name="email" size="8" value=""></td></tr>
<tr><td align="right">Обновлять каждые:</td><td><input type="text" id="update" name="update" size="8" maxlength="6" value=""> сек.(0=запрет)</td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Сохранить"></td></tr>
</table>
</form>
<a href="http://openweathermap.org/api" align="center" target="_blank">Получить API ключ</a><br><br>
<a href="http://openweathermap.org/help/city_list.txt" align="center" target="_blank">Получить "cityID" своего города</a><br>
<br>

<script>
window.onload = function ()
{
	load("style.css","css", function() 
	{
		load("microajax.js","js", function() 
		{
				setValues("/admin/generalvalues");
		});
	});
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}
</script>
)=====";
/**************************************************************************************************************************************************************************/
void send_devicename_value_html()
{	String values ="";
	values += "devicename|" + (String) config.DeviceName + "|div\n";
	server.send ( 200, "text/plain", values);
#ifdef DEBUG  
  Serial.println(__FUNCTION__); 
#endif  	
}
/**************************************************************************************************************************************************************************/
void send_general_html()
{	if (server.args() > 0 )  // Save Settings
	{	
		String temp = "";
		for ( uint8_t i = 0; i < server.args(); i++ ) {
			if (server.argName(i) == "devicename") config.DeviceName = urldecode(server.arg(i)); 
      if (server.argName(i) == "email") config.email = urldecode(server.arg(i));
      if (server.argName(i) == "update") config.Update_Weather_Every =  server.arg(i).toInt(); 
		}
		WriteConfig();
	}
	server.send_P ( 200, "text/html", PAGE_AdminGeneralSettings ); 
#ifdef DEBUG  
  Serial.println(__FUNCTION__); 
#endif  
}
/**************************************************************************************************************************************************************************/
void send_general_configuration_values_html()
{
	String values ="";
	values += "devicename|" +  (String)  config.DeviceName +  "|input\n";
  values += "email|" +  (String)  config.email +  "|input\n";
  values += "update|" +  (String) config.Update_Weather_Every + "|input\n";
 
	server.send ( 200, "text/plain", values);
#ifdef DEBUG  
  Serial.println(__FUNCTION__); 
#endif  
}
/**************************************************************************************************************************************************************************/
#endif
