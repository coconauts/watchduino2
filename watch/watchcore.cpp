#include <SoftwareSerial.h>// import the serial library


#include "watchcore.h"

#ifdef JEELIB_ENABLED
  #include <JeeLib.h> 
  ISR(WDT_vect) { Sleepy::watchdogEvent(); }
#endif

#include "notes.h"
#include "images.h"
#include "utils.h"

//Screens
#include "screen.h" //abstract class
#include "settings.h"
#include "alarmSet.h" 
#include "watch.h"
#include "weather.h"
#include "twitter.h"
#include "top10.h"
#include "tfl.h"

//SYSTEM
#include "topbar.h"
#include "selectScreen.h"
#include "notifications.h"
#include "alarmSet.h"

//SLEEP VARIABLES
bool isSleep = false;
long sleepStart = 0;                   // counter
#define AWAKE_TIME 30000 //every 30 seconds
#define SLEEP_TIME 60000
//SOUND VARIABLES

short NOTE_DURATION = 1000 / 4; //a quarter
#define DELAY_BETWEEN_NOTES 1000 //ms
#define SECONDS_IN_DAY 86400

//SCREEN VARIABLES
#if defined(SSD1306I2C_U8G)  
  #define OLED_SDA 4
  U8GLIB_SSD1306_128X64 display = U8GLIB_SSD1306_128X64(OLED_SDA);
#endif

int screen = 0; 

//TIMESET
int selectedTimeSet = 0;

//SETTINGS 
bool sleep = true;
bool sound = true;
int selectedSettings = 0;
int fixTime = 0;

boolean alarmEnabled = false;
String weather = "";
unsigned char* weatherImage ;
String response = "";
String notif = "";
boolean warning = false;
Notifications notifications = Notifications();
Alarm alarm = Alarm();

#ifdef BLUETOOTH
  #include <SoftwareSerial.h>// import the serial library
  #define BT_RX 10
  #define BT_TX 9
  SoftwareSerial bluetooth(BT_TX, BT_RX); 
  Bluetooth bt = Bluetooth(); //Bluetooth initialization
#endif

int screensSize = 6 ;
Screen *screens[] = { 
      //new Pong(),
      //new Test(),
      new Watch(),
      new Weather(),
      new Twitter(),
      new Top10(),
      new Tfl(),
      new Settings(),
     /* new TimeSet(),
//    new Snake(),
//    new Pong(),
     ,
      new AlarmSet()*/
};
bool selectScreen = false;
int newScreen = 0;

#ifdef TOPBAR
  Topbar topbar = Topbar();
#endif

#ifdef VIBRATION
  bool vibrationEnabled = true;
  long vibrationStart = 0;
  int vibrationDuration = 0;
  int vibrationTimes =0 ;
  bool vibrationActive = true;
#endif

long lastBatMsg = 0;
#define SEND_BAT_TIME 300000 //Send battery status every 5 mins
#define LOW_BAT 3500


void sysinit(){
  
    display.setFont(u8g_font_fixed_v0r); //list of availablable fonts https://code.google.com/p/u8glib/wiki/fontsize
    //4x10r //normal
    //4x6r //tiny
    //micro //tiniest
    
    pinMode(WAKE_PIN, INPUT); digitalWrite(WAKE_PIN,HIGH);   // attachInterrupt(0, wakePressed, LOW);
    pinMode(UP_PIN, INPUT); digitalWrite(UP_PIN,HIGH);
    pinMode(DOWN_PIN, INPUT);digitalWrite(DOWN_PIN,HIGH);
    pinMode(SELECT_PIN, INPUT); digitalWrite(SELECT_PIN,HIGH);
        
    #ifdef VIBRATION
      pinMode(VIBRATION,OUTPUT);
    #endif

    bt.sendATCommand("AT");
    bt.sendATCommand("AT+PWRM0");
    bt.sendATCommand("AT+NAMEWatchDuino"); 
    bt.sendATCommand("AT+RESET"); 
              
    bt.adjustTime();
     
    wakeUp() ;
    vibrate(1,100);
    buzzer();
    setTime(0,0,0,0,0,0);
    
    delay(100); screens[screen]->enter();
    
    #ifdef DEBUG
      Serial.begin(4800);
      Serial.println(F("Serial ready on 4800, comment DEBUG at watchcore.h to disable"));
    #endif 
      
}

