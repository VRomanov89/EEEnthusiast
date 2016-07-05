//Full Program: https://github.com/VRomanov89
const int rightSensorPin = A0;
const int leftSensorPin = A1;
int rightSensorRead = 0;
int leftSensorRead = 0;
int rightLightPct = 0;
int leftLightPct = 0;
int degreeChange = 1;

//Arduino's CustomStepper library
//Author:  Igor Campos
#include <CustomStepper.h>
CustomStepper stepper(9, 10, 11, 12);

void setup() {
  Serial.begin(9600);
  stepper.setRPM(5);
  stepper.setSPR(4075.7728395);
}

void loop() {
  rightSensorRead = analogRead(rightSensorPin);
  leftSensorRead = analogRead(leftSensorPin);
  rightLightPct = map(rightSensorRead, 0, 1023, 0, 100);
  leftLightPct = map(leftSensorRead, 0, 1023, 0, 100);
  degreeChange = map(abs(rightLightPct-leftLightPct),0,100,2,10);
  Serial.print("right = ");
  Serial.print(rightSensorRead);
  Serial.print(" left = ");
  Serial.print(leftSensorRead);
  Serial.print(" Pct r/l = ");
  Serial.print(rightLightPct);
  Serial.print("/");
  Serial.println(leftLightPct);
  if(rightLightPct < 30 && leftLightPct < 30){
    Serial.println("No sun detected!");
  }else if(rightLightPct > leftLightPct){
    Serial.println("Turning CCW!");
    rotateLeft();
    stepper.run();
  }else{
    Serial.println("Turning CW!");
    rotateRight();
    stepper.run();
  }
}

void rotateLeft(){
  stepper.setDirection(CCW);
  stepper.rotateDegrees(degreeChange);
  while(stepper.isDone() == false){
    stepper.run();
  }
}
void rotateRight(){
  stepper.setDirection(CW);
  stepper.rotateDegrees(degreeChange);
  while(stepper.isDone() == false){
    stepper.run();
  }
}

