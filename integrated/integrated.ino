#include "time.h"
#include "button.h"
#include "debounce.h"
#include "pot.h"
#include "sequence.h"



///////////////////////////////////////////////////////////////////////////////
//constants
///////////////////////////////////////////////////////////////////////////////
const unsigned long LOOP_MSEC= 25; //ms period to start  //might be able to go down without dbg?


//bottons
const int kButtonMPin = 5;
const int kButtonNPin = 4;
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
Button buttonN(kButtonNPin);
Button buttonM(kButtonMPin);


Debounce mic(kMicMPin,100);

Pot potA(kPotAPin);
Pot potB(kPotBPin);//logrithmic

Sequence strobe(-1);

Timer timer(LOOP_MSEC);


///////////////////////////////////////////////////////////////////////////////
//functions
///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  setupLeds();
  attachInterrupt(digitalPinToInterrupt(mic.getPin()), micIsr, RISING);
}

void loop() {

  if( buttonM.getRisingEdge()){
    strobe.startSequence(0,4);
  }

  if( buttonN.getRisingEdge()){
    strobe.startSequence(1,15);
  }

  if (mic.getHit()){  
    nextPattern();
  }
 
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

  //use pots
  strobe.setSequenceTimes(0,   map( potA.getVal(),   0, 1024 , 25 , 200));
  strobe.setSequenceTime (1,0, map( potB.getVal(),   0, 4096 , 25 , 400));
  strobe.setSequenceTime (1,1, map( potB.getVal()*4, 0, 4096 , 25 , 400));

  
  //poll buttons? this will change state
  
  timer.run(); //delay till timeout
}



void micIsr(){
  mic.setHit();
}



