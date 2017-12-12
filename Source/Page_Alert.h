#ifndef PAGE_ALERT_H
#define PAGE_ALERT_H
/**************************************************************************************************************************************************************************/
const char PAGE_AlertConfiguration[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Настройки будильников</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="4" >
<tr><td align="center">ВКЛ</td><td align="center">Время</td><td align="left">Повторять</td><td align="left">Мелодия</td></tr>
<tr><td align="center"><input type="checkbox" id="alarm1_en" name="alarm1_en"></td><td align="center"><input type="time" id="alarm1" name="alarm1" value="00:00"></td><td>
Пн<input type="checkbox" id="alarm1_pn" name="alarm1_pn">
Вт<input type="checkbox" id="alarm1_vt" name="alarm1_vt">
Ср<input type="checkbox" id="alarm1_sr" name="alarm1_sr">
Чт<input type="checkbox" id="alarm1_ct" name="alarm1_ct">
Пт<input type="checkbox" id="alarm1_pt" name="alarm1_pt">
Сб<input type="checkbox" id="alarm1_sb" name="alarm1_sb">
Вс<input type="checkbox" id="alarm1_vs" name="alarm1_vs"></td>
<td align="left"><input type="number" id="snd1" name="snd1" min="1" max="255" size="8" maxlength="6" value="">
<input type="button" id="btn1" style="width:50px" onclick="Alarm_test('btn1','snd1')" value="Play"></td>
</tr>
<tr><td align="center"><input type="checkbox" id="alarm2_en" name="alarm2_en"></td><td align="center"><input type="time" id="alarm2" name="alarm2" value="00:00"></td><td>
Пн<input type="checkbox" id="alarm2_pn" name="alarm2_pn">
Вт<input type="checkbox" id="alarm2_vt" name="alarm2_vt">
Ср<input type="checkbox" id="alarm2_sr" name="alarm2_sr">
Чт<input type="checkbox" id="alarm2_ct" name="alarm2_ct">
Пт<input type="checkbox" id="alarm2_pt" name="alarm2_pt">
Сб<input type="checkbox" id="alarm2_sb" name="alarm2_sb">
Вс<input type="checkbox" id="alarm2_vs" name="alarm2_vs"></td>
<td align="left"><input type="number" id="snd2" name="snd2" min="1" max="255" size="8" maxlength="6" value="">
<input type="button" id="btn2" style="width:50px" onclick="Alarm_test('btn2','snd2')" value="Play"></td>
</tr>
<tr><td align="center"><input type="checkbox" id="alarm3_en" name="alarm3_en"></td><td align="center"><input type="time" id="alarm3" name="alarm3" value="00:00"></td><td>
Пн<input type="checkbox" id="alarm3_pn" name="alarm3_pn">
Вт<input type="checkbox" id="alarm3_vt" name="alarm3_vt">
Ср<input type="checkbox" id="alarm3_sr" name="alarm3_sr">
Чт<input type="checkbox" id="alarm3_ct" name="alarm3_ct">
Пт<input type="checkbox" id="alarm3_pt" name="alarm3_pt">
Сб<input type="checkbox" id="alarm3_sb" name="alarm3_sb">
Вс<input type="checkbox" id="alarm3_vs" name="alarm3_vs"></td>
<td align="left"><input type="number" id="snd3" name="snd3" min="1" max="255" size="8" maxlength="6" value="">
<input type="button" id="btn3" style="width:50px" onclick="Alarm_test('btn3','snd3')" value="Play"></td>
</tr>
<tr><td align="center"><input type="checkbox" id="alarm4_en" name="alarm4_en"></td><td align="center"><input type="time" id="alarm4" name="alarm4" value="00:00"></td><td>
Пн<input type="checkbox" id="alarm4_pn" name="alarm4_pn">
Вт<input type="checkbox" id="alarm4_vt" name="alarm4_vt">
Ср<input type="checkbox" id="alarm4_sr" name="alarm4_sr">
Чт<input type="checkbox" id="alarm4_ct" name="alarm4_ct">
Пт<input type="checkbox" id="alarm4_pt" name="alarm4_pt">
Сб<input type="checkbox" id="alarm4_sb" name="alarm4_sb">
Вс<input type="checkbox" id="alarm4_vs" name="alarm4_vs"></td>
<td align="left"><input type="number" id="snd4" name="snd4" min="1" max="255" size="8" maxlength="6" value="">
<input type="button" id="btn4" style="width:50px" onclick="Alarm_test('btn4','snd4')" value="Play"></td>
</tr>
<tr><td align="center"><input type="checkbox" id="alarm5_en" name="alarm5_en"></td><td align="center"><input type="time" id="alarm5" name="alarm5" value="00:00"></td><td>
Пн<input type="checkbox" id="alarm5_pn" name="alarm5_pn">
Вт<input type="checkbox" id="alarm5_vt" name="alarm5_vt">
Ср<input type="checkbox" id="alarm5_sr" name="alarm5_sr">
Чт<input type="checkbox" id="alarm5_ct" name="alarm5_ct">
Пт<input type="checkbox" id="alarm5_pt" name="alarm5_pt">
Сб<input type="checkbox" id="alarm5_sb" name="alarm5_sb">
Вс<input type="checkbox" id="alarm5_vs" name="alarm5_vs"></td>
<td align="left"><input type="number" id="snd5" name="snd5" min="1" max="255" size="8" maxlength="6" value="">
<input type="button" id="btn5" style="width:50px" onclick="Alarm_test('btn5','snd5')" value="Play"></td>
</tr>
<tr><td align="center"><input type="checkbox" id="alarm6_en" name="alarm6_en"></td><td align="center"><input type="time" id="alarm6" name="alarm6" value="00:00"></td><td>
Пн<input type="checkbox" id="alarm6_pn" name="alarm6_pn">
Вт<input type="checkbox" id="alarm6_vt" name="alarm6_vt">
Ср<input type="checkbox" id="alarm6_sr" name="alarm6_sr">
Чт<input type="checkbox" id="alarm6_ct" name="alarm6_ct">
Пт<input type="checkbox" id="alarm6_pt" name="alarm6_pt">
Сб<input type="checkbox" id="alarm6_sb" name="alarm6_sb">
Вс<input type="checkbox" id="alarm6_vs" name="alarm6_vs"></td>
<td align="left"><input type="number" id="snd6" name="snd6" min="1" max="255" size="8" maxlength="6" value="">
<input type="button" id="btn6" style="width:50px" onclick="Alarm_test('btn6','snd6')" value="Play"></td>
</tr>
<tr><td align="center"><input type="checkbox" id="alarm7_en" name="alarm7_en"></td><td align="center"><input type="time" id="alarm7" name="alarm7" value="00:00"></td><td>
Пн<input type="checkbox" id="alarm7_pn" name="alarm7_pn">
Вт<input type="checkbox" id="alarm7_vt" name="alarm7_vt">
Ср<input type="checkbox" id="alarm7_sr" name="alarm7_sr">
Чт<input type="checkbox" id="alarm7_ct" name="alarm7_ct">
Пт<input type="checkbox" id="alarm7_pt" name="alarm7_pt">
Сб<input type="checkbox" id="alarm7_sb" name="alarm7_sb">
Вс<input type="checkbox" id="alarm7_vs" name="alarm7_vs"></td>
<td align="left"><input type="number" id="snd7" name="snd7" min="1" max="255" size="8" maxlength="6" value="">
<input type="button" id="btn7" style="width:50px" onclick="Alarm_test('btn7','snd7')" value="Play"></td>
</tr>
<tr><td align="center"><input type="checkbox" id="alarm8_en" name="alarm8_en"></td><td align="center"><input type="time" id="alarm8" name="alarm8" value="00:00"></td><td>
Пн<input type="checkbox" id="alarm8_pn" name="alarm8_pn">
Вт<input type="checkbox" id="alarm8_vt" name="alarm8_vt">
Ср<input type="checkbox" id="alarm8_sr" name="alarm8_sr">
Чт<input type="checkbox" id="alarm8_ct" name="alarm8_ct">
Пт<input type="checkbox" id="alarm8_pt" name="alarm8_pt">
Сб<input type="checkbox" id="alarm8_sb" name="alarm8_sb">
Вс<input type="checkbox" id="alarm8_vs" name="alarm8_vs"></td>
<td align="left"><input type="number" id="snd8" name="snd8" min="1" max="255" size="8" maxlength="6" value="">
<input type="button" id="btn8" style="width:50px" onclick="Alarm_test('btn8','snd8')" value="Play"></td>
</tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Сохранить"></td></tr>
</table>
</form>
<br>

<script>
window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/alertvalues");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

function Clear_Alert_test ()
{var btn = document.getElementById("btn1"); btn.value="Play";  
     btn = document.getElementById("btn2"); btn.value="Play";
     btn = document.getElementById("btn3"); btn.value="Play";
     btn = document.getElementById("btn4"); btn.value="Play";
     btn = document.getElementById("btn5"); btn.value="Play";
     btn = document.getElementById("btn6"); btn.value="Play";
     btn = document.getElementById("btn7"); btn.value="Play";
     btn = document.getElementById("btn8"); btn.value="Play"; 
}

function Alarm_test (_btn, _snd)
{  var xmlhttp = new XMLHttpRequest();
   var btn = document.getElementById(_btn);
   var sound = document.getElementById(_snd);

   if (btn.value=='Stop') 
  { 
    btn.value='Play'; 
    xmlhttp.open("GET","/remctrl.html?fun=1&num=0",true); xmlhttp.send();
  }
   else
  {
    Clear_Alert_test();
    if (!isNaN(parseInt(sound.value)) && isFinite(sound.value))
      {   xmlhttp.open("GET","/remctrl.html?fun=2&num=" + sound.value,true); xmlhttp.send();
          btn.value="Stop";
      }
    else
      {   xmlhttp.open("GET","/remctrl.html?fun=1&num=0",true); xmlhttp.send();    
      }
  }
}
</script>
)=====";
/**************************************************************************************************************************************************************************/
void send_alert_html()
{
  uint8_t i = 0;
  char Buf [3];
  String tmp_h, tmp_m,tmp;
  if (server.args() > 0 )  // Save Settings
  {
    for ( i = 0; i < 8; i++ ) { for (int j=0;j<4;j++) { config.alarm_param[i][j]=0; }}
    for ( i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "alarm1_en") config.alarm_param[0][2] = (1 << al_en);
      if (server.argName(i) == "alarm1_pn") config.alarm_param[0][2] += (1 << al_pn);
      if (server.argName(i) == "alarm1_vt") config.alarm_param[0][2] += (1 << al_vt);
      if (server.argName(i) == "alarm1_sr") config.alarm_param[0][2] += (1 << al_sr);
      if (server.argName(i) == "alarm1_ct") config.alarm_param[0][2] += (1 << al_ct);
      if (server.argName(i) == "alarm1_pt") config.alarm_param[0][2] += (1 << al_pt);
      if (server.argName(i) == "alarm1_sb") config.alarm_param[0][2] += (1 << al_sb);
      if (server.argName(i) == "alarm1_vs") config.alarm_param[0][2] += (1 << al_vs);
   
      if (server.argName(i) == "alarm2_en") config.alarm_param[1][2] = (1 << al_en);
      if (server.argName(i) == "alarm2_pn") config.alarm_param[1][2] += (1 << al_pn);
      if (server.argName(i) == "alarm2_vt") config.alarm_param[1][2] += (1 << al_vt);
      if (server.argName(i) == "alarm2_sr") config.alarm_param[1][2] += (1 << al_sr);
      if (server.argName(i) == "alarm2_ct") config.alarm_param[1][2] += (1 << al_ct);
      if (server.argName(i) == "alarm2_pt") config.alarm_param[1][2] += (1 << al_pt);
      if (server.argName(i) == "alarm2_sb") config.alarm_param[1][2] += (1 << al_sb);
      if (server.argName(i) == "alarm2_vs") config.alarm_param[1][2] += (1 << al_vs);

      if (server.argName(i) == "alarm3_en") config.alarm_param[2][2] = (1 << al_en);
      if (server.argName(i) == "alarm3_pn") config.alarm_param[2][2] += (1 << al_pn);
      if (server.argName(i) == "alarm3_vt") config.alarm_param[2][2] += (1 << al_vt);
      if (server.argName(i) == "alarm3_sr") config.alarm_param[2][2] += (1 << al_sr);
      if (server.argName(i) == "alarm3_ct") config.alarm_param[2][2] += (1 << al_ct);
      if (server.argName(i) == "alarm3_pt") config.alarm_param[2][2] += (1 << al_pt);
      if (server.argName(i) == "alarm3_sb") config.alarm_param[2][2] += (1 << al_sb);
      if (server.argName(i) == "alarm3_vs") config.alarm_param[2][2] += (1 << al_vs);

      if (server.argName(i) == "alarm4_en") config.alarm_param[3][2] = (1 << al_en);
      if (server.argName(i) == "alarm4_pn") config.alarm_param[3][2] += (1 << al_pn);
      if (server.argName(i) == "alarm4_vt") config.alarm_param[3][2] += (1 << al_vt);
      if (server.argName(i) == "alarm4_sr") config.alarm_param[3][2] += (1 << al_sr);
      if (server.argName(i) == "alarm4_ct") config.alarm_param[3][2] += (1 << al_ct);
      if (server.argName(i) == "alarm4_pt") config.alarm_param[3][2] += (1 << al_pt);
      if (server.argName(i) == "alarm4_sb") config.alarm_param[3][2] += (1 << al_sb);
      if (server.argName(i) == "alarm4_vs") config.alarm_param[3][2] += (1 << al_vs);

      if (server.argName(i) == "alarm5_en") config.alarm_param[4][2] = (1 << al_en);
      if (server.argName(i) == "alarm5_pn") config.alarm_param[4][2] += (1 << al_pn);
      if (server.argName(i) == "alarm5_vt") config.alarm_param[4][2] += (1 << al_vt);
      if (server.argName(i) == "alarm5_sr") config.alarm_param[4][2] += (1 << al_sr);
      if (server.argName(i) == "alarm5_ct") config.alarm_param[4][2] += (1 << al_ct);
      if (server.argName(i) == "alarm5_pt") config.alarm_param[4][2] += (1 << al_pt);
      if (server.argName(i) == "alarm5_sb") config.alarm_param[4][2] += (1 << al_sb);
      if (server.argName(i) == "alarm5_vs") config.alarm_param[4][2] += (1 << al_vs);

      if (server.argName(i) == "alarm6_en") config.alarm_param[5][2] = (1 << al_en);
      if (server.argName(i) == "alarm6_pn") config.alarm_param[5][2] += (1 << al_pn);
      if (server.argName(i) == "alarm6_vt") config.alarm_param[5][2] += (1 << al_vt);
      if (server.argName(i) == "alarm6_sr") config.alarm_param[5][2] += (1 << al_sr);
      if (server.argName(i) == "alarm6_ct") config.alarm_param[5][2] += (1 << al_ct);
      if (server.argName(i) == "alarm6_pt") config.alarm_param[5][2] += (1 << al_pt);
      if (server.argName(i) == "alarm6_sb") config.alarm_param[5][2] += (1 << al_sb);
      if (server.argName(i) == "alarm6_vs") config.alarm_param[5][2] += (1 << al_vs);

      if (server.argName(i) == "alarm7_en") config.alarm_param[6][2] = (1 << al_en);
      if (server.argName(i) == "alarm7_pn") config.alarm_param[6][2] += (1 << al_pn);
      if (server.argName(i) == "alarm7_vt") config.alarm_param[6][2] += (1 << al_vt);
      if (server.argName(i) == "alarm7_sr") config.alarm_param[6][2] += (1 << al_sr);
      if (server.argName(i) == "alarm7_ct") config.alarm_param[6][2] += (1 << al_ct);
      if (server.argName(i) == "alarm7_pt") config.alarm_param[6][2] += (1 << al_pt);
      if (server.argName(i) == "alarm7_sb") config.alarm_param[6][2] += (1 << al_sb);
      if (server.argName(i) == "alarm7_vs") config.alarm_param[6][2] += (1 << al_vs);

      if (server.argName(i) == "alarm8_en") config.alarm_param[7][2] = (1 << al_en);
      if (server.argName(i) == "alarm8_pn") config.alarm_param[7][2] += (1 << al_pn);
      if (server.argName(i) == "alarm8_vt") config.alarm_param[7][2] += (1 << al_vt);
      if (server.argName(i) == "alarm8_sr") config.alarm_param[7][2] += (1 << al_sr);
      if (server.argName(i) == "alarm8_ct") config.alarm_param[7][2] += (1 << al_ct);
      if (server.argName(i) == "alarm8_pt") config.alarm_param[7][2] += (1 << al_pt);
      if (server.argName(i) == "alarm8_sb") config.alarm_param[7][2] += (1 << al_sb);
      if (server.argName(i) == "alarm8_vs") config.alarm_param[7][2] += (1 << al_vs);

      if (server.argName(i) == "alarm1") {
          tmp = urldecode( server.arg(i));
          tmp_h=tmp.substring(0,server.arg(i).indexOf(":"));
          tmp_m=tmp.substring(server.arg(i).indexOf(":")+1);
          tmp_h.toCharArray(Buf,3);
          config.alarm_param[0][0]=atoi(Buf);
          tmp_m.toCharArray(Buf,3);
          config.alarm_param[0][1]=atoi(Buf);
      }
      if (server.argName(i) == "alarm2") {
          tmp = urldecode( server.arg(i));
          tmp_h=tmp.substring(0,server.arg(i).indexOf(":"));
          tmp_m=tmp.substring(server.arg(i).indexOf(":")+1);
          tmp_h.toCharArray(Buf,3);
          config.alarm_param[1][0]=atoi(Buf);
          tmp_m.toCharArray(Buf,3);
          config.alarm_param[1][1]=atoi(Buf);
      }
      if (server.argName(i) == "alarm3") {
          tmp = urldecode( server.arg(i));
          tmp_h=tmp.substring(0,server.arg(i).indexOf(":"));
          tmp_m=tmp.substring(server.arg(i).indexOf(":")+1);
          tmp_h.toCharArray(Buf,3);
          config.alarm_param[2][0]=atoi(Buf);
          tmp_m.toCharArray(Buf,3);
          config.alarm_param[2][1]=atoi(Buf);
      }
      if (server.argName(i) == "alarm4") {
          tmp = urldecode( server.arg(i));
          tmp_h=tmp.substring(0,server.arg(i).indexOf(":"));
          tmp_m=tmp.substring(server.arg(i).indexOf(":")+1);
          tmp_h.toCharArray(Buf,3);
          config.alarm_param[3][0]=atoi(Buf);
          tmp_m.toCharArray(Buf,3);
          config.alarm_param[3][1]=atoi(Buf);
      }
      if (server.argName(i) == "alarm5") {
          tmp = urldecode( server.arg(i));
          tmp_h=tmp.substring(0,server.arg(i).indexOf(":"));
          tmp_m=tmp.substring(server.arg(i).indexOf(":")+1);
          tmp_h.toCharArray(Buf,3);
          config.alarm_param[4][0]=atoi(Buf);
          tmp_m.toCharArray(Buf,3);
          config.alarm_param[4][1]=atoi(Buf);
      }
      if (server.argName(i) == "alarm6") {
          tmp = urldecode( server.arg(i));
          tmp_h=tmp.substring(0,server.arg(i).indexOf(":"));
          tmp_m=tmp.substring(server.arg(i).indexOf(":")+1);
          tmp_h.toCharArray(Buf,3);
          config.alarm_param[5][0]=atoi(Buf);
          tmp_m.toCharArray(Buf,3);
          config.alarm_param[5][1]=atoi(Buf);
      }
      if (server.argName(i) == "alarm7") {
          tmp = urldecode( server.arg(i));
          tmp_h=tmp.substring(0,server.arg(i).indexOf(":"));
          tmp_m=tmp.substring(server.arg(i).indexOf(":")+1);
          tmp_h.toCharArray(Buf,3);
          config.alarm_param[6][0]=atoi(Buf);
          tmp_m.toCharArray(Buf,3);
          config.alarm_param[6][1]=atoi(Buf);
      }
      if (server.argName(i) == "alarm8") {
          tmp = urldecode( server.arg(i));
          tmp_h=tmp.substring(0,server.arg(i).indexOf(":"));
          tmp_m=tmp.substring(server.arg(i).indexOf(":")+1);
          tmp_h.toCharArray(Buf,3);
          config.alarm_param[7][0]=atoi(Buf);
          tmp_m.toCharArray(Buf,3);
          config.alarm_param[7][1]=atoi(Buf);
      }

      if (server.argName(i) == "snd1") config.alarm_param[0][3] = server.arg(i).toInt();
      if (server.argName(i) == "snd2") config.alarm_param[1][3] = server.arg(i).toInt();
      if (server.argName(i) == "snd3") config.alarm_param[2][3] = server.arg(i).toInt();
      if (server.argName(i) == "snd4") config.alarm_param[3][3] = server.arg(i).toInt();
      if (server.argName(i) == "snd5") config.alarm_param[4][3] = server.arg(i).toInt();
      if (server.argName(i) == "snd6") config.alarm_param[5][3] = server.arg(i).toInt();
      if (server.argName(i) == "snd7") config.alarm_param[6][3] = server.arg(i).toInt();
      if (server.argName(i) == "snd8") config.alarm_param[7][3] = server.arg(i).toInt();
     }
    WriteConfig();
    CheckAlarmSet();
   }
  server.send_P ( 200, "text/html", PAGE_AlertConfiguration ); 
