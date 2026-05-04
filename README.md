# Line Following Robot (LFR) - Arduino Control System

## Overview

This project implements an autonomous line-following robot using an Arduino-compatible microcontroller. The robot uses a 5-sensor array to detect and follow a line, with support for various junction types including 90-degree turns, T-junctions, and complex cross patterns. The system features PID-based motor control for smooth line tracking and includes a servo mechanism for auxiliary functions.

## Hardware Requirements

### Microcontroller
- Arduino-compatible board (Uno, Nano, Mega, etc.)

### Sensors
- 5x IR/optical line sensors (digital output)
- Sensor positions (left to right): L2, L1, M, R1, R2

### Actuators
- 2x DC motors with wheel encoders (optional)
- 1x Servo motor (for auxiliary mechanisms)

### Motor Driver
- Dual H-bridge motor driver (L298N or similar)

### Additional Components
- 1x Push button (start control)
- 1x LED indicator
- Power supply appropriate for motors and logic

## Pin Configuration

| Component | Pin | Description |
|-----------|-----|-------------|
| **Sensors** |||
| Sensor R2 | A0 | Far-right line sensor |
| Sensor R1 | A1 | Right-center line sensor |
| Sensor M | A2 | Center line sensor |
| Sensor L1 | A3 | Left-center line sensor |
| Sensor L2 | A4 | Far-left line sensor |
| **Motor A (Right)** |||
| PWM A | 3 | Right motor speed control |
| A1 | 2 | Right motor direction 1 |
| A2 | 4 | Right motor direction 2 |
| **Motor B (Left)** |||
| PWM B | 5 | Left motor speed control |
| B1 | 6 | Left motor direction 1 |
| B2 | 7 | Left motor direction 2 |
| **Controls** |||
| Button | 11 | Start button (INPUT_PULLUP) |
| LED | 13 | Status indicator |
| Servo | 12 | Auxiliary servo control |

## Sensor Logic

The 5-sensor array provides the following line detection states:

| State | Description | Robot Action |
|-------|-------------|--------------|
| `11111` | All sensors on line | White area/junction detected |
| `11011` | Center only off line | Move forward (centered) |
| `00111` | Left side off line | Right turn correction |
| `11100` | Right side off line | Left turn correction |
| `10011` | Edge of line | Sharp right correction |
| `11001` | Edge of line | Sharp left correction |

*(1 = on line, 0 = off line)*

## Features

### Junction Handling
- **90-Degree Turns**: Automatic detection and execution of left/right turns at perpendicular junctions
- **T-Junctions**: Configurable default direction (left/right/stop)
- **Side Cross Detection**: Optional handling of L-shaped junctions
- **60-Degree Turns**: Partial junction navigation with forward movement before turning

### Control Modes
- **PID-Based Tracking**: Proportional speed adjustments based on sensor offset
- **White Area Navigation**: Configurable behavior when all sensors detect white surface
- **T-Junction Decision**: Programmable turn preference at T-intersections

### Safety & Feedback
- LED status indication during junction detection
- Emergency stop on unrecognized junction patterns
- Debounced button start sequence

## Configuration Parameters

Modify these variables in the code to customize robot behavior:

```cpp
int speed = 150;        // Base forward speed (0-255)
int pidSpeed = 100;     // PID correction speed
int base = 25;          // Base PID adjustment value

char white = "r";       // White area behavior: "r" = right, "l" = left
char tShape = "r";      // T-junction behavior: "r" = right, "l" = left, other = stop
char sideCross = "s";   // Side cross junction handling: "s" = enabled
