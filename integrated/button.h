/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Button_h
#define Button_h


#include "Arduino.h"


class Button {
  public:
    Button(int pin, unsigned long debounce);


    
    bool getState();    
    void clearRisingEdge();
    void setRisingEdge();  

      
    int getEdgeCount();
    bool getRisingEdge(); 
    int getPin();

    
  private:
    int mPin;
    bool mEdgeHit;
    int mEdgeCount;
    unsigned long mEdgeTime;
    unsigned long mDebounce;
};

#endif
