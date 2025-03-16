
const int Hour1 = 10;
const int Hour2 = 11;
const int Hour4 = 12;

const int Minute1 = 3;
const int Minute2 = 4;
const int Minute4 = 5;
const int Minute8 = 6;
const int Minute16 = 7;
const int Minute32 = 8;

const int Second = 2;

const int Lights[] = { Hour1, Hour2, Hour4, Minute1, Minute2, Minute4, Minute8, Minute16, Minute32, Second };
const int LightsCount = sizeof(Lights) / sizeof(Lights[0]);

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < LightsCount; ++i) {
    pinMode(Lights[i], OUTPUT);
    digitalWrite(Lights[i], HIGH);
  }
  delay(2000);

  for (int i = 0; i < LightsCount; ++i) {
    digitalWrite(Lights[i], LOW);
  }
}

void loop() {
  const auto ms = millis();

  const int seconds = floor(ms / 1000.0);
  const int minutes = floor(ms / 1000.0 / 60.0);
  const int hours = floor(ms / 1000.0 / 60.0 / 60.0);
  
  const int second1  = seconds & 1;

  const int minute1  = minutes & 1;
  const int minute2  = (minutes & (1 << 1)) >> 1;
  const int minute4  = (minutes & (1 << 2)) >> 2;
  const int minute8  = (minutes & (1 << 3)) >> 3;
  const int minute16 = (minutes & (1 << 4)) >> 4;
  const int minute32 = (minutes & (1 << 5)) >> 5;
  
  const int hour1  = hours & 1;
  const int hour2  = (hours & (1 << 1)) >> 1;
  const int hour4  = (hours & (1 << 2)) >> 2;

  //digitalWrite(Second, second1);

  digitalWrite(Minute1, minute1);
  digitalWrite(Minute2, minute2);
  digitalWrite(Minute4, minute4);
  digitalWrite(Minute8, minute8);
  digitalWrite(Minute16, minute16);
  digitalWrite(Minute32, minute32);

  digitalWrite(Hour1, hour1);
  digitalWrite(Hour2, hour2);
  digitalWrite(Hour4, hour4);

  Serial.println(seconds);
  
  delay(100);
}
