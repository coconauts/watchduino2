#pragma once

#ifndef WATCHDUINO_TWITTER_H
#define WATCHDUINO_TWITTER_H

#include "watchcore.h"

class Twitter: public Screen {

    private:
      int count;
    public:
    Twitter() {
        icon =  (unsigned char*)  twitter_img;
        refresh = 1000;
        count = 0;
    }
    ~Twitter(){}
    void draw(){

        display.drawXBMP(0,20, twitter_width,twitter_height, twitter_img);

         if (response.length() > MAX_MSG_SHORT) display.setFont(u8g_font_4x6r );
        drawLines(20,25, 100, response.c_str());
        display.setFont(u8g_font_fixed_v0r);

        if (count != 0) drawButton(UP_PIN, left_width,right_height, (unsigned char*) left_img);
        drawButton(DOWN_PIN, left_width,right_height, (unsigned char*) right_img);
        drawButton(SELECT_PIN, refresh_width,refresh_height, (unsigned char*)refresh_img);

    }
    void controller(){}
    void update(){
      if (pressedButton(SELECT_PIN)) enter();
      else if (pushedButton(UP_PIN) ) {
         count++;
         bt.send(CM_TWITTER, count);
       }
      else if (pushedButton(DOWN_PIN) ) {
         count--;
         if (count < 0) count = 0;
         bt.send(CM_TWITTER, count);
       }
    }
    void enter() {
      count= 0;
      bt.send(CM_TWITTER, 0);

    }
    void exit() {
      response = "";
    }
};

#endif
