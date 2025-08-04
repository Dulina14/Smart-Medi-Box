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
     - Tem
