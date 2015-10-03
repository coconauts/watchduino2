#pragma once

#ifndef WATCHDUINO_TEST_H 
#define WATCHDUINO_TEST_H

#include "watchcore.h"
#include "utils.h"

class Test: public Screen //http://www.avr-developers.com/mm/memoryusage.html
{
  private:
    int data_size;
    int bss_size; // (Block Started by Symbol) part of the data segment containing statically-allocated variables represented solely by zero-valued bits initially
    int heap_end;
    int heap_size;
    int stack_size;
    int available;
    char stack;
    String dynArr;
  public:
    Test(){
      refresh = 1000;
      
      stack = 1;
      
      extern char *__data_start;
      extern char *__data_end;
      extern char *__bss_start;
      extern char *__bss_end;
      extern char *__heap_start;
      extern char *__heap_end;
      
      data_size = (int)&__data_end - (int)&__data_start;
      bss_size  = (int)&__bss_end - (int)&__data_end;
      heap_end  = (int)&stack - (int)&__malloc_margin;
      heap_size = heap_end - (int)&__bss_end;
      stack_size  = RAMEND - (int)&stack + 1;
      available = (RAMEND - (int)&__data_start + 1);
    }
    ~Test(){}
    void draw(){
      
      display.setCursor(2,16); 
      /*display.print(F("Data: ")); display.println(data_size);
      display.print(F("BSS: ")); display.println(bss_size);
      display.print(F("Heap: ")); display.println(heap_size);
      display.print(F("Stack: ")); display.println(stack_size);
      display.print(F("Available: ")); display.println(available);
*/
      int free_memory;
      
      extern char __bss_end;
      extern char *__brkval;

      if((int)__brkval == 0)  free_memory = ((int)&free_memory) - ((int)&__bss_end);
      else free_memory = ((int)&free_memory) - ((int)__brkval);
      display.print(F("Free: ")); display.println(free_memory);
      
      display.print(F("DynString: ")); 
      display.print(dynArr);
      
    }
    void controller(){}
    void update(){ 
      //Increase memory every second
      dynArr += "-";
    }
    void enter(){}
    void exit(){}
};

#endif
