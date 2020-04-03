#include "time.h"
#include "button.h"
#include "pot.h"
#include "sequence.h"

#include <Servo.h>

///////////////////////////////////////////////////////////////////////////////
//constants
///////////////////////////////////////////////////////////////////////////////
const unsigned long LOOP_MSEC= 25; //ms period to start  //might be able to go down without dbg?

const int kServoPin = 11;
///////////////////////////////////////////////////////////////////////////////
//globals
///////////////////////////////////////////////////////////////////////////////
Button buttonR(2,50);
Button buttonB(13,50);
Button mic(3,100);

Pot potA(A1);
Pot potB(A2);//logrithmic

Sequence strobe(-1);

Timer timer(LOOP_MSEC);

Servo servo;

///////////////////////////////////////////////////////////////////////////////
//functions
///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  setupButtons();//setup interrupts
  servo.attach(kServoPin);
  //timer.setup();//sets time to 0
}

void loop() {
  
  if( mic.getRisingEdge()){
    strobe.startSequence(1,5);
  }
 
  else if( buttonR.getRisingEdge()){
    strobe.startSequence(0,1);
  }
 
 


  

  //Serial.println("strobe.getStates()");
  //Serial.println(strobe.getStates());
  houseKeeping();//don't delete
}

//executed after each loop
void houseKeeping(){
  servo.write(map(potB.getVal(), 0, 1023, 50, 180));
  strobe.run();
  potA.sample();
  potB.sample();
  timer.run(); //delay till timeout
}

