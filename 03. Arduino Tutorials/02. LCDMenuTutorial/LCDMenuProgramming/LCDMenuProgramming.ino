#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);

//Input & Button Logic
const int numOfInputs = 4;
const int inputPins[numOfInputs] = {8,9,10,11};
int inputState[numOfInputs];
int lastInputState[numOfInputs] = {LOW,LOW,LOW,LOW};
bool inputFlags[numOfInputs] = {LOW,LOW,LOW,LOW};
long lastDebounceTime[numOfInputs] = {0,0,0,0};
long debounceDelay = 5;

//LCD Menu Logic
const int numOfScreens = 10;
int currentScreen = 0;
String screens[numOfScreens][2] = {{"Motor Voltage","Volts"}, {"Motor Current", "Amps"}, 
{"Motor Rated HP","HP"},{"Overload Temp.","degC"}, {"Accel Time", "Secs"}, {"Restart Time","Mins"},
{"Analog Out. Curr.","mA"},{"Input Temp.","degC"}, {"Run Time", "Hours"}, {"Start Times","times"}};
int parameters[numOfScreens];

void setup() {
  for(int i = 0; i < numOfInputs; i++) {
    pinMode(inputPins[i], INPUT);
    digitalWrite(inputPins[i], HIGH); // pull-up 20k
  }
  //Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  setInputFlags();
  resolveInputFlags();
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
      inputAction(i);
      inputFlags[i] = LOW;
      printScreen();
    }
  }
}

void inputAction(int input) {
  if(input == 0) {
    if (currentScreen == 0) {
      currentScreen = numOfScreens-1;
    }else{
      currentScreen--;
    }
  }else if(input == 1) {
    if (currentScreen == numOfScreens-1) {
      currentScreen = 0;
    }else{
      currentScreen++;
    }
  }else if(input == 2) {
    parameterChange(0);
  }else if(input == 3) {
    parameterChange(1);
  }
}

void parameterChange(int key) {
  if(key == 0) {
    parameters[currentScreen]++;
  }else if(key == 1) {
    parameters[currentScreen]--;
  }
}

void printScreen() {
  lcd.clear();
  lcd.print(screens[currentScreen][0]);
  lcd.setCursor(0,1);
  lcd.print(parameters[currentScreen]);
  lcd.print(" ");
  lcd.print(screens[currentScreen][1]);
}

