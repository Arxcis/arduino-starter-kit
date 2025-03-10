
const int C = 261, D = 293, E = 329, F = 349, G = 392, A = 440, H = 493;
const int Input = A0;
const int Speaker = 13;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int input = analogRead(A0);

  Serial.println(input);

  if (input > 1020) {
    tone(Speaker, C);
  } else if (input > 1000) {
    tone(Speaker, D);
  } else if (input > 970) {
    tone(Speaker, E);
  } else if (input > 930) {
    tone(Speaker, F);
  } else if (input > 700) {
    tone(Speaker, G);
  } else if (input > 510) {
    tone(Speaker, A);
  } else if (input > 5 && input < 10) {
    tone(Speaker, H);
  } else {
    noTone(Speaker);
  }

  delay(32);
}
