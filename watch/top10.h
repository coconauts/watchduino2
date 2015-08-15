#pragma once

#ifndef WATCHDUINO_TOP10_H 
#define WATCHDUINO_TOP10_H 

#include "watchcore.h"

#define top10_width 10
#define top10_height 10
static const unsigned char top10_img[] PROGMEM = {
   0xc4, 0x00, 0xe6, 0x01, 0x27, 0x03, 0x07, 0x03, 0x36, 0x03, 0x36, 0x03,
   0x36, 0x03, 0x36, 0x03, 0xe6, 0x01, 0xc6, 0x00 };

class Top10: public Screen {
  
    private:
      int count;
    public:
    Top10() {
        icon =  (unsigned char*) top10_img;
        refresh = 1000;
        count = 0;
    }
    ~Top10(){}
    void draw(){
         
        display.drawXBMP(0,20, top10_width,top10_height, top10_img);

         display.setFont(u8g_font_4x6r );
        drawLines(20,25, 100, response.c_str());
        display.setFont(u8g_font_fixed_v0r);
        
        if (count > 0) drawButton(UP_PIN, left_width,right_height, (unsigned char*) left_img);
        else drawButton(UP_PIN, refresh_width,refresh_height, (unsigned char*) refresh_img);
        drawButton(DOWN_PIN, left_width,right_height, (unsigned char*) right_img);
        drawButton(SELECT_PIN, confirm_width,confirm_height, (unsigned char*)confirm_img);
        
    }
    void controller(){}
    void update(){      
      if (pressedButton(SELECT_PIN)) {
         bt.send(CM_TOP10);
      }
      else if (pushedButton(UP_PIN) ) {
         count++;
         wakeUp() ;
         bt.send(CM_TOP10, count);
       }
      else if (pushedButton(DOWN_PIN) ) {
         count--;
         wakeUp() ;
         if (count < -1) count = -1;
         bt.send(CM_TOP10, count);
       }
    }
    void enter() {
      count= 0;
      wakeUp() ;
      bt.send(CM_TOP10, -1);
      
    }
    void exit() {
      response = "";
    }
};

#endif
