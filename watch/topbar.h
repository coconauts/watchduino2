#pragma once

#ifndef WATCHDUINO_TOPBAR_H 
#define WATCHDUINO_TOPBAR_H 

#include "watchcore.h"

class Topbar {
    private:
      void printBarTime(){
         // display.setCursor(54,0); 
      
          char separator = '.';
          if (second() % 2 == 0 ) separator = ':';
          
          drawTime(WIDTH-30,10, separator);
         
          //display.println(getDigit(hour())+separator+getDigit(minute()));  
          //display.drawRoundRect(52,-1,50,10,2 , BLACK);
      }

    public:      
      void printBarBattery(){
          //3300 is the minimum battery (bat = 0%)
          //4000 (3300 + 700) is the maximum (bat = 100%)
          //(vcc - 3300 ) * 100 / 700 = (vcc - 3300) / 7
          //We divide by 10 to get a number between 0 an 10
          int bat = (int) (readVcc() - 3300)/70;
      
          //battery case
          display.drawFrame(WIDTH-44, 3, 10, 7);
          //battery nipple
          display.drawFrame(WIDTH-35, 4, 3, 5);
          //fill
          display.drawBox(WIDTH-44, 3, max(0,min(bat,10)), 7); 
            
    }

    Topbar() {}
    ~Topbar(){}
    void draw(){
      
      #ifdef BLUETOOTH
        if (bt.enabled) display.drawXBMP(0, 0, bluetooth_width,bluetooth_height,bluetooth_img);
      #endif
      
      //DEBUG
      display.setPrintPos(15,10); 
      display.print(freeRam());
      //display.print(" ");
      //display.print(sleepStart / 1000);
      
      printBarTime();
      printBarBattery();
      //if (alarmEnabled) display.drawBitmap(0, 0 , sound_width,sound_height,sound_img);
      
      //Separator line
      display.drawHLine(0,STATUS_H,WIDTH);
    }
};

#endif
