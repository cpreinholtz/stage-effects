#ifndef Debounce_h
#define Debounce_h

#include "Arduino.h"


class Debounce {
  public:
    /////////////////////////////////////////////////////////////////////
    //Ctor
    /////////////////////////////////////////////////////////////////////
    Debounce::Debounce(int pin, unsigned long debounce)
    {
      pinMode(mPin, INPUT);
      mDebounceDelay = debounce;
      mPin = pin;
      mHit = false;
      mDebounceTime = 0;
    }
    
    
    /////////////////////////////////////////////////////////////////////
    //Setters
    /////////////////////////////////////////////////////////////////////
    void clearHit()
    {
      mHit = false;
    }
    
    
    void setHit()
    {
      if ( millis() - mDebounceTime > mDebounceDelay and mHit == false){
        mHit = true;
        mDebounceTime = millis();
      }
    }

    /////////////////////////////////////////////////////////////////////
    //getters  and setters
    /////////////////////////////////////////////////////////////////////
    bool getHit()
    {
      if(mHit== true){
        clearHit();
        return true;
      } else {
        return false;
      }  
    }
    
    /////////////////////////////////////////////////////////////////////
    //getters  
    /////////////////////////////////////////////////////////////////////
    int getPin(){
      return mPin;
    };
    
  private:
    int mPin;
    bool mHit;
    unsigned long mDebounceTime;
    unsigned long mDebounceDelay;
};



#endif
