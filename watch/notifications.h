#pragma once

#ifndef WATCHDUINO_NOTIFICATIONS_H 
#define WATCHDUINO_NOTIFICATIONS_H

#include "watchcore.h"
#include "utils.h" 
#include "drawUtils.h"

class Notifications {
  private:
 
  public:
    Notifications() {

    }
    ~Notifications(){}
  
    boolean hasNotifications(){
      return notif.length() > 0;
    }
    void draw(){
      
          if (warning) display.drawXBMP(0,20,warning_width,warning_height, warning_img);
          else display.drawXBMP(0,20,message_width,message_height, message_img);
          
          if (notif.length() > MAX_MSG_SHORT) display.setFont(u8g_font_4x6r );
          drawLines(20,25, 100, notif.c_str());
          display.setFont(u8g_font_fixed_v0r);
        
          drawButton(SELECT_PIN, cancel_width, cancel_height,  (unsigned char*) cancel_img);
    }
    void controller(){
       if (pushedButton(SELECT_PIN)) {
         notif = "";
         bt.send(CM_NOTIF);
       }
    }

};

#endif

