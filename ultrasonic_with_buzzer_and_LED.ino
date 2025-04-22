// === Pin Definitions ===
#define TRIG_PIN     33  // Ultrasonic Sensor Trigger Pin
#define ECHO_PIN     25  // Ultrasonic Sensor Echo Pin

#define BUZZER_PIN   16  // Passive Buzzer Pin

#define RED_PIN      26  // RGB LED Red Channel
#define GREEN_PIN    27  // RGB LED Green Channel

#define SENSOR_HW511_PIN 4  // Line Following Sensor HW-511
#define SENSOR_HW201_PIN 5  // Line Following Sensor HW-201

void setup() {
  // --- Initialize ultrasonic sensor pins ---
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // --- Initialize buzzer and RGB LED pins ---
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  // --- Initialize line following sensor pins ---
  pinMode(SENSOR_HW511_PIN, INPUT);
  pinMode(SENSOR_HW201_PIN, INPUT);

  // --- Start serial communication ---
  Serial.begin(115200);
  Serial.println("System Initialized...");
}

// === Function to get distance from ultrasonic sensor in cm ===
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2; // Convert time to distance

  return distance;
}

// === Function to control passive buzzer based on proximity ===
void alertWithBuzzer(int distance, int threshold = 10) {
  if (distance < threshold) {
    tone(BUZZER_PIN, 1000); // Emit 1kHz tone if too close
  } else {
    noTone(BUZZER_PIN);     // Silence buzzer if safe
  }
}

// === Function to control RGB LED based on proximity ===
void controlRGBLed(int distance, int threshold = 10) {
  if (distance < threshold) {
    digitalWrite(RED_PIN, HIGH);    // Red ON = Object too close
    digitalWrite(GREEN_PIN, LOW);
  } else {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);  // Green ON = Safe distance
  }
}

// === Function to read and print line sensor values ===
void checkLineSensors() {
  int hw511 = digitalRead(SENSOR_HW511_PIN); // Read HW-511 sensor
  int hw201 = digitalRead(SENSOR_HW201_PIN); // Read HW-201 sensor

  // Display interpretation of sensor readings
  Serial.print("HW-511: ");
  Serial.print(hw511 == HIGH ? "LINE DETECTED (BLACK)" : "NO LINE (WHITE)");
  Serial.print(" | HW-201: ");
  Serial.println(hw201 == HIGH ? "LINE DETECTED (BLACK)" : "NO LINE (WHITE)");
}

void loop() {
  // --- Read current distance from ultrasonic sensor ---
  int distance = getDistance();

  // --- Trigger feedback components ---
  alertWithBuzzer(distance);       // Control buzzer
  controlRGBLed(distance);         // Control RGB LED
  checkLineSensors();              // Check and report line sensor status

  // --- Print distance to serial monitor ---
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(200);  // Delay between readings
}