void sysloop() {
           
        if (lastBatMsg + SEND_BAT_TIME < millis() ) {
          lastBatMsg = millis();
          bt.send(CM_BAT, readVcc());
        }

        #ifdef BLUETOOTH
            if (bt.enabled){
              bt.update();
              if (bt.receiving) return; //skip delay
            }
        #endif
        
        controller();
        checkSleep();
       
        if( isSleep ) drawSleep();
        else draw();
        
        if (alarmEnabled) {
          alarm.controller();
          alarm.update();
        }
        else if (notifications.hasNotifications() ) notifications.controller();
        else if (selectScreen) selectScreenController();
        else screens[screen]->controller();
        
        screens[screen]->update();
        
        //TODO
        //checkAlarm(alarm_melody, alarm_durations, ALARM_SIZE);
        if (minute() == 59 && second() == 0)  bt.adjustTime();
        
         #ifdef VIBRATION
          if (vibrationEnabled && vibrationActive && vibrationStart + vibrationDuration < millis()){
               digitalWrite(VIBRATION, LOW);
               vibrationActive = false;
          }
          
          //Wait between vibrations
          if (vibrationTimes > 1 && !vibrationActive && vibrationStart + vibrationDuration*2 < millis() ) vibrate(vibrationTimes-1, vibrationDuration);
        #endif
     /*
     //TODO enable delay
     if (isAlarmSounding()) customDelay(100); 
        else if (screen < screensSize) customDelay(screens[screen]->getRefresh()); 
        else customDelay(1000);
       */
        //customDelay(500);
       //buzzer(1); 
}

void vibrate(int times, int ms){
  
  #ifdef VIBRATION
    digitalWrite(VIBRATION, HIGH);
    vibrationStart = millis();
    vibrationDuration = ms;
    vibrationTimes = times;
    vibrationActive = true;
  #endif
}

void draw(){
  
    display.firstPage();  
    do {
      
      #ifdef TOPBAR
        topbar.draw();
      #endif    
      
      #ifdef SELECT_SCREEN
        if (selectScreen) drawSelectScreen();
        else {
          if (alarmEnabled) alarm.draw();
          else if (notifications.hasNotifications() )  notifications.draw();
          else screens[screen]->draw();
        }
      #else
      
        if (notifications.hasNotifications() )  notifications.draw();
        else screens[screen]->draw();
      #endif
    } while( display.nextPage() );       
}

boolean lowBattery(){
  return readVcc() < LOW_BAT;
}

void drawSleep(){
  
  display.firstPage();  
  do {
    if (notifications.hasNotifications()) display.drawXBMP(15, 2, message_width,message_height,message_img);
    //if (bt.enabled) display.drawXBMP(0, 0, bluetooth_width,bluetooth_height,bluetooth_img);
    if (lowBattery()) topbar.printBarBattery();
    drawTime(WIDTH/2 - 15,HEIGHT/2, ':');
  } while( display.nextPage() );       
  
}
void customDelay(int ms){
  #ifdef JEELIB_ENABLED
    Sleepy::loseSomeTime(ms); 
  #else
    delay(ms);
  #endif
}

