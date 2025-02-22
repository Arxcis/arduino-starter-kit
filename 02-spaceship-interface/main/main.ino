
const int Button = 2;
const int GreenLED = 3;
const int FirstRedLED = 4;
const int SecondRedLED = 5;
const int Delay = 300;

void setup() {
  // ...digital I/O-pins
  pinMode(Button, INPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(FirstRedLED, OUTPUT);
  pinMode(SecondRedLED, OUTPUT);
}

int active = LOW;

void loop() {
  int switchState = digitalRead(Button);

  if (switchState == HIGH && active == HIGH) {
    active = LOW;
    digitalWrite(GreenLED, HIGH);
    digitalWrite(FirstRedLED, HIGH);
    digitalWrite(SecondRedLED, HIGH);
    delay(Delay*2);

    digitalWrite(GreenLED, LOW);
    digitalWrite(FirstRedLED, LOW);
    digitalWrite(SecondRedLED, LOW);
    delay(Delay*2);
  } else if (switchState == HIGH && active == LOW) {
    active = HIGH;
  }

  if (active == LOW) {
    digitalWrite(GreenLED, HIGH);
    digitalWrite(FirstRedLED, LOW);
    digitalWrite(SecondRedLED, LOW);
  } else { 
    // if active == HIGH
    digitalWrite(GreenLED, LOW);
    digitalWrite(FirstRedLED, HIGH);
    digitalWrite(SecondRedLED, LOW);
    delay(Delay);

    digitalWrite(FirstRedLED, LOW);
    digitalWrite(SecondRedLED, HIGH);
    delay(Delay);
  }
}
