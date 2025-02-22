
const int Temperature = A0;
const int Down   = 2;
const int Up     = 3;
const int Green  = 4;
const int Yellow = 5;
const int Red    = 6;
const int Delay  = 200;

void setup() {
  Serial.begin(9600);
  
  // 1. Buttons
  pinMode(Down, INPUT);
  pinMode(Up, INPUT);
  digitalWrite(Down, LOW);
  digitalWrite(Up, LOW);
  attachInterrupt(digitalPinToInterrupt(Down), onDown, RISING);
  attachInterrupt(digitalPinToInterrupt(Up), onUp, RISING);

  // 2. LEDs
  pinMode(Green, OUTPUT);
  pinMode(Yellow, OUTPUT);
  pinMode(Red, OUTPUT);
  digitalWrite(Green, LOW);
  digitalWrite(Yellow, LOW);
  digitalWrite(Red, LOW);
}

int AnalogBitMax = 1024;

// From datasheet of TMP36 - https://www.analog.com/media/en/technical-documentation/data-sheets/tmp35_36_37.pdf - 22.02.2025
volatile float BaseTemp = 24.4;      // C
const float MaxVoltage  = 5.0;        
const float BaseTempVoltage = 0.75;  // V
const float VoltagePerTemp = 0.01;   // V/C
const float TempPerVoltage = 100.0;  // C/V

void loop() {
  int   readBit = analogRead(Temperature);                               // between [0, 1024];
  float readVolt = (float(readBit) / AnalogBitMax) * MaxVoltage;         // between [0V, 5V]
  float temp = BaseTemp + (readVolt - BaseTempVoltage) * TempPerVoltage; // Between [-40C, +125C] specified

  // For the serial plotter
  Serial.print(BaseTemp);
  Serial.print("\t");
  Serial.println(temp);
 
  delay(Delay*5);

  // Set colors of LED
  if (temp > 24.0) {
    digitalWrite(Red, HIGH);
    digitalWrite(Yellow, HIGH);
    digitalWrite(Green, HIGH);
  } else if (temp > 22.0) {
    digitalWrite(Red, LOW);
    digitalWrite(Yellow, HIGH);
    digitalWrite(Green, HIGH);
  } else {
    digitalWrite(Red, LOW);
    digitalWrite(Yellow, LOW);
    digitalWrite(Green, HIGH);
  }
}

volatile int last = 0;

void onDown() {
  // Debounce
  unsigned long current = millis();
  if (current - last < Delay*3) return;
  last = current;
  
  // Handle
  BaseTemp -= 0.1;
}

void onUp() {
  // Debounce
  unsigned long current = millis();
  if (current - last < Delay*3) return;
  last = current;

  // Handle
  BaseTemp += 0.1;
}
