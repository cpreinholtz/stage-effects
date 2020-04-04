
#include "button.h"



void micIsr() {
  mic.setRisingEdge();
}

void setupButtons(){
  attachInterrupt(digitalPinToInterrupt(mic.getPin()), micIsr, RISING);
}
