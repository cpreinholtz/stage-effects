/* Blink without Delay
 
 Turns on and off a light emitting diode(LED) connected to a digital  
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.
 
 The circuit:
 * LED attached from pin 13 to ground.
 * Note: on most Arduinos, there is already an LED on the board
 that's attached to pin 13, so no hardware is needed for this example.
 
 
 created 2005
 by David A. Mellis
 modified 8 Feb 2010
 by Paul Stoffregen
 
 This example code is in the public domain.

 
 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */


const int numLights =  3;   

const int ledPin[numLights] =  {5,6,13};      

const int buttonPin=2; 

const int analogPin = A0;

const long minimumInterval= 20;    
const long maximumInterval= 300;


void setup() {
  // set the digital pin as output:
  for(int i=0; i<numLights; i++){
    pinMode(ledPin[i], OUTPUT);     
  }
  pinMode(buttonPin,INPUT);     
  Serial.begin(9600);
}



int ledState = LOW;     

 
unsigned long currentMillis;
long previousMillis = 0; 

int analogSample;


void loop()
{


  
  if (digitalRead(buttonPin) == HIGH ){
    ledState = HIGH;
    for(int i=0; i<numLights; i++){
      digitalWrite(ledPin[i], ledState);
    }      
    previousMillis = 0; 

               
  } else {    
    currentMillis = millis();
    
    analogSample = ((analogRead(analogPin)>>2) + 15*analogSample) >>4 ;
    
    if (analogSample > maximumInterval)analogSample= maximumInterval;
    else if(analogSample < minimumInterval)analogSample=  minimumInterval;
    
    //Serial.println(analogSample);  
    
    if(currentMillis - previousMillis > analogSample) {
      // save the last time you blinked the LED 
      previousMillis = currentMillis;


      if (ledState == LOW) ledState = HIGH;
      else ledState = LOW;
      
      for(int i=0; i<numLights; i++){     
        if (i%2==0) digitalWrite(ledPin[i], ledState);
        else digitalWrite(ledPin[i], not ledState);
      }//write all
      
    }//switch led state
    
  }//button is "on"

}

