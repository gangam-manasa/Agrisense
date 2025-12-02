#include <Servo.h>

Servo myServo; // Create servo object
const int trigPin = 9; // Ultrasonic sensor TRIG pin
const int echoPin = 8; // Ultrasonic sensor ECHO pin
const int buzzerPin = 11; // Buzzer pin
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  myServo.attach(10); // Attach servo to pin 10
  myServo.write(90); // Start at the center position
  Serial.begin(9600);
}

void loop() {
  // Sweep servo from 0° to 180°
  for (int pos = 0; pos <= 180; pos += 5) { // Adjust step size if needed
    myServo.write(pos); // Move servo to position
    delay(100); // Allow servo to reach position
    checkAndAlert(pos); // Measure distance and alert if needed
  }

  // Sweep servo back from 180° to 0°
  for (int pos = 180; pos >= 0; pos -= 5) {
    myServo.write(pos); // Move servo to position
    delay(100); // Allow servo to reach position
    checkAndAlert(pos); // Measure distance and alert if needed
  }
}

void checkAndAlert(int angle) {
  // Ultrasonic sensor measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  // Trigger alert and display only when an object is within 10 cm range
  if (distance > 0 && distance <= 20) { // Object detected within 10 cm
    Serial.print("Object detected at ");
    Serial.print(angle);
    Serial.print("°: ");
    Serial.print(distance);
    Serial.println(" cm");
    digitalWrite(buzzerPin, HIGH); // Sound the buzzer
    delay(200); // Keep the buzzer on briefly
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  }
}
