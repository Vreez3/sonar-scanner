#include <Servo.h>

/*
  Sonar Scanner (original logic preserved)
  - Keeps your original distance calculation: distance = duration * 0.0175
    That multiplier converts the pulse duration (microseconds) into centimeters.
    (duration is the time for the ultrasonic pulse round-trip; your multiplier
     approximates the speed-of-sound conversion to produce distance in cm.)

  Wiring (matches the pins below):
  - Servo signal -> D3
  - HC-SR04 TRIG -> D10
  - HC-SR04 ECHO -> D11
  - RGB LED (common-cathode) R -> D6
  - RGB LED (common-cathode) G -> D5
  - RGB LED (common-cathode) B -> D4
  - Buzzer -> D9
  - All grounds connected together (Arduino GND, servo ground, external supply GND if used)

  Notes:
  - If you use a common-anode RGB LED, invert the HIGH/LOW logic for the LED pins.
  - If the servo causes resets, power the servo from a separate 5V supply and connect grounds.
*/

Servo myservo;

int trig = 10;   // HC-SR04 TRIG pin
int echoPin = 11; // HC-SR04 ECHO pin
int b = 4;       // RGB blue pin
int g = 5;       // RGB green pin
int r = 6;       // RGB red pin
int buzz = 9;    // Buzzer pin

long duration;   // pulse duration in microseconds
float distance;  // calculated distance in centimeters

void setup() {
  // Attach servo and configure pins
  myservo.attach(3);      // servo signal pin
  pinMode(trig, OUTPUT);
  pinMode(echoPin, INPUT);

  // RGB LED pins
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

  // Buzzer pin
  pinMode(buzz, OUTPUT);

  // (Optional) start Serial for debugging - uncomment if you want logs
  // Serial.begin(115200);
}

void loop() {
  // Sweep from 0 to 180
  for (int deg = 0; deg <= 180; deg++) {
    myservo.write(deg);
    delay(10);

    // Trigger the ultrasonic sensor
    digitalWrite(trig, LOW);
    delay(10);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // Read the echo pulse duration (microseconds)
    duration = pulseIn(echoPin, HIGH);

    // Original distance formula preserved:
    // distance (cm) = duration (us) * 0.0175
    // -> your multiplier approximates speed-of-sound conversion to centimeters.
    distance = duration * 0.0175;

    // LED and buzzer logic:
    if (distance > 40) {
      // Green (safe)
      digitalWrite(r, LOW);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW);
      noTone(buzz);
    } else if (distance > 10) {
      // Yellow (caution) => red + green on
      digitalWrite(r, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW);
      tone(buzz, 75); // low tone
    } else {
      // Red (danger)
      digitalWrite(r, HIGH);
      digitalWrite(g, LOW);
      digitalWrite(b, LOW);
      tone(buzz, 800); // higher tone
    }
  }

  // Sweep from 180 back to 0
  for (int deg = 180; deg >= 0; deg--) {
    myservo.write(deg);
    delay(10);

    digitalWrite(trig, LOW);
    delay(10);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echoPin, HIGH);
    // Preserve original conversion to centimeters
    distance = duration * 0.0175;

    if (distance > 40) {
      digitalWrite(r, LOW);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW);
      noTone(buzz);
    } else if (distance > 10) {
      digitalWrite(r, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW);
      tone(buzz, 75);
    } else {
      digitalWrite(r, HIGH);
      digitalWrite(g, LOW);
      digitalWrite(b, LOW);
      tone(buzz, 800);
    }
  }
}