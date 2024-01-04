
*******************PIN DESCRIPTION *************************************************

#define MQ_PIN A0       // Replace with your MQ135 sensor pin
#define POT_PIN A1      // Replace with your potentiometer pin

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(MQ_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
}

void loop() {
  // Read air quality percentage from the potentiometer
  int potValue = analogRead(POT_PIN);
  float airQuality = map(potValue, 0, 1023, 0, 100);

  // Read sensor value from MQ135 sensor
  int sensorValue = analogRead(MQ_PIN);

  // Use the sensor value as the air quality percentage if pot is not used
  if (potValue < 10) {
    airQuality = map(sensorValue, 0, 1023, 0, 100);
  }

  // Print air quality data to the virtual terminal
  Serial.print("Air Quality: ");
  Serial.print(airQuality);
  Serial.print("%, ");

  // Categorize air quality
  if (airQuality <= 40) {
    Serial.println("Critical");
  } else if (airQuality <= 70) {
    Serial.println("Bad");
  } else {
    Serial.println("Good");
  }

  delay(1000);
}
