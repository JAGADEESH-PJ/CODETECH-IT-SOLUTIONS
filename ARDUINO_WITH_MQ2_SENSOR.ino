#include <LiquidCrystal.h>

#define BUZZER_PIN  13
#define PIN_LED_1 	6
#define PIN_LED_2 	5
#define PIN_LED_3 	4
#define PIN_LED_4 	3
#define PIN_LED_5 	2
#define PIN_GAS 	A0

LiquidCrystal lcd(7, 8, 9, 10, 11,12); // Adjust these pin numbers based on your LCD wiring

void setup() {
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);
  pinMode(PIN_LED_5, OUTPUT);
  lcd.begin(16, 2);  // Adjust the dimensions based on your LCD (cols, rows)
  Serial.begin(9600);
}

void loop() {
  long frequency;
  int value = map(analogRead(PIN_GAS), 300, 750, 0, 100);

  digitalWrite(PIN_LED_1, HIGH);
  digitalWrite(PIN_LED_2, value >= 20 ? HIGH : LOW);
  digitalWrite(PIN_LED_3, value >= 40 ? HIGH : LOW);
  digitalWrite(PIN_LED_4, value >= 60 ? HIGH : LOW);
  digitalWrite(PIN_LED_5, value >= 80 ? HIGH : LOW);

  frequency = map(value, 0, 1023, 1500, 2500);

  if (value >= 50) {
    tone(BUZZER_PIN, frequency, 250);
  }

 lcd.clear();
if (digitalRead(PIN_LED_5) == HIGH) {
  lcd.print("Smoke level 100%");
} else if (digitalRead(PIN_LED_4) == HIGH) {
  lcd.print("Smoke level 70%");
} else if (digitalRead(PIN_LED_3) == HIGH) {
  lcd.print("Smoke level 50%");
} else if (digitalRead(PIN_LED_2) == HIGH) {
  lcd.print("Smoke level 30%");
} else if (digitalRead(PIN_LED_1) == HIGH && digitalRead(PIN_LED_2) == LOW &&
           digitalRead(PIN_LED_3) == LOW && digitalRead(PIN_LED_4) == LOW &&
           digitalRead(PIN_LED_5) == LOW) {
  lcd.print("POWER ON");
}


  Serial.println(value);
  delay(250);
}
