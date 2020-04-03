
#include "button.h"

void buttonRIsr() {
  buttonR.setRisingEdge();
}

void micIsr() {
  mic.setRisingEdge();
}

void setupButtons(){
  attachInterrupt(digitalPinToInterrupt(buttonR.getPin()), buttonRIsr, RISING);
  attachInterrupt(digitalPinToInterrupt(mic.getPin()), micIsr, RISING);
}
