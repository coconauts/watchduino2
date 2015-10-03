#pragma once

#ifndef WATCHDUINO_ALARM_H 
#define WATCHDUINO_ALARM_H

#include "watchcore.h"
#include "drawUtils.h"
#include "notes.h"
/*
int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4, 0 }; //add silence to the end
int noteDurations[] = {4, 8, 8, 4,4,4,4,4, 8 };
int notes = 9;*/
 int melody[] = {  NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_G4, NOTE_A4, NOTE_B4 , NOTE_A4, NOTE_B4, 0};
 int noteDurations[] = { 8,8,8, 4,4,4, 6, 4, 8, 4 };
 int notes = 10;

class Alarm: public Screen {
    private: 
    
    int notePos;
    long lastNotePlayed ;
    
    //Async
    void playAlarm(){

      if (notePos == 0) vibrate(1,100);
      
      if (millis() > lastNotePlayed ) { 
        noTone(BUZZERPIN);
        
         int noteDuration = 1000/noteDurations[notePos];
         tone(BUZZERPIN, melody[notePos],noteDuration);
         
         lastNotePlayed = millis() + noteDuration ;
          
          notePos++;
          if (notePos > notes -1) notePos =0;
      }
    }
    void dismiss(){
      alarmEnabled = false;
    }
    public:
        
    Alarm(){
      lastNotePlayed = 0;
      notePos = 0;
      }
    ~Alarm(){}
    void draw() {}
 
    void controller(){
        if (pressedButton(UP_PIN) || pressedButton(DOWN_PIN) || pushedButton(SELECT_PIN)){
            dismiss();
        } 
    }
    void update(){
      
        playAlarm();
    }
    void enter() {}
    void exit() {}
    
};


#endif
