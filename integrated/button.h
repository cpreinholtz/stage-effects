#ifndef Button_h
#define Button_h

#include "Arduino.h"


class Button {
  public:
    /////////////////////////////////////////////////////////////////////
    //ctor
    /////////////////////////////////////////////////////////////////////        
    Button(int pin){
      pinMode(mPin, INPUT);
      mLastState = false;
      mPin = pin;
    };

    /////////////////////////////////////////////////////////////////////
    //getters and setters
    /////////////////////////////////////////////////////////////////////
          
    bool getState(){
      bool mCurrentState= digitalRead(mPin)== HIGH ? true : false;
      mLastState =mCurrentState;
      return mCurrentState;      
    };
    
    bool getRisingEdge(){
      
      bool mCurrentState = digitalRead(mPin)== HIGH ? true : false;

      //rising edge
      if(mCurrentState==true and mLastState==false ){
        mLastState = true;
        return true;
      }

      //currently high, but not edge
      else if (mCurrentState==true and mLastState==true ){
        mLastState = true;
        return false;
      }
      
      //falling edge
      else if (mCurrentState==false and mLastState==true ){
        mLastState = false;
        return false; 
      } 
      
      //false false   
      else { 
        mLastState =false;
        return false;
      } 
    };


    /////////////////////////////////////////////////////////////////////
    //getters  
    /////////////////////////////////////////////////////////////////////
    int getPin(){
      return mPin;
    };

    
  private:
    int mPin;
    bool mLastState;
};


#endif
