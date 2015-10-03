#pragma once

#ifndef WATCHDUINO_WATCH_H 
#define WATCHDUINO_WATCH_H

#include "watchcore.h"

#define ANALOG_RAD 23
#define ANALOG_X 80
#define ANALOG_Y 40

class Watch: public Screen {
    private:
      unsigned short watchType ;
    public:
    Watch() {
        icon =  (unsigned char*)  watch_img;
        watchType = 0;
        refresh = 100;
    }
    ~Watch(){}
    
    void drawDigital(){
     
        display.setPrintPos(70,30); 
        display.print(day());
        display.print('/');
        display.print(month());
        
        //list of availablable fonts https://code.google.com/p/u8glib/wiki/fontsize
        display.setPrintPos(0,30); 
        
        display.setScale2x2();//display.setTextSize(2);
        display2digits(hour());
        display.print(':');
        display2digits(minute());
        
        display.setPrintPos(70,58); 
        display.undoScale(); //display.setTextSize(1);
        display.print(':');
        display2digits(second()  );
    }
    
    void drawAnalog(){
        display.setPrintPos(0,50); 
        display.print(day());
        display.print('/');
        display.print(month());
        
       display.drawCircle(ANALOG_X, ANALOG_Y, ANALOG_RAD);
       
       // DRaw seconds
       int r = clock60ToDeg(second());
       int x = degToClockX(r, ANALOG_RAD-2);
       int y = degToClockY(r, ANALOG_RAD-2);
       display.drawLine(ANALOG_X, ANALOG_Y, ANALOG_X + x, ANALOG_Y - y);
       
       r = clock60ToDeg(minute());
       x = degToClockX(r, ANALOG_RAD-4);
       y = degToClockY(r, ANALOG_RAD-4);
       display.drawLine(ANALOG_X, ANALOG_Y, ANALOG_X + x, ANALOG_Y - y);
       
       r = clock12ToDeg(hour());
       x = degToClockX(r, ANALOG_RAD-6);
       y = degToClockY(r, ANALOG_RAD-6);
       display.drawLine(ANALOG_X, ANALOG_Y, ANALOG_X + x, ANALOG_Y - y);
    }
    
    void draw(){
      
      //display.setFont(u8g_font_timR10);
      display.setPrintPos(0,30); 
        display.print(dayStr(weekday()) );
        
        switch (watchType){
           case 0: drawDigital(); break; 
           case 1: drawAnalog(); break;
        }
        
        drawButton(SELECT_PIN, refresh_width,refresh_height, (unsigned char*) refresh_img);
        drawButton(DOWN_PIN, watch_width,watch_height, (unsigned char*) watch_img);

    }
    void controller(){
      if (pushedButton(SELECT_PIN)) bt.adjustTime();
      if (pushedButton(UP_PIN) || pushedButton(DOWN_PIN) )  watchType = (watchType +1) %2;
    }
    void update(){}
    void enter() {}
    void exit() {}
};

#endif
