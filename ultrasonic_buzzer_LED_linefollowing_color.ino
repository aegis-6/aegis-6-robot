// === Pin Definitions ===
// --- Ultrasonic Sensor ---
#define TRIG_PIN     33
#define ECHO_PIN     25

// --- Passive Buzzer ---
#define BUZZER_PIN   16

// --- RGB LED ---
#define RED_PIN      26
#define GREEN_PIN    27

// --- Line Following Sensors ---
#define SENSOR_HW511_PIN 4
#define SENSOR_HW201_PIN 5

// --- TCS3200 Color Sensor ---
#define S0           13
#define S1           32
#define S2           14
#define S3           18
#define sensorOut    19

int redFreq = 0;
int greenFreq = 0;
int blueFreq = 0;

void setup() {
  // --- Serial ---
  Serial.begin(115200);
  Serial.println("System Initialized...");

  // --- Ultrasonic ---
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // --- Buzzer + RGB LED ---
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  // --- Line Sensors ---
  pinMode(SENSOR_HW511_PIN, INPUT);
  pinMode(SENSOR_HW201_PIN, INPUT);

  // --- TCS3200 Color Sensor ---
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

// === Distance Sensor Function ===
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

// === Buzzer Alert Function ===
void alertWithBuzzer(int distance, int threshold = 10) {
  if (distance < threshold) {
    tone(BUZZER_PIN, 1000);
  } else {
    noTone(BUZZER_PIN);
  }
}

// === RGB LED Control ===
void controlRGBLed(int distance, int threshold = 10) {
  if (distance < threshold) {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
  } else {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
  }
}

// === Line Sensor Check ===
void checkLineSensors() {
  int hw511 = digitalRead(SENSOR_HW511_PIN);
  int hw201 = digitalRead(SENSOR_HW201_PIN);

  Serial.print("Left (HW-511): ");
  Serial.print(hw511 == HIGH ? "BLACK" : "WHITE");
  Serial.print(" | Right (HW-201): ");
  Serial.println(hw201 == HIGH ? "BLACK" : "WHITE");
}

// === Read Color Sensor Frequencies ===
int getColorFreq(int s2State, int s3State) {
  long sum = 0;
  for (int i = 0; i < 5; i++) {
    digitalWrite(S2, s2State);
    digitalWrite(S3, s3State);
    delay(10);
    sum += pulseIn(sensorOut, LOW);
  }
  return sum / 5;
}

// === Detect Color Function ===
void detectColor() {
  redFreq = getColorFreq(LOW, LOW);
  greenFreq = getColorFreq(HIGH, HIGH);
  blueFreq = getColorFreq(LOW, HIGH);

  Serial.print("R: "); Serial.print(redFreq);
  Serial.print(" | G: "); Serial.print(greenFreq);
  Serial.print(" | B: "); Serial.println(blueFreq);

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
}

void loop() {
  // --- Distance ---
  int distance = getDistance();

  // --- Feedback ---
  alertWithBuzzer(distance);
  controlRGBLed(distance);

  // --- Line Sensors ---
  checkLineSensors();

  // --- Color Detection ---
  detectColor();

  // --- Distance Info ---
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);
}
