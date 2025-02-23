const int RedLamp = 11;
const int GreenLamp = 10;
const int BlueLamp = 9;

const int RedSensor = A3;
const int GreenSensor = A4;
const int BlueSensor = A5;

const int LoopDelay = 500;

void setup() {
  Serial.begin(9600);
  
  pinMode(RedLamp, OUTPUT);
  pinMode(GreenLamp, OUTPUT);
  pinMode(BlueLamp, OUTPUT);
}

int redValues[] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };
int greenValues[] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };
int blueValues[] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };
const int ValuesLength = 20;
unsigned long n = 0;

void loop() {
  // 1. Keep last values around
  analogRead(RedSensor); // Dummy read. This forces the ADC to settle before taking the real reading.
  redValues[n % ValuesLength] = analogRead(RedSensor);
  
  analogRead(GreenSensor); // Dummy read.
  greenValues[n % ValuesLength] = analogRead(GreenSensor);
  
  analogRead(BlueSensor); // Dummy read.
  blueValues[n % ValuesLength] = analogRead(BlueSensor);

  n += 1;

  // 2. Mean value filter
  float redValue = 0; float greenValue = 0; float blueValue = 0;
  for (int i = 0; i < ValuesLength; ++i) {
    redValue += redValues[i];
    greenValue += greenValues[i];
    blueValue += blueValues[i];
  }
  redValue /= ValuesLength;
  greenValue /= ValuesLength;
  blueValue /= ValuesLength;

  // 3. Transform from 1023 -> 255
  redValue /= 4;
  greenValue /= 4;
  blueValue /= 4;

  // 4. Print to plot
  Serial.print(redValue); Serial.print("\t");
  Serial.print(greenValue); Serial.print("\t");
  Serial.print(blueValue); Serial.print("\n");

  // 5. Write to output RGB lamp
  analogWrite(RedLamp, redValue);
  analogWrite(GreenLamp, greenValue);
  analogWrite(BlueLamp, blueValue);

  delay(20);
}

