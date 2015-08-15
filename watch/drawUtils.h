#pragma once

#ifndef WATCHDUINO_DRAWUTILS_H
#define WATCHDUINO_DRAWUTILS_H 
void display2digits(int d){
  if (d<10) display.print('0');
  display.print(d);  
}

void drawLines(int x, int y, int w, const char* str){
    int origx = x;
    int vspace = display.getFontLineSpacing();
    int hspace =  display.getStrWidth("A");
    int screen_width = display.getWidth();
    char c ;

    boolean imageProc = false;

    for (int i = 0; i < strlen(str); i++){

      display.setPrintPos(x,y);
      c = str[i];

      display.print(c);
      if (c == '\n' || x + hspace > w) {
        x = origx;
        y+= vspace;
      } 
      else {
        x+= hspace;
      }
    }
}
  
void drawButton(int buttonPin, int imgWidth,int imgHeight, u8g_pgm_uint8_t* img){
  unsigned int x = 0;
  unsigned int y = 0;
  #define BOX_SIZE 14
  
  switch(buttonPin){
    
    case WAKE_PIN: 
        x = -1;
        y = 15;
        break;
    case SELECT_PIN: 
        x = WIDTH - BOX_SIZE + 1;
        y = 15;
        break;
    case UP_PIN:
        x = -1;
        y = HEIGHT - BOX_SIZE + 1; 
        break;
    case DOWN_PIN: 
        x = WIDTH - BOX_SIZE + 1;
        y = HEIGHT - BOX_SIZE + 1; 
        break;
  }
  
  display.drawFrame(x,y,BOX_SIZE,BOX_SIZE);
  display.drawXBMP(x+2,y+2, imgWidth,imgHeight,img);
  
} 
/*
https://code.google.com/p/u8glib/wiki/userreference#drawBitmap

void u8g_DrawInvXBM(u8g_t u8g, u8g_uint_t x, u8g_uint_t y, u8g_uint_t cnt, const u8g_pgm_uint8_t xbm) {
    while( cnt > 0 ) {
        display.u8g_Draw8Pixel?(u8g, x, y, 0, ~u8g_pgm_read(xbm)); 
        bitmap++; 
        cnt--; 
        x+=8; 
    } 
}*/

void drawTime(int x, int y, char sep){
  display.setPrintPos(x, y); 
  display2digits(hour()); 
  display.print(sep);
  display2digits(minute()); 
}

#endif
