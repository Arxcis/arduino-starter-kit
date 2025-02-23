#include <Servo.h>

Servo servo;
const int PotentiometerPin = A5;
const int ServoPin = 9;

void setup() {
  Serial.begin(9600);
  servo.attach(ServoPin);
}

const float alpha = 0.1;
float potential   = 0.0;

void loop() {
  int newPotential = analogRead(PotentiometerPin);
  // alpha-filter
  potential = potential * (1.0 - alpha) + (newPotential * alpha);
  
  // map from [0,1023] bits -> degrees
  int angle = map(long(potential), 0, 1023, 50, 145);

  Serial.print(potential);
  Serial.print("\t");
  Serial.println(angle);

  servo.write(angle);
  delay(20);
}

int clamp(int value, int minVal, int maxVal) {
  if (value < minVal) return minVal;
  if (value > maxVal) return maxVal;
  return value;
}