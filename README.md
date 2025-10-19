# Sonar Scanner (Arduino UNO R3)

An Arduino UNO R3 project that sweeps an HC‑SR04 ultrasonic sensor on a hobby servo and uses an RGB LED + buzzer to show proximity.

Features
- Uses HC‑SR04 for distance sensing
- Sweeps servo from 0–180° and back
- RGB LED shows proximity: Green (>40 cm), Yellow (10–40 cm), Red (<=10 cm)
- Buzzer tones change with proximity

Hardware (what I used)
- Arduino UNO R3
- HC‑SR04 ultrasonic sensor
- Hobby servo (e.g., SG90)
- Common-cathode RGB LED
- Passive buzzer
- Jumper Wires
- Breadboard

**Features:**  
- Servo sweeps 0° → 180° → 0° continuously  
- RGB LED indicates distance:  
  - **Blue/Green:** Safe  
  - **Yellow (Red + Green):** Medium  
  - **Red:** Close  
- Buzzer alerts for medium and close distances

  
Wiring (matches the sketch)
- Servo signal -> D3
- HC‑SR04 TRIG -> D10
- HC‑SR04 ECHO -> D11
- RGB LED R -> D6
- RGB LED G -> D5
- RGB LED B -> D4
- Buzzer -> D9
- All grounds connected together

Important notes
- The sketch preserves the original conversion used in the provided code: distance = duration * 0.0175, which yields distance in centimeters.
- If the servo causes the Arduino to reset or behave erratically, use a separate 5V supply for the servo and connect grounds.
Videos
[![Demo Video 1](https://img.youtube.com/vi/5Y3a9QMXJlM/0.jpg)](https://youtu.be/5Y3a9QMXJlM)
[![Demo Video 2](https://img.youtube.com/vi/cpp6jHr58mc/0.jpg)](https://youtu.be/cpp6jHr58mc)




License
MIT (see LICENSE file)
