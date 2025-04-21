
// Simple ESP32 Motor Control (Forward/Backward)
#define MOTOR_PIN1 25  
#define MOTOR_PIN2 26
#define MOTOR_PIN3 27
#define MOTOR_PIN4 14
#define ENB_PIN 32
#define ENA_PIN 33

void setup() {
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  
  // Start with motors stopped
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
  analogWrite(ENB_PIN, 0);
  analogWrite(ENA_PIN, 0);
  
  Serial.begin(115200);
  Serial.println("Simple Motor Control Ready");
}

void loop() {
  // Move forward at medium speed (150/255)
  Serial.println("Moving FORWARD");
  digitalWrite(MOTOR_PIN1, HIGH);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, HIGH);
  digitalWrite(MOTOR_PIN4, LOW);
  analogWrite(ENB_PIN, 2000),
    analogWrite(ENA_PIN, 5000);
  delay(3000);
  
  // Stop for 1 second
  Serial.println("STOP");
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
  analogWrite(ENB_PIN, 0);
  analogWrite(ENA_PIN, 0);
  delay(100);
  
  // Move backward at medium speed
  Serial.println("Moving BACKWARD");
  digitalWrite(MOTOR_PIN1,LOW);
  digitalWrite(MOTOR_PIN2, HIGH);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, HIGH);
  analogWrite(ENB_PIN, 2000);
  analogWrite(ENA_PIN, 5000);
  delay(3000);
  
  // Stop for 1 second
  Serial.println("STOP");
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
  analogWrite(ENB_PIN, 0);
  analogWrite(ENA_PIN, 0);
  delay(100);
}
