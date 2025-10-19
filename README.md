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

Quick start
1. Open src/sonar_scanner.ino in the Arduino IDE.
2. Select Arduino UNO, set the correct COM port, and upload.
3. Power the circuit and observe the LED and buzzer behavior as the sensor sweeps.

Files
- src/sonar_scanner.ino — Arduino sketch (original logic preserved with added comments)
- scripts/plot_serial.py — optional live plotter (not required by the sketch as-is)
- CONTRIBUTING.md — contribution guidelines
- LICENSE — MIT license

License
MIT (see LICENSE file)