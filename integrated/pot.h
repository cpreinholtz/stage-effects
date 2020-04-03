#ifndef Pot_h
#define Pot_h

#include "Arduino.h"


class Pot {
  public:
    Pot(int pin){
      mPin=pin;
      mVal=512;
    };
    
    void sample(){
      mVal = analogRead(mPin);
      //int temp = analogRead(mPin);
      //mVal = (temp + mVal) >>1;
    };  

      
    int getVal(){
      return mVal;
    };   
    
    int sampleAndGetVal(){
      sample();
      return getVal();
    };   

    
  private:
    int mPin;
    int mVal;
};

#endif
