#pragma once

#ifndef WATCHDUINO_SETTINGS_H
#define WATCHDUINO_SETTINGS_H

#include "watchcore.h"
#include "utils.h"

#define MAX_SETTINGS 4

class Settings: public Screen
{
  public:
    Settings(){
      icon =  (unsigned char*)  gear_img;
    }
    ~Settings(){}
    void draw(){
        display.drawXBMP(0, selectedSettings*10 + 20, right_width, right_height, right_img);

        //SELECTED SETTING 0
        display.setPrintPos(10,25); display.println(F("Sleep: "));
        if (sleep) display.println(F("yes"));
        else display.println(F("no"));

        //SELECTED SETTING 1
        display.setPrintPos(10,35);  display.println(F("Sound: "));
        if (sound) display.print(F("yes"));
        else display.print(F("no"));

        //SELECTED SETTING 2
        display.setPrintPos(10,45);  display.print(F("Bluetooth: "));
        if (bt.enabled) display.print(F("yes"));
        else display.print(F("no"));

        //SELECTED SETTING 3
        display.setPrintPos(10,55);  display.print(F("Sleep bluetooth: "));
        if (bt.sleepEnabled) display.print(F("yes"));
        else display.print(F("no"));
    }
    void controller(){
        if (pushedButton(SELECT_PIN))  {
            switch(selectedSettings){
              case 0: sleep = !sleep; break;
              case 1: sound = !sound ;break;
              case 2: bt.enabled = !bt.enabled; break;
              case 3: bt.sleepEnabled = !bt.sleepEnabled; break;
            }
        }
        if (pushedButton(UP_PIN) ) selectedSettings = (selectedSettings+1) %MAX_SETTINGS;
        if (pushedButton(DOWN_PIN) ) {
          selectedSettings-=1;
          if (selectedSettings <0) selectedSettings = MAX_SETTINGS-1;
        }

    }
    void update(){ }
    void enter(){}
    void exit(){}
};

#endif
