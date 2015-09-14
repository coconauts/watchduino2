#pragma once

#ifndef BLUETOOTH_WATCH_H 
#define BLUETOOTH_WATCH_H

#include <Time.h>   
#include "watchcore.h"
#include "notes.h"

//COMMANDS
//TODO PROGMEM this
const char CM_TIME[] = "!tm" ;
const char CM_WEATHER[] = "!wt" ;
const char CM_WEATHER_IMAGE[] = "!wi" ;
const char CM_PING[] = "!pg" ;
const char CM_NOTIF[] = "!nt" ;
const char CM_ERROR[] = "!er" ;
const char CM_TWITTER[] = "!tw" ;
const char CM_SLEEP[] = "!sl" ;
const char CM_AWAKE[] = "!aw" ;
const char CM_DEBUG[] = "!db" ;
const char CM_BAT[] = "!bt";
const char CM_AT[] = "!at";
const char CM_TOP10[] = "!t1";
const char CM_TFL[] = "!tf";
const char CM_ALARM[] = "!al";
const char CM_SETTINGS[] = "!st";
const char CM_WARNING[] = "!wr";

#define BLUETOOTH_DELAY  50

class Bluetooth {

  public:
  
    bool sleepEnabled;
    bool enabled;
    bool receiving;
    
    Bluetooth() {
      
      bluetooth.begin(9600);
          
      buffer = "";     
      enabled = true;    
      sleepEnabled = false;  
      
      //bluetooth.print("AT+PWRM0");
      //bluetooth.print("AT+IMME1");
      //bluetooth.print("AT+ROLE1");

      //sendATCommand("AT+PWRM0");
      //sendATCommand("AT+NAMEWatchduino"); 
      //sendATCommand("AT+RESET"); 

    }
    ~Bluetooth(){
    }

  //Dangerous
  void sendATCommand(String str){

    bool atResponse = false;
    while(!atResponse) {

      bluetooth.print(str); 
      delay(BLUETOOTH_DELAY);
      while(bluetooth.available()){
        atResponse = true;
        bluetooth.read();
      }
    }
  }
  void sleep(){

    send(CM_SLEEP);

     sendATCommand("AT"); 
     sendATCommand("AT+SLEEP"); 
     //sendATCommand("AT+NAMEWatchZ");
     //sendATCommand("AT+RESET"); 

  }
  void awake() {
    
     /*sendATCommand("AT"); 
     sendATCommand("AT+NAMEWatchDuino");
     sendATCommand("AT+RESET"); */
  }
 
    void send(String m){
      
      bluetooth.println(m+'\r');
       delay(BLUETOOTH_DELAY);
    } 
    void send(String command, String v){
      
      bluetooth.println(command + ':'+v+'\r');
       delay(BLUETOOTH_DELAY);
    } 
    void send(String command, int v){
      
      bluetooth.print(command + ':');
      bluetooth.print(v);
      bluetooth.println('\r');
      delay(BLUETOOTH_DELAY);
    } 
  
    void update(){
      if (enabled) listen();
    }
    
    void adjustTime(){
        send(CM_TIME);
    }
    
  private: 
  
    String buffer;
    char data;
    
    long lastReceived ;
        
    void getImg(unsigned char* &img, String s){
      
      int len = s.length();
      img = (unsigned char*) new char [ len]; 
      memcpy(img, s.c_str(), len);
      
    }

    void processMessage(){

      //send(CM_DEBUG, buffer);

        #ifdef DEBUG
              Serial.print(F("Full message "));
              Serial.println(buffer);
          #endif
          
      if (buffer.startsWith(CM_PING)) {
        send(CM_PING);
      } else if (buffer.startsWith(CM_TIME)) {
        buffer.remove(0,4);
        setTime(buffer.toInt());
      } else if (buffer.startsWith(CM_ALARM)) {
        alarmEnabled = true;
      } else if (buffer.startsWith(CM_WEATHER)) {
        weather = buffer;
        weather.remove(0,4);
      } else if (buffer.startsWith(CM_SETTINGS) ){
        //TODO dynamic settings 
      }
      //else if (buffer.startsWith(CM_WEATHER_IMAGE)) getImg(weatherImage, buffer.substring(4));
      else if (buffer.startsWith(CM_NOTIF) || buffer.startsWith(CM_WARNING)) {
        wakeUp();
        
        warning = buffer.startsWith(CM_WARNING);
        selectScreen =false;
        notif = buffer;
        notif.remove(0,4);
        vibrate(1,100);
        if (warning) buzzer(NOTE_C3);
        else buzzer(); 
      } else if (buffer.startsWith(CM_TWITTER)) {
        response = buffer;
         response.remove(0,4);

      } /*else if (buffer.startsWith("AT")) {
        int i = 0;
        char c = 0;
        //Enter AT mode
        enterATMode();
        while (i < buffer.length() && c != 13){
           
             c = buffer.charAt(i) ;
             bluetooth.write(c);
             i++;
         }
      } else if (buffer.startsWith("OK")) {
        ; //Bluetooth AT response
      } */ else if (buffer.startsWith(CM_TOP10)) {
         response = buffer;
         response.remove(0,4);
      } else if (buffer.startsWith(CM_TFL)) {
         response = buffer;
         response.remove(0,4);
      } else if (buffer.startsWith(CM_DEBUG))  {
        //send(CM_DEBUG, buffer); 
      } else if (buffer.startsWith(CM_AT)) {
        buffer.remove(0,4);
        bluetooth.print(buffer);
      } else send(CM_ERROR, buffer); //Unrecognized message
     
      buffer = "";
      receiving = false;
      
    }
    void listen(){
          
      #ifdef DEBUG
      //Send messages to bluetooth module through Monitor Serial ( 4800 baud)
        while (Serial.available()) {
           char c = Serial.read();
           bluetooth.write(c);
        }
      #endif
            
      if(bluetooth.available()){

        enabled = true;
        data=bluetooth.read();

        wakeUp();
        
         #ifdef DEBUG
              Serial.print(F("Received bluetooth "));
              Serial.println(data);
          #endif
         /*#ifdef DEBUG
          Serial.print(data);
        #endif*/
      
        switch(data) {
          //13: \r
        case 13:  
          //Returning responses
          processMessage();
  
          break; //end message
        default: 
           
          lastReceived = millis() ;
          receiving = true;
          buffer.concat(data);
          
        }
       
      }
      //Timeout
      if(receiving && lastReceived + 5000 < millis() ){
          send(CM_ERROR, buffer);
          processMessage();
      }
    }
};

#endif

