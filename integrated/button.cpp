#include "Arduino.h"
#include "button.h"

Button::Button(int pin, unsigned long debounce)
{
  pinMode(mPin, INPUT);
  mDebounce = debounce;
  mPin = pin;
  mEdgeHit = false;
  mEdgeCount = 0;
  mEdgeTime = 0;
}

bool Button::getState()
{
  if(digitalRead(mPin)== HIGH){
    //if( mEdgeHit == false) setRisingEdge();
    return true;
  } else {
    return false;
  }  
}

void Button::clearRisingEdge()
{
  mEdgeHit = false;
}


void Button::setRisingEdge()
{
  if ( millis() - mEdgeTime > mDebounce ){
    mEdgeHit = true;
    mEdgeCount = mEdgeCount + 1;
    mEdgeTime = millis();
  }
}



bool Button::getRisingEdge()
{
  if(mEdgeHit== true){
    clearRisingEdge();
    return true;
  } else {
    return false;
  }  
}

int Button::getPin()
{
  return mPin;
}

int Button::getEdgeCount()
{
  return mEdgeCount;
}

