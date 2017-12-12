#ifndef PAGE_REMCTRL_H
#define PAGE_REMCTRL_H

#include "WIFI_Clock.h"
/**************************************************************************************************************************************************************************/
const char PAGE_RemCTRL[] PROGMEM =  R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
)=====";

/**************************************************************************************************************************************************************************/
void send_remctrl_html()
{ uint8_t fun=0;
  uint8_t num=0; 
  if (server.args() > 0 )  // Save Settings
  { for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "fun") fun = urldecode(server.arg(i)).toInt(); 
      if (server.argName(i) == "num") num = urldecode(server.arg(i)).toInt();
    }
  }

Serial.print ("Remote control. Function: "); Serial.print(fun); Serial.print(" Number: "); Serial.println (num);

  switch (fun) {
    case FAlertStop:
        DoAlert(false,0);
        break;
    case FAlertPlay:
        DoAlert(true,CheckAlertMaxNum(num));
        break;    
  };

  server.send_P ( 200, "text/html", PAGE_RemCTRL ); 
  #ifdef DEBUG  
    Serial.println(__FUNCTION__); 
  #endif

}
#endif


