################################## WEATHER MONITORING SYSTEM #################################


**********************************iMPORT REQUIRED LIBRARY*************************************

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <DHT.h>
**********************************INITIALIZE PINS & SENSORS**********************************
#define TFT_CS 10
#define TFT_DC 9
#define DHT_PIN 2      // Replace with your DHT sensor pin
#define DHT_TYPE DHT11 // Replace with your DHT sensor type
#define MQ_PIN A0      // Replace with your MQ135 sensor pin
#define POT_PIN A1     // Replace with your potentiometer pin

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, -1);
DHT dht(DHT_PIN, DHT_TYPE);

void setup(void) {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  dht.begin();
  pinMode(MQ_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
}

float readAirQuality() {
  // Read sensor values
  int sensorValue = analogRead(MQ_PIN);
  int potValue = analogRead(POT_PIN);

  // Use the potentiometer value as the air quality percentage
  float airQuality = map(potValue, 0, 1023, 0, 100);
  return constrain(airQuality, 0, 100); // Ensure airQuality is within 0-100%
}

String classifyAirQuality(float airQuality) {
  if (airQuality <= 40) {
    return "Critical";
  } else if (airQuality <= 70) {
    return "Bad";
  } else {
    return "Good";
  }
}

void printData(float temperature, float humidity, float airQuality, String airQualityClass) {
  // Print temperature on the first row in bright green
  tft.setCursor(10, 20);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.print("Temperature: " + String(temperature) + " C");

  // Print humidity on the second row in bright green
  tft.setCursor(10, 40);
  tft.print("Humidity: " + String(humidity) + " %");

  // Print air quality percentage, air quality classification on the third row in bright green
  tft.setCursor(10, 60);
  tft.print("Air Quality: " + airQualityClass + ", " + String(airQuality) + "%");
}

void loop(void) {
  // Set a black background
  tft.fillScreen(ST7735_BLACK);

  // Read temperature, humidity, and air quality from sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float airQuality = readAirQuality();

  // Classify air quality
  String airQualityClass = classifyAirQuality(airQuality);

  // Print sensor data on the display
  printData(temperature, humidity, airQuality, airQualityClass);

  // Delay for 1 second before the next iteration
  delay(1000);
}
