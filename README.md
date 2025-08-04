# Medibox Simulation for ESP32

## Project Overview
This project is a comprehensive simulation of a **Medibox** implemented on the **ESP32** microcontroller using the **Wokwi** platform within **VS Code** via **PlatformIO**, enhanced with additional features as part of **EN2853: Embedded Systems and Applications Programming Assignments 1 and 2** at the University of Moratuwa. The Medibox is designed to assist users in managing their medication schedules effectively by providing timely reminders and maintaining optimal storage conditions for light- and temperature-sensitive medicines. The project was submitted in two phases: Assignment 1 on March 30, 2025, and Assignment 2 on May 18, 2025.

## Features
The Medibox simulation encompasses the following functionalities, divided into two phases as per the assignments:

### Assignment 1: Core Medibox Functionality
1. **Menu Interface**:
   - **Set Time Zone**: Configures the local time zone by accepting a UTC offset input.
   - **Set Alarms**: Supports setting up to two alarms for medication reminders.
   - **View Active Alarms**: Displays the currently set alarms.
   - **Delete Alarm**: Allows deletion of a specific alarm.
2. **Time Synchronization**:
   - Fetches the current time from an NTP server over Wi-Fi and displays it on an OLED screen.
3. **Alarm Functionality**:
   - Triggers alarms at set times with visual (LED), audible (buzzer), and OLED message indications.
   - Supports stopping the alarm or snoozing it for 5 minutes using a push button.
4. **Environmental Monitoring**:
   - Monitors temperature and humidity using a DHT11/DHT22 sensor.
   - Issues warnings (via LED, buzzer, or OLED messages) when values exceed healthy limits:
     - **Healthy Temperature**: 24°C ≤ Temperature ≤ 32°C
     - **Healthy Humidity**: 65% ≤ Humidity ≤ 80%

### Assignment 2: Enhanced Medibox Functionality
1. **Light Intensity Monitoring**:
   - Uses a Light Dependent Resistor (LDR) to measure light intensity at configurable intervals (default: 5 seconds).
   - Averages LDR readings over a configurable period (default: 2 minutes) and sends the average to a Node-RED dashboard via MQTT (using `test.mosquitto.org` as the broker).
   - Normalizes light intensity values to a range of 0 to 1 (0 = minimum, 1 = maximum).
2. **Node-RED Dashboard Integration**:
   - Displays light intensity data in a dedicated group:
     - Numerical display for the most recent average light intensity.
     - A chart to visualize historical average light intensity values over time.
     - Two sliders to adjust:
       - Sampling interval (\(t_s\)) in seconds.
       - Sending interval (\(t_u\)) in seconds or minutes.
   - A separate group with three sliders to configure:
     - Minimum servo angle (\(\theta_{\text{offset}}\)): 0 to 120 degrees (default: 30 degrees).
     - Controlling factor (\(\gamma\)): 0 to 1 (default: 0.75).
     - Ideal storage temperature (\(T_{\text{med}}\)): 10°C to 40°C (default: 30°C).
3. **Shaded Sliding Window Control**:
   - Adjusts light exposure using a servo motor connected to a shaded sliding window, with angles ranging from 0 to 180 degrees.
   - Calculates the servo angle (\(\theta\)) using the equation:
     \[
     \theta = \theta_{\text{offset}} + \left(180 - \theta_{\text{offset}}\right) \times I \times \gamma \times \ln\left(\frac{t_s}{t_u}\right) \times \frac{T}{T_{\text{med}}}
     \]
     where:
     - \(\theta\): Motor angle.
     - \(\theta_{\text{offset}}\): Minimum angle (configurable).
     - \(I\): Normalized light intensity (0 to 1).
     - \(\gamma\): Controlling factor (configurable).
     - \(t_s\): Sampling interval (configurable).
     - \(t_u\): Sending interval (configurable).
     - \(T\): Measured temperature (from DHT11).
     - \(T_{\text{med}}\): Ideal storage temperature (configurable).
4. **Temperature Monitoring**:
   - Uses a DHT11 sensor to measure ambient temperature inside the storage area, integrated into the servo angle calculation.

