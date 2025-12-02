// Pin Configuration
const int soilMoisturePin = A0; // Analog pin connected to soil moisture sensor
const int relayPin = 8;        // Digital pin connected to relay module

// Threshold for soil moisture
int moistureThreshold = 400; // Adjust this value based on testing

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure relay is off initiallyd1311
  
}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Print soil moisture value to the Serial Monitor
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilMoistureValue);

  // Check if soil is dry
  if (soilMoistureValue > moistureThreshold) {
    Serial.println("Soil is dry. Turning on the pump.");
    digitalWrite(relayPin, HIGH); // Turn on the relay
  } else {
    Serial.println("Soil is wet. Turning off the pump.");
    digitalWrite(relayPin, LOW); // Turn off the relay
  }

  delay(2000); // Wait for 2 seconds before next reading
}

