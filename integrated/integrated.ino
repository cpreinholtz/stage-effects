#include "time.h"
#include "button.h"
#include "pot.h"
#include "sequence.h"



///////////////////////////////////////////////////////////////////////////////
//constants
///////////////////////////////////////////////////////////////////////////////
const unsigned long LOOP_MSEC= 25; //ms period to start  //might be able to go down without dbg?


//bottons
const int kButtonMPin = 1;
const int kMicMPin = 3;


const int kLedPin=7;

//const int kSequenceNumPins = 6;    
//const int kSequencePins[kSequenceNumPins] = {13,12,11,10,9,8};


const int kPotAPin = A1;
const int kPotBPin = A2;

///////////////////////////////////////////////////////////////////////////////
//globals
///////////////////////////////////////////////////////////////////////////////
//Button buttonR(2,50);
//Button buttonB(13,50);
Button buttonM(kButtonMPin,50);
Button mic(kMicMPin,100);

Pot potA(kPotAPin);
Pot potB(kPotBPin);//logrithmic

Sequence strobe(-1);

Timer timer(LOOP_MSEC);


///////////////////////////////////////////////////////////////////////////////
//functions
///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  setupButtons();//setup interrupts
  setupLeds();
}

void loop() {
  
  if( mic.getRisingEdge()){
    strobe.startSequence(0,8);
    strobe.startSequence(1,5);
  }

//  else if( buttonR.getRisingEdge()){
//    strobe.startSequence(0,1);
//  }
 
  houseKeeping();//don't delete
}

//executed after each loop
void houseKeeping(){
  //maintain stuff
  runLeds();
  strobe.run();


  //poll pots
  potA.sample();
  potB.sample();

  //poll buttons
  
  timer.run(); //delay till timeout
}