void checkSleep(){
    if (sleep && (sleepStart + AWAKE_TIME) < millis()) { 
              
            //GO to sleep
            isSleep = true;
           // bt.send(CM_SLEEP);
            
            attachInterrupt(0, wakePressed, LOW);
                        
            #ifdef VIBRATION  
              digitalWrite(VIBRATION, LOW);      //JUst in case
            #endif
            
            bt.sleep();
            
            drawSleep();
            
            selectScreen = false;
                        
            long beforeSleep;
            /*if (alarmEnabled) customDelay((alarm - now())*1000);
            else */
            while ( isSleep) {
              #ifdef DEBUG
                Serial.println(F("Sleeping"));
              #endif

              delay(10);
              beforeSleep = millis();
              customDelay(SLEEP_TIME);
              delay(10);
              
              #ifdef DEBUG
                Serial.print(F("Awaking after "));
                Serial.print(millis() - beforeSleep);
                Serial.println(F(" seconds"));
              #endif 
              
              bt.update();
                          
              drawSleep();
              
            }

            bt.awake();
            
            //if (bt.sleep)  bt.enable();
            
            #ifdef DEBUG
              Serial.print(F("Awaking after "));
              Serial.print(millis() - beforeSleep);
              Serial.println(F(" seconds"));
            #endif 
            
            //bt.send(CM_AWAKE); //Unlikely to arrive
            detachInterrupt(0);
            wakeUp();
            
            //This sleepStart hack will force the watch to sleep again in 1 second, 
            //but it will give it some space to process incoming messages via Bluetooth
            //if (isSleep) sleepStart = millis() - AWAKE_TIME + BT_CHECK ;
    }
}

#define ICON_SIZE 10
#define BOX_SIZE 14
#define SELECT_X 23
#define SELECT_Y 35

void drawSelectScreen(){

  for (int i=0; i < screensSize; i++){
      int x = SELECT_X+(BOX_SIZE)*i;
      
      //TODO Draw inverted bitmpa for selected screen //drawInvXBM(x+2, 20+2, ICON_SIZE, ICON_SIZE,  screens[i]->icon);
      if (i==newScreen) display.drawFrame(x, SELECT_Y, BOX_SIZE,BOX_SIZE);
      //display.drawFrame(x, 20, BOX_SIZE,BOX_SIZE );
      display.drawXBMP(x+2, SELECT_Y+2, ICON_SIZE, ICON_SIZE,  screens[i]->icon);
      
      if (newScreen > 0) drawButton(UP_PIN, left_width,right_height, (unsigned char*) left_img);
      if (newScreen < screensSize-1) drawButton(DOWN_PIN, left_width,right_height,  (unsigned char*) right_img);
      drawButton(SELECT_PIN, confirm_width,confirm_height,  (unsigned char*) confirm_img);
      drawButton(WAKE_PIN, cancel_width,cancel_height,  (unsigned char*) cancel_img);
  }
}

void changeScreen(){
   #ifdef SELECT_SCREEN
      selectScreen = true;
      newScreen = screen;
   #else
      changeScreen(screen+1);
   #endif
}

void changeScreen(int pos){
  
  screens[screen]->exit();
  screen = pos % screensSize;
  screens[screen]->enter();
}

void controller(){
   
    if (pressedButton(SELECT_PIN) ||
        pressedButton(UP_PIN) ||
        pressedButton(DOWN_PIN)) {
        wakeUp() ;  //Refresh sleep time
        //if (isAlarmSounding()) alarm_active = false;
        
    } else if (pushedButton(WAKE_PIN)) {

        if (selectScreen) selectScreen =false;
        else changeScreen();
        wakeUp() ;
    }    
   
}
void selectScreenController(){
  
  #ifdef SELECT_SCREEN
     if (selectScreen)  {
       if (pushedButton(SELECT_PIN)) {
         changeScreen(newScreen);
         selectScreen = false;
       } 
       if (pushedButton(UP_PIN) ) newScreen= (newScreen+1)% screensSize;
       if (pushedButton(DOWN_PIN) ) {
         newScreen= newScreen-1;
         if (newScreen <0) newScreen = screensSize-1;
       }
      
     }
   #endif
}

void wakeUp() {

  isSleep = false;
  sleepStart = millis() ;
}
void wakePressed() {
  wakeUp();
}

void buzzer(int note){
     if (sound) {
         tone(BUZZERPIN, note, NOTE_DURATION);
         //delay(10);
         //noTone(BUZZERPIN);
     }
}

void buzzer(){
     buzzer(NOTE_C4);
}










