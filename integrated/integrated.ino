#include "Arduino.h"
#include "button.h"

Button buttonR(2,50);
Button buttonB(13,50);
Button mic(3,100);

void setup() {
  Serial.begin(9600);
  setupButtons();
}

void loop() {
 if( mic.getRisingEdge()){
  Serial.println("mic hit here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
 }
 
 else if( buttonR.getRisingEdge()){
  Serial.println(buttonR.getEdgeCount());
 }
 
 else if( buttonR.getState()){
  Serial.println("high");
  buttonR.getRisingEdge();
 }  
 
 else Serial.println("nothin");
 
}
