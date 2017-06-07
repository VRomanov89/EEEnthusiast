#include <Servo.h>
Servo myServo;
byte myServoAngle = 0;
byte myServoAngleRead = 0;

#include "Wire.h"
#define EEPROM_I2C_ADDRESS 0x50
long lastWrite = 0;
int writePointer = 0;
int writeLimit = 200;

const int analogInPin = A3;
const int numOfInputs = 1;
const int inputPins[numOfInputs] = {8};
int inputState[numOfInputs];
int lastInputState[numOfInputs] = {LOW};
bool inputFlags[numOfInputs] = {LOW};
int inputCounters[numOfInputs];
long lastDebounceTime[numOfInputs] = {0};
long debounceDelay = 10;

void setup() {
  for(int i = 0; i < numOfInputs; i++) {
    pinMode(inputPins[i], INPUT);
    digitalWrite(inputPins[i], HIGH); // pull-up 20k
  }
  Serial.begin(9600);
  myServo.attach(9); 
  Wire.begin();
}

void loop() {
  setInputFlags();
  resolveInputFlags();
  resolveOutputs();
}

void setInputFlags() {
  for(int i = 0; i < numOfInputs; i++) {
    int reading = digitalRead(inputPins[i]);
    if (reading != lastInputState[i]) {
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (reading != inputState[i]) {
        inputState[i] = reading;
        if (inputState[i] == HIGH) {
          inputFlags[i] = HIGH;
        }
      }
    }
    lastInputState[i] = reading;
  }
}

void resolveInputFlags() {
  for(int i = 0; i < numOfInputs; i++) {
    if(inputFlags[i] == HIGH) {
      inputCounters[i]++;
      inputFlags[i] = LOW;
    }
  }
}

void resolveOutputs() {
  myServoAngle = map(analogRead(A3), 0, 1023, 0, 180);
  switch(inputCounters[0]) {
    case 1:
      myServo.write(myServoAngle);
      break;
    case 2:
      myServo.write(myServoAngle);
      if(millis() - lastWrite > 100) {
        writeAddress(writePointer, myServoAngle);
        Serial.print("Writing =");
        Serial.print(writePointer);
        Serial.print(" value =");
        Serial.println(myServoAngle);
        writePointer++;
        lastWrite = millis();
      }
      if(writePointer > writeLimit) {
        inputCounters[0] = 3;
        writePointer = 0;
      }
      break;
    case 3:
      if(millis() - lastWrite > 100) {
        myServoAngleRead = readAddress(writePointer);
        Serial.print("Reading =");
        Serial.print(writePointer);
        Serial.print(" value =");
        Serial.println(myServoAngleRead);
        myServo.write(myServoAngleRead);
        writePointer++;
        lastWrite = millis();
      }
      if(writePointer > writeLimit) {
        writePointer = 0;
      }
  }
}

void writeAddress(int address, byte val)
{
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  Wire.write(val);
  Wire.endTransmission();
}

byte readAddress(int address)
{
  byte rData = 0xFF;
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  Wire.endTransmission();  
  Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);  
  rData =  Wire.read();
  return rData;
}

