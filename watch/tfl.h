#pragma once

#ifndef WATCHDUINO_TFL_H 
#define WATCHDUINO_TFL_H 

#include "watchcore.h"

#define tfl_width 10
#define tfl_height 10
static const unsigned char tfl_img[] PROGMEM = {
   0xfc, 0x00, 0xce, 0x01, 0xff, 0x03, 0x03, 0x03, 0x01, 0x02, 0x01, 0x02,
   0xff, 0x03, 0xfd, 0x02, 0xff, 0x03, 0x86, 0x01 };

class Tfl: public Screen {
  
    private:
      int count;   
      long lastRequest;
    public:
    Tfl() {
        icon =  (unsigned char*) tfl_img;
        refresh = 1000;
        count = 0;
    }
    ~Tfl(){}
    void draw(){
         
        display.drawXBMP(0,20, tfl_width,tfl_height, tfl_img);

        display.setFont(u8g_font_4x6r );
        drawLines(20,25, 100, response.c_str());
        display.setFont(u8g_font_fixed_v0r);
        
        if (count != 0) drawButton(UP_PIN, left_width,right_height, (unsigned char*) left_img);
        drawButton(DOWN_PIN, left_width,right_height, (unsigned char*) right_img);
        drawButton(SELECT_PIN, refresh_width,refresh_height,  (unsigned char*)refresh_img);
        
    }
    void controller(){}
    void update(){      
      
      if (pressedButton(SELECT_PIN) && (millis() - lastRequest > 3000)) enter();
      else if (pushedButton(UP_PIN) ) {
         count++;
         wakeUp() ;
         bt.send(CM_TFL, count);
       }
      else if (pushedButton(DOWN_PIN) ) {
         count--;
         wakeUp() ;
         if (count < 0) count = 0;
         bt.send(CM_TFL, count);
       }
    }
    void enter() {
      lastRequest = millis();
      wakeUp() ;
      count= 0;
      bt.send(CM_TFL);
      
    }
    void exit() {
      response = "";
    }
};

#endif
