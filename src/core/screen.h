#pragma once

#ifndef WATCHDUINO_SCREEN_H 
#define WATCHDUINO_SCREEN_H

#include "images.h"

class Screen
{
    protected:
        int refresh;
    public:
        unsigned char* icon;
        Screen(){
            refresh = 100;
            icon =   (unsigned char*)  twitter_img;
        }
        int getRefresh(){
            return refresh;
        }
        virtual ~Screen(){}
        virtual void draw() = 0;
        virtual void controller() = 0;
        virtual void update() = 0;
        virtual void enter() = 0;
        virtual void exit() = 0;
};


#endif
