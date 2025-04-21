// TCS3200 Color Sensor Minimal Test with ESP32
#define S0 25
#define S1 26
#define S2 27
#define S3 18
#define sensorOut 19

int redFreq = 0;
int greenFreq = 0;
int blueFreq = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.println("Color Sensor Ready...");
}

int getColorFreq(int s2State, int s3State) {
  long sum = 0;
  for (int i = 0; i < 5; i++) {
    digitalWrite(S2, s2State);
    digitalWrite(S3, s3State);
    delay(10); // Let it settle
    sum += pulseIn(sensorOut, LOW);
  }
  return sum / 5;
}

void loop() {
  redFreq = getColorFreq(LOW, LOW);      // RED
  greenFreq = getColorFreq(HIGH, HIGH);  // GREEN
  blueFreq = getColorFreq(LOW, HIGH);    // BLUE

  // Print raw frequencies
  Serial.print("R: "); Serial.print(redFreq);
  Serial.print(" | G: "); Serial.print(greenFreq);
  Serial.print(" | B: "); Serial.println(blueFreq);

  // Determine detected color (adjust logic as needed)
  if (redFreq < greenFreq && redFreq < blueFreq) {
    Serial.println("Detected Color: RED");
  } else if (greenFreq < blueFreq && greenFreq < redFreq) {
    Serial.println("Detected Color: GREEN");
  } else if (blueFreq < redFreq && blueFreq < greenFreq) {
    Serial.println("Detected Color: BLUE");
  } else {
    Serial.println("Detected Color: UNKNOWN");
  }

  Serial.println("------------------------");
  delay(1000);
}
