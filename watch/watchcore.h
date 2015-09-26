#pragma once

#ifndef WATCHDUINO_CORE_H 
#define WATCHDUINO_CORE_H

//DEFINITIONS
#define SSD1306I2C_U8G
#define JEELIB_ENABLED //TODO Fix jeelib. if enabled bluetooth won't work, maybe we should use delay on bluetooth ?
#define BLUETOOTH 
#define VIBRATION 11
#define TOPBAR
#define DEBUG
#define BUZZERPIN  12
#define SELECT_SCREEN

#define MAX_MSG_SHORT 50


#include <Arduino.h>

#include "screen.h"

//#define PROTOTYPE

//CONTROLS
#ifdef PROTOTYPE
  #define UP_PIN 4
  #define DOWN_PIN 5
  #define SELECT_PIN 6
#else
  //ALTERNATIVE CONTROLS FOR ASSEMBLED PROTOTYPE
  #define UP_PIN 6
  #define DOWN_PIN 4
  #define SELECT_PIN 5
#endif


#define WAKE_PIN  2                // pin used for waking up

//SCREEN

#if defined(SSD1306I2C_U8G)  
  #define WIDTH  128
  #define STATUS_H 15
  #define HEIGHT  64
  
 #include <U8glib.h>
 extern U8GLIB_SSD1306_128X64 display;

#endif

extern SoftwareSerial bluetooth;
extern bool selectScreen;

//SETTINGS 
extern bool sleep;
extern bool sound;
extern int selectedSettings;

//TIMESET
extern long SECONDS_IN_DAY;
extern int selectedTimeSet;
extern long sleepStart  ;

//WEATHER
extern unsigned char* weatherImage;

//ALARM
extern boolean alarmEnabled;

//RESPONSE (Twitter, weather, tfl)
extern String response;

//NOTIF
extern String notif;
extern boolean warning;

//NOTIFICATIONS
//#include "notifications.h"
//extern Notifications notifications;
void selectScreenController();
void drawSelectScreen();
void changeScreen(int pos);
void vibrate(int times, int ms);
void customDelay(int ms);
void gameSound();
int main(void) ;
void checkSleep();
void controller();
void wakeUp();
void wakePressed();
void adjustTime();
void buzzer(int note);
void buzzer();
void printPowerDown();
void checkAlarm(const int alarm_melody[], const int alarm_melody_durations[], const int ALARM_SIZE);
void playAlarm(const int alarm_melody[], const int alarm_melody_durations[], const int ALARM_SIZE);

void sysinit();
void sysloop();
void clearDisplay();
void doDisplay();
void draw();
void drawSleep();
//EXTERN CLASSES 

//BLUETOOTH
#ifdef BLUETOOTH
  #include "bluetooth.h"
  extern Bluetooth bt;
#endif

#endif

