# Arduino Smart Home Mini Controller

A **Smart Home Mini Controller** using Arduino that automates home devices based on sensor inputs. This project demonstrates **motion detection, ambient light monitoring, temperature alerting**, and includes a **manual override** mode with a push button. Ideal for **learning embedded systems, sensor integration, and basic IoT concepts**.

---
## Features

* **Automatic Mode:**

  * Motion detected → buzzer alert
  * Low light → LED turns ON (simulating a lamp)
  * High temperature → buzzer alert

* **Manual Mode:**

  * Push button toggles auto/manual mode
  * Allows manual control of LEDs and buzzer

* **Indicators:**

  * LED1 → Auto mode ON
  * LED2 → Device active ON (light/buzzer)

* **Real-time Monitoring:**

  * Serial Monitor displays sensor readings for debugging

---

## Components Required

| Component                 | Purpose                     | Arduino Pin |
| ------------------------- | --------------------------- | ----------- |
| PIR Sensor                | Detect motion               | D2          |
| LDR (Light Sensor)        | Detect ambient light        | A0          |
| Temperature Sensor (LM35) | Monitor temperature         | A1          |
| Push Button               | Toggle auto/manual mode     | D3          |
| LED1                      | Auto mode indicator         | D9          |
| LED2                      | Device active indicator     | D10         |
| Buzzer                    | Alert on motion/temperature | D11         |
| Resistors                 | Pull-up/current limiting    | -           |

---

## Circuit Diagram

![Circuit Diagram](circuit.png)

---

## How It Works

1. System starts in **Auto Mode** → LED1 ON
2. **Sensors Monitor Environment:**

   * PIR → Motion detection → buzzer alert
   * LDR → Low light → LED2 ON
   * Temperature sensor → High temperature → buzzer alert
3. **Manual Override:** Press the push button to switch between auto and manual mode
4. **Device Indicators:** LED2 reflects any active device
5. **Serial Monitor:** Displays motion, light, and temperature readings for debugging

---

## Code Overview

* `setup()`: Initializes pins, serial communication, and variables
* `loop()`: Reads sensor values, updates outputs, handles button toggling, and prints sensor values
* **Debouncing:** Prevents false toggles from push button
* **Thresholds:** Adjustable for light (LDR) and temperature sensors

---

## Learning Outcomes

* Integrating multiple sensors (PIR, LDR, LM35)
* Using analog and digital pins effectively
* Implementing auto/manual mode toggling
* Controlling LEDs and buzzer based on sensor data
* Debugging with Serial Monitor
* Preparing a GitHub-ready project with documentation and visuals

---

## Future Extensions

* Add more sensors (humidity, gas, smoke)
* Integrate Wi-Fi/Bluetooth for remote control
* Expand automation logic for multiple rooms or devices

---

## Usage Instructions

1. Connect components according to the circuit diagram
2. Upload `SmartHomeController.ino` to Arduino
3. Open Serial Monitor at **9600 baud** to view sensor readings
4. Press the push button to toggle between **auto** and **manual** mode

---



