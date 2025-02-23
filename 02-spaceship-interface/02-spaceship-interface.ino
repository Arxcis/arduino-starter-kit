
const int Button = 2;
const int GreenLED = 3;
const int FirstRedLED = 4;
const int SecondRedLED = 5;
const int Delay = 300;

void setup() {
  // 0. Aktiver mulighet for Serial.println() på 96000-kanalen
  Serial.begin(9600);

  // 1. Activate digital I/O-pins
  pinMode(Button, INPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(FirstRedLED, OUTPUT);
  pinMode(SecondRedLED, OUTPUT);

  // 2. Attach interrupts
  attachInterrupt(digitalPinToInterrupt(Button), buttonInterrupt, RISING);
}


volatile int active = LOW;
volatile int buttonState = LOW;
volatile int buttonLocked = LOW;

void loop() {
  // 1. During normal operation
  if (active == LOW) {
    digitalWrite(GreenLED, HIGH);
    digitalWrite(FirstRedLED, LOW);
    digitalWrite(SecondRedLED, LOW);
  } else { 
    // if active == HIGH
    digitalWrite(GreenLED, LOW);
    digitalWrite(FirstRedLED, LOW);
    digitalWrite(SecondRedLED, HIGH);
    delay(Delay);

    digitalWrite(FirstRedLED, HIGH);
    digitalWrite(SecondRedLED, LOW);
    delay(Delay);
  }

  // 2. After button pressed
  if (buttonState == HIGH && active == HIGH) {
    buttonLocked = HIGH;
    buttonState = LOW;
    active = LOW;

    digitalWrite(GreenLED, HIGH);
    digitalWrite(FirstRedLED, HIGH);
    digitalWrite(SecondRedLED, HIGH);
    delay(Delay*2);

    digitalWrite(GreenLED, LOW);
    digitalWrite(FirstRedLED, LOW);
    digitalWrite(SecondRedLED, LOW);
    delay(Delay*2);

    buttonLocked = LOW;
  } else if (buttonState == HIGH && active == LOW) {
    buttonLocked = HIGH;
    buttonState = LOW;
    active = HIGH;

    digitalWrite(GreenLED, LOW);
    digitalWrite(FirstRedLED, HIGH);
    digitalWrite(SecondRedLED, LOW);
    delay(Delay);

    buttonLocked = LOW;
  }
}

void buttonInterrupt() {
  if (buttonLocked) {
    return;
  }
  
  buttonState = HIGH;
}