## Implementation Details
- **Platform**: Wokwi simulation environment integrated within VS Code using PlatformIO.
- **Hardware Components**:
  - ESP32 microcontroller.
  - OLED display (for time and message display).
  - Push button (for alarm control).
  - Buzzer and LED (for alarm and warning indications).
  - DHT11/DHT22 sensor (for temperature and humidity).
  - Light Dependent Resistor (LDR) (for light intensity).
  - Servo motor (for controlling the shaded sliding window).
- **Software**:
  - Written in **C++** using the Arduino framework for ESP32 logic, managed via PlatformIO in VS Code.
  - Node-RED for dashboard visualization and MQTT communication.
  - Libraries used:
    - Arduino: WiFi, NTPClient, Adafruit_SSD1306, DHT, Servo.
    - Node-RED: MQTT nodes, dashboard nodes (gauge, chart, sliders).
  - MQTT broker: `test.mosquitto.org`.
- **Design Approach**:
  - Modular code structure for menu navigation, time synchronization, alarm management, environmental monitoring, and light intensity control.
  - Dynamic servo control based on real-time environmental data and user-configurable parameters.
  - Efficient MQTT communication for sending and receiving data between ESP32 and Node-RED.
  - Creative use of visual (OLED, LED, Node-RED dashboard) and audible (buzzer) feedback for an enhanced user experience.

## How to Run
1. **Access the Project**:
   - Clone this repository to your local machine.
   - Open the project in VS Code with the PlatformIO extension installed.
2. **Dependencies**:
   - Install PlatformIO in VS Code.
   - Arduino libraries (included in `platformio.ini`): WiFi, NTPClient, Adafruit_SSD1306, DHT, Servo.
   - Node-RED nodes: MQTT, dashboard (gauge, chart, sliders).
3. **Simulation**:
   - Configure the Wokwi simulation environment within PlatformIO by setting up the `platformio.ini` file to target the ESP32.
   - Upload the Arduino code to the ESP32 using PlatformIO.
   - Deploy the Node-RED flow (provided as a JSON file) in a Node-RED instance.
   - Interact with the menu using simulated inputs (e.g., buttons or serial monitor in Wokwi).
   - Access the Node-RED dashboard to view light intensity data and adjust parameters.
4. **Testing**:
   - Verify time synchronization with the NTP server.
   - Test alarm functionality (set, view, delete, stop, snooze).
   - Monitor temperature and humidity warnings.
   - Validate LDR data averaging and display on the Node-RED dashboard.
   - Confirm servo motor angle adjustments based on the provided equation and user inputs.

## Submission Details
### Assignment 1
- **Course**: EN2853: Embedded Systems and Applications
- **Due Date**: March 30, 2025
- **Components**:
  - PlatformIO project files for Wokwi simulation.
  - A 5-minute video walkthrough explaining code structure, key functions, and feature implementation.
  - Submitted as a `.zip` file via Moodle.

### Assignment 2
- **Due Date**: May 18, 2025
- **Components**:
  - Arduino code for ESP32 (PlatformIO project).
  - Node-RED flow as a JSON file.
  - A 5-minute video walkthrough explaining code, Node-RED setup, and feature implementation.
  - Submitted as a `.zip` file named `XXXXX.zip` (where XXXXX is the index number) via Moodle.

## Marks Allocation
### Assignment 1 (30% of final grade)
- Fetching and displaying time from NTP server: 20%
- Menu navigation: 10%
- Setting time zone: 10%
- Setting and viewing alarms: 10%
- Alarm ringing, stopping, and snoozing: 20%
- Deleting alarms: 10%
- Temperature and humidity warnings: 10%
- Creativity and neatness: 10%

### Assignment 2 (20% of final grade)
- Taking LDR input properly: 5%
- Taking DHT11 temperature input properly: 5%
- Adjusting sampling and sending intervals of LDR: 15%
- Sending LDR data to the dashboard via MQTT: 5%
- Visualizing light intensity with a plot and gauge: 5%
- Setting up a servo motor properly: 10%
- Programming ESP32 to control the servo angle with the given equation: 15%
- Setting sliders in the Node-RED dashboard for controlling parameters: 10%
- Sending parameters to ESP32 and applying them to the equation: 20%
- Creativity and neatness: 10%

## Acknowledgments
- This project was developed based on concepts and demonstrations provided during weeks 2 and 3 of the EN2853 course, with enhancements from subsequent lectures.
- Special thanks to the University of Moratuwa for providing resources and guidance for both assignments.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.
