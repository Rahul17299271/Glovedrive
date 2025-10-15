# GloveDrive: ESP32 Gesture-Controlled Car

This project allows you to control a two-wheeled robot car using hand gestures. A glove equipped with flex sensors wirelessly transmits commands to the car via Wi-Fi, creating an intuitive and futuristic driving experience. 🚗🖐️

[Image of a gesture controlled car project]

## How It Works

The system consists of two main ESP32-based parts: a transmitter and a receiver.

* **Transmitter (Glove):** An ESP32 mounted on a glove reads analog data from four flex sensors. When a sensor is bent past a defined threshold (`FLEX_THRESHOLD`), it sends a corresponding command ("FORWARD", "BACKWARD", etc.) over a TCP connection to the car's IP address.
* **Receiver (Car):** A second ESP32 on the car chassis hosts a TCP server on port 4080, waiting for a client to connect. When it receives a command from the glove, it controls an L298N motor driver to move the car accordingly.

## Components Required

* 2 x ESP32 Development Boards
* 4 x Flex Sensors
* 1 x L298N Motor Driver Module
* 1 x Robot Car Chassis with 2 DC Motors
* Resistors (4 x 10kΩ for flex sensors, 1 x 220Ω for optional LED)
* Jumper Wires
* Power source for the car (e.g., Li-ion batteries, Power Bank)
* A glove to mount the transmitter components

## Setup and Installation

### 1. Hardware Assembly

**Transmitter (Glove):**
Wire the four flex sensors to the first ESP32. Each sensor requires a **voltage divider circuit** (using a 10kΩ resistor) for accurate readings.
