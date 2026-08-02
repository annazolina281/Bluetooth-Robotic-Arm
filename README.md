# Bluetooth Robotic Arm

![Platform](https://img.shields.io/badge/Platform-Arduino-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B-orange)
![License](https://img.shields.io/badge/License-MIT-green)

## Overview

The **Bluetooth Robotic Arm** is an Arduino Mega based embedded robotics
project that combines a mobile platform with a multi-servo robotic arm.
The system accepts serial/Bluetooth commands to drive the robot, rotate
the arm, extend joints, and operate a claw.

This project demonstrates:

-   Embedded systems programming
-   PWM motor control
-   Multi-servo coordination
-   Differential drive
-   Serial/Bluetooth communication
-   Modular Arduino programming

------------------------------------------------------------------------

## Features

-   Bluetooth serial control
-   Differential drive (Forward, Backward, Left, Right)
-   Smooth servo movement
-   Multi-position arm control
-   Claw open/close control
-   Expandable software architecture

------------------------------------------------------------------------

## Hardware

  Component                            Qty
  ---------------------------------- -----
  Arduino Mega                           1
  DC Motors                              4
  L298D Motor Driver                     1
  PCA9685 Servo Driver                   1
  MG996 Servo                            4
  SG96 Servo                             2
  SG90 Servo                             1
  IR Remote / Bluetooth Controller       1

------------------------------------------------------------------------

## Pin Configuration

  Arduino Pin   Function
  ------------- -----------------------
  D2            Left Motor Direction
  D5            Left Motor PWM
  D4            Right Motor Direction
  D6            Right Motor PWM
  D8            Claw Servo
  D9            Up/Down Servo
  D10           Base Servo
  D11           Extend Servo
  D12           Wrist Servo

------------------------------------------------------------------------

## Project Structure

``` text
Bluetooth-Robotic-Arm/
├── README.md
├── code/
│   └── RoboticArm.ino
├── docs/
├── hardware/
├── images/
└── media/
```

------------------------------------------------------------------------

## Command Reference

  Command   Action
  --------- -------------
  F         Forward
  B         Backward
  L         Turn Left
  R         Turn Right
  P         Close Claw
  A         Open Claw
  C         Rotate Base
  X         Lift Arm
  T         Extend Arm
  S         Move Wrist

------------------------------------------------------------------------

## Software Flow

``` text
Power On
   │
Initialize Hardware
   │
Wait for Serial/Bluetooth Command
   │
Parse Command
   ├── Drive Robot
   ├── Move Servo
   └── Control Claw
   │
Repeat
```

------------------------------------------------------------------------

## Motion Control

The left and right DC motors are controlled independently using PWM for
speed and digital outputs for direction. Turning is achieved by reducing
the speed of one side while maintaining the other.

## Servo Control

Each servo moves between predefined positions. A smooth interpolation
routine gradually changes the angle to reduce sudden movement and
mechanical stress.

## Required Library

-   Servo.h (built into the Arduino IDE)

## Installation

1.  Install the Arduino IDE.
2.  Connect the Arduino Mega.
3.  Open `RoboticArm.ino`.
4.  Select the correct board and COM port.
5.  Upload the sketch.

## Testing

The project was tested for:

-   Forward/backward movement
-   Turning accuracy
-   Servo positioning
-   Claw operation
-   Continuous operation
-   Basic power stability

## Future Improvements

-   Obstacle detection
-   Inverse kinematics
-   Joystick control
-   Mobile app interface
-   Camera integration
-   Voice control

## Gallery

Place project images in the `images/` folder.

Example:

``` text
images/
├── robotic_arm.jpg
├── wiring.png
├── schematic.png
└── demo.gif
```

## License

MIT License.

## Authors

Developed as a Computer Engineering embedded systems laboratory project.
