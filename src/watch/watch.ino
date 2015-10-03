//DEPENDENCIES
#include <Wire.h>
#include <SPI.h>

#include <U8glib.h> // Documentation : https://code.google.com/p/u8glib/wiki/userreference
#include <Time.h> // Source : http://www.pjrc.com/teensy/td_libs_Time.html
                    // Example code : http://playground.arduino.cc//Code/Time?action=sourceblock&num=7
#include <JeeLib.h> // Source: https://github.com/jcw/jeelib
                     // Example code: http://hwstartup.wordpress.com/2013/03/11/how-to-run-an-arduino-on-a-9v-battery-for-weeks-or-months/
                     // powerDown example code: http://hwstartup.wordpress.com/2013/04/15/how-to-run-an-arduino-clone-on-aa-batteries-for-over-a-year-part-2/

#include <SoftwareSerial.h>
#include <watchcore.h>
/*int main(void) {
   init(); // don't forget this!
   sysinit(); 
   
   while (1) sysloop();
}*/

void setup(){
  sysinit();
}

void loop(){
  sysloop();
}

