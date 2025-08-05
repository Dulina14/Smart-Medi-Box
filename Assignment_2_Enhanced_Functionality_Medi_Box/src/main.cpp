#include <Arduino.h>
#include "display.h"
#include "time_utils.h"
#include "menu.h"
#include "alarm.h"
#include "pin.h"
#include "temp_sensor.h"
#include "ldr_sensor.h"
#include "servo_control.h"
#include "mqtt_client.h"
#include <WiFi.h>

#include <ESP32Servo.h>

// Variables for periodic tasks
unsigned long last_sensor_update = 0;
unsigned long sensor_update_interval = 2000; // Update sensors every 2 seconds

void setup() {
    Serial.begin(115200);

    pinMode(PB_DOWN, INPUT_PULLUP);
    pinMode(PB_UP, INPUT_PULLUP);
    pinMode(PB_OK, INPUT_PULLUP);
    pinMode(PB_CANCEL, INPUT_PULLUP);

    pinMode(BUZZER, OUTPUT);
    pinMode(LED_1, OUTPUT);

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    display.display();
    delay(2000);
    display.clearDisplay();
    print_line("Welcome to Medibox!", 10, 20, 2);
    delay(2000);
    display.clearDisplay();

    // Connect to WiFi
    connect_wifi();

    display.clearDisplay();
    print_line("Connected to WiFi", 10, 20, 2);
    delay(1000);
    display.clearDisplay();

    configTime(current_utc_offset * 3600, UTC_OFFSET_DST, NTP_SERVER);

    // Setup all components
    setup_temp_sensor();
    setup_ldr_sensor();
    setup_servo();
    setup_mqtt();

    display.clearDisplay();
    print_line("All systems ready", 10, 20, 2);
    delay(1000);
    display.clearDisplay();

    setup_temp_sensor();
    setup_ldr_sensor();
    setup_servo();
    setup_mqtt();
    publish_servo_parameters();
}

void loop() {
    display.clearDisplay();
    update_time_with_check_alarm();

    check_temp();

    check_mqtt_connection();

    sample_ldr_reading();

    calculate_and_send_ldr_avg();

    unsigned long current_time = millis();
    if (current_time - last_sensor_update >= sensor_update_interval) {

        float temperature = get_temperature();
        float light_intensity = get_light_intensity();

        update_servo_position(light_intensity, temperature);

        publish_sensor_data();

        last_sensor_update = current_time;
    }

    if (digitalRead(PB_OK) == LOW) {
        delay(200);
        go_to_menu();
    }

    delay(50);
}