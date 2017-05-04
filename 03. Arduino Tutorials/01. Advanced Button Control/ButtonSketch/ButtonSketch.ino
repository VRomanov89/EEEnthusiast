const int numOfInputs = 2;
const int inputPins[numOfInputs] = {2,3};
const int outputPin = 10;

int LEDState = 0;
int inputState[numOfInputs];
int lastInputState[numOfInputs] = {LOW,LOW};
bool inputFlags[numOfInputs] = {LOW,LOW};
int inputCounters[numOfInputs];

long lastDebounceTime[numOfInputs] = {0,0};
long debounceDelay = 50;

void setup() {
  for(int i = 0; i < numOfInputs; i++) {
    pinMode(inputPins[i], INPUT);
    digitalWrite(inputPins[i], HIGH); // pull-up 20k
  }
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
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
      // Input Toggle Logic
      inputCounters[i]++;
      updateLEDState(i); 
      printString(i);
      inputFlags[i] = LOW;
    }
  }
}

void printString(int output) {
      Serial.print("Input ");
      Serial.print(output);
      Serial.print(" was pressed ");
      Serial.print(inputCounters[output]);
      Serial.println(" times.");
}

void updateLEDState(int input) {
  // input 0 = State 0 and 1
  if(input == 0) {
    if(LEDState == 0) {
      LEDState = 1;
    }else{
      LEDState = 0;
    }
  // input 1 = State 2 to 6
  }else if(input == 1) { // 2,3,4,5,6,2,3,4,5,6,2,
    if(LEDState == 0 || LEDState == 1 || LEDState > 5) {
      LEDState = 2;
    }else{
      LEDState++;
    }
  }
}

void resolveOutputs() {
  switch (LEDState) {
    case 0:
      digitalWrite(outputPin, LOW);
      break;
    case 1:
      digitalWrite(outputPin, HIGH);
      break;
    case 2:
      analogWrite(outputPin, 30);
      break;
    case 3:
      analogWrite(outputPin, 70);
      break;
    case 4:
      analogWrite(outputPin, 100);
      break;
    case 5:
      analogWrite(outputPin, 155);
      break;
    case 6:
      analogWrite(outputPin, 255);
      break;
    default: 
    break;
  }
}

