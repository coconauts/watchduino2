#pragma once

#ifndef WATCHDUINO_UTILS_H
#define WATCHDUINO_UTILS_H 

bool wasPushed[13];

bool pressedButton(int pin){
    return digitalRead(pin) == LOW;
}

bool pushedButton(int pin){
    if (digitalRead(pin) == LOW){
        if (!wasPushed[pin]){
            wasPushed[pin] = true;
            return true;
        }
        return false;
    } else {
        wasPushed[pin] = false;
        return false;
    }
}

float rad (int degree){
    return degree* (3.1416/180);
}

int clock12ToDeg(int clockVal) {
    if (clockVal >= 12) clockVal = clockVal-12; 
    return  90 - (30 * clockVal);
}

int clock60ToDeg(int clockVal){
    if (clockVal >= 60) clockVal = clockVal-60; 
    return  90 - (6 * clockVal);
}

int degToClockX(int degree, int r){
    return  r * cos(rad(degree));
}

int degToClockY(int degree, int r){
    return  r * sin(rad(degree));
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  
 
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring
 
  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both
 
  long result = (high<<8) | low;
 
  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}
#endif
