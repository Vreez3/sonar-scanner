// --------------------------------------------------------
//  Arduino Sonar Scanner Project
//  Author: Ahmad Faheem
//  Description: A servo-mounted ultrasonic sensor that scans
//  from 0° to 180° and back, detecting distance and signaling
//  through RGB LEDs and a buzzer.
//
//  Hardware:
//    - Arduino UNO
//    - HC-SR04 Ultrasonic Sensor
//    - SG90 Servo Motor
//    - RGB LED (Red, Green, Blue)
//    - Buzzer
//    - Jumper Wires & Breadboard
//
//  Version: 1.0
//  License: MIT License
// --------------------------------------------------------

#include <Servo.h>     // Include the Servo library to control the servo motor

// --- Component and pin setup ---
Servo myservo;         // Servo object to control the scanning motor
int trig = 10;         // Ultrasonic sensor trigger pin
int echo = 11;         // Ultrasonic sensor echo pin
int b = 4;             // Blue LED pin (Safe distance)
int g = 5;             // Green LED pin (Medium distance)
int r = 6;             // Red LED pin (Close distance)
int buzz = 9;          // Buzzer pin

// --- Variables for distance measurement ---
long duration;         // Stores the time taken for the ultrasonic pulse to return
float distance;        // Calculated distance in centimeters

void setup() {
  // Attach the servo to digital pin 3
  myservo.attach(3);

  // Set up pins for input and output
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(buzz, OUTPUT);
}

// --------------------------------------------------------
//  Main loop: sweeps the servo left to right and back
//  Measures distance and provides LED + buzzer feedback
// --------------------------------------------------------
void loop() {

  // --- Sweep from 0° to 180° ---
  for (int deg = 0; deg <= 180; deg++) {
    myservo.write(deg);  // Move servo to the current degree
    delay(10);           // Small delay to let servo reach position

    // Trigger ultrasonic sensor pulse
    digitalWrite(trig, LOW);
    delay(10);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // Read the echo time
    duration = pulseIn(echo, HIGH);

    // Convert time to distance (speed of sound: 0.034 cm/μs, divide by 2)
    distance = duration * 0.0175;

    // --- LED and buzzer feedback based on distance ---
    if (distance > 40) {
      // Safe distance: Green LED ON
      digitalWrite(r, LOW);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW);
      noTone(buzz); // No sound
    }
    else if (distance > 10) {
      // Medium distance: Yellow (Red + Green)
      digitalWrite(r, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW);
      tone(buzz, 75); // Low buzzer tone
    }
    else {
      // Close distance: Red LED ON + High buzzer tone
      digitalWrite(r, HIGH);
      digitalWrite(g, LOW);
      digitalWrite(b, LOW);
      tone(buzz, 800);
    }
  }

  // --- Sweep from 180° back to 0° ---
  for (int deg = 180; deg >= 0; deg--) {
    myservo.write(deg);
    delay(10);

    // Trigger ultrasonic sensor pulse again
    digitalWrite(trig, LOW);
    delay(10);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // Read and calculate distance
    duration = pulseIn(echo, HIGH);
    distance = duration * 0.0175;

    // --- LED and buzzer feedback based on distance ---
    if (distance > 40) {
      digitalWrite(r, LOW);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW);
      noTone(buzz);
    }
    else if (distance > 10) {
      digitalWrite(r, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW);
      tone(buzz, 75);
    }
    else {
      digitalWrite(r, HIGH);
      digitalWrite(g, LOW);
      digitalWrite(b, LOW);
      tone(buzz, 800);
    }
  }
}
