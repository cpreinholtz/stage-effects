/*
  Input Pull-up Serial

  This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a digital
  input on pin 2 and prints the results to the Serial Monitor.

  The circuit:
  - momentary switch attached from pin 2 to ground
  - built-in LED on pin 13

  Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
  20K-ohm resistor is pulled to 5V. This configuration causes the input to read
  HIGH when the switch is open, and LOW when it is closed.

  created 14 Mar 2012
  by Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/InputPullupSerial
*/


const int kMicPin = 11;

void setup() {
  Serial.begin(9600);
  pinMode(kMicPin, INPUT);

}

void loop() {
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(kMicPin);
  //print out the value of the pushbutton
  Serial.println(sensorVal);


}
