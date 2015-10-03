#pragma once

#ifndef WATCHDUINO_SELECT_SCREEN_H 
#define WATCHDUINO_SELECT_SCREEN_H 

#define ICON_SIZE 10
#define BOX_SIZE 14

#include "watchcore.h"
#include "screen.h" //abstract class
class SelectScreen {

    private: 

    public:
      int selected;
      bool enabled;
      SelectScreen( ) {
        enabled = false;
      }
      ~SelectScreen(){}
      void draw(){
        
      }
      void controller(){
        if (pressedButton(SELECT_PIN)) enabled = false;
        else if (pushedButton(UP_PIN) ) { selected++; }
        else if (pushedButton(DOWN_PIN) ) { selected--; }
      }
};

#endif
