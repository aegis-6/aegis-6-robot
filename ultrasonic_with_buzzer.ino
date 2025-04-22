#define TRIG_PIN     33  // GPIO13
#define ECHO_PIN     25  // GPIO12
#define BUZZER_PIN   16  // GPIO14

#define RED_PIN      26  // RGB LED Red channel
#define GREEN_PIN    27  // RGB LED Green channel

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);  // Passive buzzer
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  Serial.begin(115200);
}

// Function to get distance in cm using ultrasonic sensor
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

// Function to control passive buzzer based on distance threshold
void alertWithBuzzer(int distance, int threshold = 10) {
  if (distance < threshold) {
    tone(BUZZER_PIN, 1000);  // Start 1kHz tone
  } else {
    noTone(BUZZER_PIN);      // Stop tone
  }
}

// Function to control RGB LED based on distance
void controlRGBLed(int distance, int threshold = 10) {
  if (distance < threshold) {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
  } else {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
  }
}

void loop() {
  int distance = getDistance();

  alertWithBuzzer(distance);
  controlRGBLed(distance);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100);  // Delay to prevent rapid state switching
}
