#!/usr/bin/env python3
"""
Simple live plotter for sonar scanner CSV output: angle,distance_cm,status
Usage: python scripts/plot_serial.py --port /dev/ttyUSB0
Requires: pyserial, matplotlib
"""

import argparse
import sys
import serial
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation

parser = argparse.ArgumentParser()
parser.add_argument("--port", required=True, help="Serial port e.g. COM3 or /dev/ttyUSB0")
parser.add_argument("--baud", type=int, default=115200)
parser.add_argument("--timeout", type=float, default=1.0)
args = parser.parse_args()

try:
    ser = serial.Serial(args.port, args.baud, timeout=args.timeout)
except Exception as e:
    print("Could not open serial port:", e)
    sys.exit(1)

angles = np.arange(0, 181)
distances = np.full_like(angles, np.nan, dtype=float)

fig, ax = plt.subplots()
line, = ax.plot(angles, distances, marker='o', linestyle='-')
ax.set_xlim(0, 180)
ax.set_ylim(0, 400)
ax.set_xlabel("Angle (deg)")
ax.set_ylabel("Distance (cm)")
ax.set_title("Sonar Scanner Live")

def update(frame):
    global distances
    try:
        raw = ser.readline().decode('utf-8', errors='ignore').strip()
    except Exception:
        return line,
    if not raw:
        return line,
    # Expect "angle,distance,status"
    parts = raw.split(",")
    if len(parts) < 2:
        return line,
    try:
        angle = int(float(parts[0]))
        dist_str = parts[1]
        if dist_str.lower() == "nan":
            value = np.nan
        else:
            value = float(dist_str)
        if 0 <= angle <= 180:
            distances[angle] = value
            line.set_ydata(distances)
    except Exception:
        pass
    return line,

ani = FuncAnimation(fig, update, interval=50, blit=True)
plt.show()
ser.close()