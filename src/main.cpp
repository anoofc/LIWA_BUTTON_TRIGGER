#include <Arduino.h>

#define DEBUG 0

#define DEBOUNCE_DELAY 500

const int buttonPins[5] = {13, 14, 27, 26, 25}; 
const int relayPins[5]  = {22, 21, 19, 18, 5 }; 

bool ledStatus[5] = {0,0,0,0,0};
uint8_t currentSwitch = 0;
uint32_t lastUpdateMillis = 0;


void checkSwitch (){
  for (int i=0; i<5; i++){
    if (i != currentSwitch){ digitalWrite(relayPins[i], HIGH); }
    if (digitalRead(buttonPins[i]) == LOW){
      if (millis() - lastUpdateMillis < DEBOUNCE_DELAY) { return; }
      currentSwitch = i;
      digitalWrite(relayPins[i], LOW);
      char command = 'A' + i;
      Serial.println();
      Serial.println(command);
      lastUpdateMillis = millis();
      if (DEBUG) { Serial.println("Switch " + String(i) + " is pressed"); }
    }
  }
}

void debugSwitch (){
  for(int i = 0; i <5; i++){
      Serial.print("Button "+ String(i) + " : " + String(digitalRead(buttonPins[i])) + "\t");
  } Serial.println();
}

void io_int(){
  for (int i = 0; i < 5; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);
  }
}

void setup() {
  Serial.begin(9600);
  io_int();
}

void loop() {
  checkSwitch();
  if (DEBUG) { debugSwitch(); }
}