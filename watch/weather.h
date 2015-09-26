#pragma once

#ifndef WATCHDUINO_WEATHER_H
#define WATCHDUINO_WEATHER_H



#include "watchcore.h"

class Weather: public Screen {
    private:
      long lastRequest;
    public:
    Weather() {
        refresh = 1000;
        icon = (unsigned char*)  weather_img;
    }
    ~Weather(){}
    void draw(){

        display.drawXBMP(0,20, weather_width,weather_height, weather_img);

         drawLines(20,25, 100, response.c_str());

        drawButton(SELECT_PIN, refresh_width,refresh_height, (unsigned char*) refresh_img);
    }
    void controller(){}
    void update(){
      if (pressedButton(SELECT_PIN) && (millis() - lastRequest > 3000)) enter();
    }
    void enter() {
      lastRequest = millis();
      bt.send(CM_WEATHER);
      response = EMPTY;
    }
    void exit() {
      response = EMPTY;
    }
};

#endif
