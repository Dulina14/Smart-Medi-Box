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
   - Uses an LDR sensor to measure light intensity every \( t_s \) seconds (default: 5s).  
   - Averages readings over a configurable interval \( t_u \) (default: 2 minutes).  
   - Normalized average (range 0–1) is published to the Node-RED dashboard via MQTT (`test.mosquitto.org` broker).  
   - Both \( t_s \) and \( t_u \) are adjustable using sliders in the dashboard.  

2. **Node-RED Dashboard**  
   - Displays the most recent average light intensity numerically and as a time-series chart.  
   - Group 1: Controls for light intensity monitoring (sampling and sending intervals).  
   - Group 2: Controls for shaded window tuning:  
     - **θₒₑₓₜ (Minimum Servo Angle)**: 0–120° (default: 30°)  
     - **γ (Controlling Factor)**: 0–1 (default: 0.75)  
     - **Tₘₑd (Ideal Storage Temperature)**: 10–40°C (default: 30°C)

3. **Servo-Controlled Shaded Window**  
   - A servo motor adjusts the window position to regulate light exposure based on light and temperature.  
   - Angle \( \theta \) is calculated using the equation:
     \[
     \theta = \theta_{\text{offset}} + (180 - \theta_{\text{offset}}) \cdot I \cdot \gamma \cdot \ln\left(\frac{t_s}{t_u}\right) \cdot \frac{T}{T_{\text{med}}}
     \]
     where:
     - \( I \) = normalized light intensity  
     - \( T \) = measured ambient temperature  
     - All parameters are configurable via the dashboard

4. **Temperature Integration**  
   - Uses a DHT11 sensor to continuously monitor internal Medibox temperature.  
   - Temperature value directly contributes to the shaded window angle calculation to maintain safe medicine storage conditions.


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



## 🙏 Acknowledgments

- Developed under guidance of **EN2853 course instructors**  
- Inspired by lab sessions and extended for creative problem solving  
- Thanks to the **University of Moratuwa** for support and infrastructure

---

## 📄 License

This project is licensed under the MIT License. See `LICENSE` file for details.
