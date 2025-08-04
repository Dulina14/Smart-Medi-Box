# Medibox Simulation for ESP32

## 🩺 Project Overview
This project is a comprehensive simulation of a **Medibox** implemented on the **ESP32 microcontroller** using the **Wokwi** platform within **VS Code** via **PlatformIO**. It was developed for **EN2853: Embedded Systems and Applications** (Assignments 1 and 2) at the University of Moratuwa.

The Medibox assists users in managing their medication schedules effectively by providing timely reminders and maintaining optimal storage conditions for light- and temperature-sensitive medicines.

---

## ✨ Features

### 🧪 Assignment 1: Core Medibox Functionality

1. **Menu Interface**  
   - Set Time Zone (with UTC offset)  
   - Set and delete up to two alarms  
   - View active alarms  

2. **Time Synchronization**  
   - Syncs with NTP server over Wi-Fi  
   - Displays current time on OLED  

3. **Alarm System**  
   - Triggers alarms using LED, buzzer, and OLED  
   - Supports stop/snooze (5 minutes) via push button  

4. **Environmental Monitoring**  
   - Reads temperature and humidity via DHT11/DHT22  
   - Issues warnings if values exceed healthy limits:  
     - Temperature: 24–32°C  
     - Humidity: 65–80%

---

### 🌟 Assignment 2: Enhanced Features

1. **Light Intensity Monitoring**  
   - LDR measures light every \( t_s \) seconds (default: 5s)  
   - Averages readings over \( t_u \) (default: 2 mins)  
   - Normalized (0–1) average sent via MQTT to Node-RED  

2. **Node-RED Dashboard**  
   - Displays current and historical light intensity  
   - Sliders for:  
     - Sampling Interval \( t_s \)  
     - Sending Interval \( t_u \)  
     - Minimum servo angle \( \theta_{\text{offset}} \)  
     - Controlling factor \( \gamma \)  
     - Ideal storage temperature \( T_{\text{med}} \)  

3. **Servo-Controlled Shaded Window**  
   - Controls exposure via motorized servo window  
   - Computes angle \( \theta \) with the formula:
     \[
     \theta = \theta_{\text{offset}} + (180 - \theta_{\text{offset}}) \cdot I \cdot \gamma \cdot \ln\left(\frac{t_s}{t_u}\right) \cdot \frac{T}{T_{\text{med}}}
     \]

4. **Temperature Integration**  
   - Real-time ambient temperature (DHT11) used in servo equation  

---

## 🛠️ Implementation Details

- **Platform**: Wokwi + VS Code + PlatformIO  
- **Microcontroller**: ESP32  
- **Languages**: C++ (Arduino Framework)  
- **Visualization**: Node-RED + MQTT (`test.mosquitto.org`)  
- **Key Components**:
  - OLED display  
  - Buzzer & LED  
  - DHT11/DHT22 sensor  
  - LDR sensor  
  - Servo motor  
  - Push button  
  - ESP32 board  

- **Libraries Used**:
  - Arduino: `WiFi`, `NTPClient`, `Adafruit_SSD1306`, `DHT`, `Servo`  
  - Node-RED: MQTT nodes, Dashboard nodes (gauge, chart, sliders)

---

## 🚀 How to Run

1. **Clone and Setup**  
   - Open in VS Code with PlatformIO installed  
   - Install required Arduino libraries  

2. **Simulation (Wokwi)**  
   - Configure `platformio.ini`  
   - Upload code and simulate using Wokwi  
   - Deploy Node-RED flow from provided JSON  

3. **Test**  
   - Set and test alarms, snooze, and delete functions  
   - Verify environment warnings  
   - View LDR intensity on Node-RED dashboard  
   - Adjust parameters and observe servo control

---

## 📅 Submission Details

### Assignment 1  
- **Due**: March 30, 2025  
- **Submission**: `.zip` with PlatformIO files + 5-min video walkthrough  

### Assignment 2  
- **Due**: May 18, 2025  
- **Submission**: `.zip` (named with index number) including code, Node-RED flow, and a 5-min video walkthrough  

---

## 🧮 Marks Allocation

### Assignment 1 – 30%
- NTP Time Sync: 20%  
- Menu Navigation: 10%  
- Alarm Handling (Set, Ring, Snooze): 40%  
- Environmental Warnings: 10%  
- Creativity & Neatness: 10%  

### Assignment 2 – 20%
- Sensor Readings & Data Transmission: 20%  
- Node-RED Dashboard Setup: 20%  
- Servo Control Logic: 25%  
- Configurable Parameters via MQTT: 25%  
- Creativity & Neatness: 10%

---

## 🙏 Acknowledgments

- Developed under guidance of **EN2853 course instructors**  
- Inspired by lab sessions and extended for creative problem solving  
- Thanks to the **University of Moratuwa** for support and infrastructure

---

## 📄 License

This project is licensed under the MIT License. See `LICENSE` file for details.
