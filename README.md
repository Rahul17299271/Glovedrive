# GloveDrive: ESP32 Gesture-Controlled Car

This project allows you to control a two-wheeled robot car using hand gestures. A glove equipped with flex sensors wirelessly transmits commands to the car via Wi-Fi, creating an intuitive and futuristic driving experience. 🚗🖐️



## How It Works

The system consists of two main ESP32-based parts: a transmitter and a receiver.

* **Transmitter (Glove):** An ESP32 mounted on a glove reads analog data from four flex sensors[cite: 14]. [cite_start]When a sensor is bent past a defined threshold (`FLEX_THRESHOLD`), it sends a corresponding command ("FORWARD", "BACKWARD", etc.) over a TCP connection to the car's IP address[cite: 19, 20].
* **Receiver (Car):** A second ESP32 on the car chassis hosts a TCP server on port 4080[cite: 1], waiting for a client to connect. [cite_start]When it receives a command from the glove, it controls an L298N motor driver to move the car accordingly[cite: 7, 9, 10, 11].

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

| Flex Sensor Function | Glove ESP32 Pin |
| :------------------- | :-------------: |
| Forward              |     GPIO 34     |
| Backward             |     GPIO 35     |
| Clockwise (Right)    |     GPIO 32     |
| Anti-Clockwise (Left)|     GPIO 33     |



**Receiver (Car):**
Connect the second ESP32 to the L298N motor driver.

| Car ESP32 Pin | L298N Motor Driver Pin |
| :-----------: | :--------------------: |
|    GPIO 32    |          IN1           |
|    GPIO 33    |          IN2           |
|    GPIO 18    |          IN3           |
|    GPIO 19    |          IN4           |
|    GPIO 26    |          ENA           |
|    GPIO 27    |          ENB           |
|    GPIO 2     | Connection Status LED  |

### 2. Software Setup

1.  **Install Arduino IDE:** Ensure you have the Arduino IDE and the ESP32 board manager installed.
2.  **Install Libraries:** From the Arduino Library Manager, install `ESPAsyncWebServer` and its dependency, `AsyncTCP`.
3.  [cite_start]**Configure Wi-Fi Credentials:** In both `Car_working.ino` and `Glove_working.ino`, update the `ssid` and `password` variables with your Wi-Fi network details[cite: 1, 12].

    ```cpp
    const char* ssid = "YOUR_WIFI_SSID";
    const char* password = "YOUR_WIFI_PASSWORD";
    ```

### 3. Upload the Code

This is a two-step process:

1.  **Upload to Car (Receiver):**
    * Connect the **car's ESP32** to your computer.
    * Open `Car_working.ino` and upload the code.
    * Open the **Serial Monitor** at a baud rate of `115200`.
    * [cite_start]Wait for it to connect to your Wi-Fi[cite: 4]. It will print its IP address. **Copy this IP address.**

2.  **Upload to Glove (Transmitter):**
    * Open `Glove_working.ino`.
    * [cite_start]Update the `serverIP` variable with the IP address you copied from the car's serial monitor[cite: 13].

        ```cpp
        const char* serverIP = "192.168.X.X"; // <-- The IP address of your Car ESP32
        ```
    * Connect the **glove's ESP32** to your computer and upload the code.

## Usage

1.  Power on the car. [cite_start]The car's ESP32 will connect to Wi-Fi and start the TCP server[cite: 8].
2.  Power on the glove. [cite_start]It will connect to the Wi-Fi and then to the car's server[cite: 15, 17]. An onboard LED on pin 2 will light up when the glove connects.
3.  Control the car by bending your fingers:
    * **Bend front finger:** Move Forward
    * **Bend back finger:** Move Backward
    * **Bend clockwise finger:** Turn Right
    * **Bend anti-clockwise finger:** Turn Left
    * **Keep hand straight:** Stop

A `delay(2000)` is present in the glove's code, so there is a 2-second interval between commands. You can adjust this value for more responsive control.
