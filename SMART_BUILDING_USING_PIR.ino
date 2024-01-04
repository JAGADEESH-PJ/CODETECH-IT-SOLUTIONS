#include <Servo.h>  // Include the Servo Library
Servo myservo;  // Create servo object to control a servo

bool Open_Door_1;
bool Open_Door_2;

void setup() 
{
  pinMode(12, INPUT);  // Make the 12 pin an INPUT (PIR sensor 1)
  pinMode(9, INPUT);   // Make the 9 pin an INPUT (PIR sensor 2)
  pinMode(8, OUTPUT);  // Make the 8 pin an OUTPUT (LED 1)
  pinMode(13, OUTPUT); // Make the 13 pin an OUTPUT (LED 2)

  myservo.attach(10);  // Attaches the servo on pin 10
  myservo.write(5);    // Tell servo to go to position

  Serial.begin(9600);  // Initialize serial communication
}

void loop() 
{
  int PIR_State_1 = digitalRead(12);  // Read the input pin for PIR sensor 1
  int PIR_State_2 = digitalRead(9);   // Read the input pin for PIR sensor 2

  if (PIR_State_1 == HIGH)   // Check if PIR Sensor 1 Detected Motion
  {
    Open_Door_1 = true;
    Open_Door_2 = false;
    Serial.println("Door opened");  // Print message to virtual terminal
    delay(10);  // 1-second delay
  }
  else if (PIR_State_2 == HIGH)   // Check if PIR Sensor 2 Detected Motion
  {
    Open_Door_1 = false;
    Open_Door_2 = true;
    Serial.println("Light on in room");  // Print message to virtual terminal
    delay(10);  // 1-second delay
  }
  else
  {
    Open_Door_1 = false;
    Open_Door_2 = false;
    digitalWrite(8, LOW);   // Turn OFF LED 1
    digitalWrite(13, LOW);  // Turn OFF LED 2
    myservo.write(5); // Tell servo to go to position
    Serial.println("Door closed / Lights off");  // Print message to virtual terminal
    delay(10);  // 1-second delay
  }

  if (Open_Door_1)
  {
    digitalWrite(8, HIGH);  // Turn ON LED 1
    
    for (int pos = 5; pos <= 93; pos++) // Goes from 0 degrees to 90 degrees
    {
      myservo.write(pos); // Tell servo to go to position in variable 'pos'
      delay(5);   // Waits 5ms for the servo to reach the position
    }

    // Increase LED blinking time to 10 seconds (10000 milliseconds)
    delay(2000);

    digitalWrite(8, LOW);   // Turn OFF LED 1
    myservo.write(15);      // Return servo to the initial position
  }

  if (Open_Door_2)
  {
    digitalWrite(13, HIGH); // Turn ON LED 2

    // Increase LED blinking time to 10 seconds (10000 milliseconds)
    delay(2000);

    digitalWrite(13, LOW);  // Turn OFF LED 2
  }
}
