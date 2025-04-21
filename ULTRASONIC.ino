#define TRIG_PIN  13  // GPIO13
#define ECHO_PIN  12  // GPIO12
#define BUZZER_PIN 14 // GPIO14
#define

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // Trigger ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo pulse
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2; // Distance in cm

  // Activate buzzer if object is within 30cm
  if (distance < 10) {
    digitalWrite(BUZZER_PIN, HIGH); // For active buzzer
    //tone(BUZZER_PIN, 1000); // For passive buzzer (1kHz tone)
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // Turn off active buzzer
    //noTone(BUZZER_PIN);          // Turn off passive buzzer
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
