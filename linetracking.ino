#define SENSOR_PIN 4

void setup() {
  Serial.begin(9600);
  Serial.println("Sensor test starting...");
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  int sensorValue = digitalRead(SENSOR_PIN);

  if (sensorValue == HIGH) {
    Serial.println("LINE DETECTED (BLACK)");
  } else {
    Serial.println("NO LINE (WHITE)");
  }

  delay(200);
}
