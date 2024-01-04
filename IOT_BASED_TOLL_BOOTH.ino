****************************INCLUDING REQUIRED LIBRARIES*************************************

#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal.h>
//Adafruit_LiquidCrystal lcd(0);  // Initialize the LCD
Servo myServo;  // Create a Servo object to control the servo motor
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);  // Initialize the LCD with the appropriate pins
const int buttonPin = 3;  // Pin number for the push button
const int ledPin = 13;    // Pin number for the LED
int buttonState = 0;      // Variable to store the button state
int lastButtonState = 0;  // Variable to store the previous button state
int count = 0;
char c;
String id;
// Function prototypes
void blinkLed(int seconds);
void rotateServo(int fromAngle, int toAngle);
void rotateMotorSequence();
void lcdPrint(String line1, String line2);

****************************SETUP BLOCK CODE*************************************************

void setup() {
  myServo.attach(2);   // Attach the servo to pin 2
  pinMode(buttonPin, INPUT);  // Set the push button pin as INPUT
  pinMode(ledPin, OUTPUT);     // Set the LED pin as OUTPUT
  Serial.begin(9600);  // Initialize the Serial communication
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  lcdPrint("WELCOME TO", "TOLL BOOTH");
  //delay(2000);  // Display the welcome message for 2 seconds
  //lcd.clear();  // Clear the LCD
  Serial.println("Please scan your RFID TAG");
}

****************************LOOP BLOCK CODE***************************************************


void loop() {
  // Check if the push button is pressed (with debouncing)
  int debouncedButtonState = digitalRead(buttonPin);
  if (debouncedButtonState == HIGH && lastButtonState == LOW) {
    // If the button is pressed, toggle the servo position
    if (myServo.read() == 0) {
      rotateServo(0, 90);  // Rotate from 0 to 90 degrees
    } else {
      rotateServo(90, 0);  // Rotate from 90 to 0 degrees
    }
  }
  lastButtonState = debouncedButtonState;  // Save the current debounced button state
  
  // RFID functionality
  while (Serial.available() > 0) {
    c = Serial.read();
    count++;
    id += c;
    if (count == 12) {
      Serial.print("Scanned RFID Tag: " + id);

      // Check for minimum RFID tag length before processing
      if (id.length() >= 12) {
        if (id == "AB123456789A") {
          Serial.println(" - Valid TAG");
          digitalWrite(ledPin, HIGH);
          blinkLed(1);  // Blink the LED for 2 seconds
          rotateMotorSequence();  // Rotate the motor for the valid tag
        
  
          
        } else {
          digitalWrite(ledPin, LOW);
          Serial.println(" - Invalid TAG");
        }
      } else {
        Serial.println(" - Invalid TAG (Insufficient Length)");
      }

      // Reset counters and clear the ID
      count = 0;
      id = "";
    }
  }
 
}
******************************LED CODE******************************************************
void blinkLed(int seconds) {
  digitalWrite(ledPin, HIGH);  // Turn on the LED
  delay(seconds * 1000);        // Blink for specified seconds
  digitalWrite(ledPin, LOW);   // Turn off the LED
}

***************************** MOTOR ROTATION ANGLE CONTROL**********************************

void rotateServo(int fromAngle, int toAngle) {
  // Gradually move the servo from 'fromAngle' to 'toAngle'
  int step = (fromAngle < toAngle) ? 1 : -1;  // Determine the step direction

  for (int angle = fromAngle; angle != toAngle + step; angle += step) {
    myServo.write(angle);  // Set the servo position
    delay(1);              // Wait for the servo to reach the desired position
  }
}
void rotateMotorSequence() {
  // Rotate the motor from initial position to 90 degrees
  for (int angle = 0; angle <= 93; angle++) {
    myServo.write(angle);  // Set the servo position
    delay(30);  // Adjust the delay based on your motor's speed
  }
  
  delay(1000);  // Wait for 1 seconds
  
  
}

***************************DISPLAY FUNTIONALITY***********************************************

void lcdPrint(String line1, String line2) {
  lcd.clear();  // Clear the LCD
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}