#ifdef DEBUG  
  Serial.println(__FUNCTION__); 
#endif  
}
/**************************************************************************************************************************************************************************/
void send_alert_values_html()
{
  String values ="";     
  for (int i=0; i< 8; i++)
  {
    values += "alarm" + (String)(i+1) + "|" + (String) (config.alarm_param[i][0] < 10 ? "0" : "") + (String) config.alarm_param[i][0] + ":";
    values += (String) (config.alarm_param[i][1] < 10 ? "0" : "") + (String) config.alarm_param[i][1] + "|input\n";
    values += "alarm" + (String)(i+1) + "_en|" + (String) ((config.alarm_param[i][2] & (1 << al_en)) ? "checked" : "") + "|chk\n";
    values += "alarm" + (String)(i+1) + "_pn|" + (String) ((config.alarm_param[i][2] & (1 << al_pn)) ? "checked" : "") + "|chk\n";
    values += "alarm" + (String)(i+1) + "_vt|" + (String) ((config.alarm_param[i][2] & (1 << al_vt)) ? "checked" : "") + "|chk\n";
    values += "alarm" + (String)(i+1) + "_sr|" + (String) ((config.alarm_param[i][2] & (1 << al_sr)) ? "checked" : "") + "|chk\n";
    values += "alarm" + (String)(i+1) + "_ct|" + (String) ((config.alarm_param[i][2] & (1 << al_ct)) ? "checked" : "") + "|chk\n";
    values += "alarm" + (String)(i+1) + "_pt|" + (String) ((config.alarm_param[i][2] & (1 << al_pt)) ? "checked" : "") + "|chk\n";
    values += "alarm" + (String)(i+1) + "_sb|" + (String) ((config.alarm_param[i][2] & (1 << al_sb)) ? "checked" : "") + "|chk\n";
    values += "alarm" + (String)(i+1) + "_vs|" + (String) ((config.alarm_param[i][2] & (1 << al_vs)) ? "checked" : "") + "|chk\n";
    values += "snd" + (String)(i+1) + "|" + (String) (config.alarm_param[i][3]) + "|input\n";
  }
  
  server.send ( 200, "text/plain", values);
#ifdef DEBUG  
  Serial.println(__FUNCTION__); 
#endif  
}
/**************************************************************************************************************************************************************************/
#endif
