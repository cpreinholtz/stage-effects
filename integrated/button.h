#ifndef Button_h
#define Button_h

#include "Arduino.h"


class Button {
  public:
    //ctor
    Button(int pin, unsigned long debounce);


    //setters
    void clearRisingEdge();
    void setRisingEdge();  

    //getters    
    bool getState();    
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
