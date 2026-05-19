# WiFi Smart Clock using ESP8266 + 74HC595

A custom-built WiFi synchronized smart clock created completely from scratch using ESP8266, 74HC595 shift register, and a 4-digit 7-segment display.

This project does not use ready-made display driver modules such as TM1637 or MAX7219.
The entire display driver, multiplexing logic, segment mapping, and time synchronization were implemented manually to deeply understand embedded systems architecture.

---

# Features

* WiFi synchronized clock using NTP
* Custom 4-digit 7-segment display driver
* Multiplexed display control
* Shift register GPIO expansion
* Decimal point blinking animation
* Common-anode display support
* Manual segment encoding
* No external display driver libraries used

---

# Hardware Used

* ESP8266 (NodeMCU)
* 74HC595 Shift Register
* 4-Digit 7-Segment Display (Common Anode)
* BC557 PNP Transistors
* 220Ω Resistors
* Capacitors
* Perfboard / PCB

---

# Circuit Overview

## Shift Register Connections

| 74HC595 Pin | ESP8266 |
| ----------- | ------- |
| DS          | D5      |
| SH_CP       | D6      |
| ST_CP       | D7      |

---

## Digit Control Pins

| Digit   | ESP8266 Pin |
| ------- | ----------- |
| Digit 1 | D1          |
| Digit 2 | D2          |
| Digit 3 | D3          |
| Digit 4 | D4          |

---

# Technologies & Concepts Used

* Embedded Systems
* ESP8266 WiFi Programming
* NTP Time Synchronization
* Shift Register Interfacing
* Multiplexing
* Bit Manipulation
* Transistor Switching
* Common-Anode Display Logic
* Hardware Debugging
* Real-Time Display Refreshing

---

# Biggest Challenges

This project involved extensive debugging and low-level hardware troubleshooting.

Some major challenges included:

* Wrong segment mapping
* Incorrect digit outputs
* Ghosting during multiplexing
* Bit-order confusion
* Decimal point logic
* Weak solder joints
* Transistor switching issues
* Display timing synchronization

Each segment and digit had to be tested individually before the final display driver was completed successfully.

---

# How It Works

1. ESP8266 connects to WiFi
2. NTP server provides real-time internet clock
3. Time is split into individual digits
4. Custom multiplexing logic refreshes the display continuously
5. Decimal point blinks like a clock colon

---

# Future Improvements

* PCB version using KiCad
* Alarm support
* Temperature display
* MQTT integration
* Firebase integration
* Smart home dashboard integration
* Edge AI integration

---

# Final Result

Successfully built a fully functional WiFi synchronized smart clock and custom 4-digit display driver completely from scratch without using any dedicated display driver modules or libraries.

---

# Author

Muhammed Hafsal

Embedded Systems & IoT Enthusiast 🚀

<img width="1200" height="1600" alt="clock" src="https://github.com/user-attachments/assets/2644e0b8-a86b-473b-8977-402dcf7b867d" />

