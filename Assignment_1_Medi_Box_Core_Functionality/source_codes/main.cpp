// UPDATES FOR main.cpp
#include <Arduino.h>
#include "display.h"
#include "time_utils.h"
#include "menu.h"
#include "alarm.h"
#include "pin.h"
#include "temp_sensor.h"
#include <WiFi.h>

void setup() {
    Serial.begin(9600);

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

    connect_wifi();

    display.clearDisplay();
    print_line("Connected to WiFi", 10, 20, 2);
    delay(1000);
    display.clearDisplay();

    configTime(current_utc_offset * 3600, UTC_OFFSET_DST, NTP_SERVER);
    
    setup_temp_sensor();
}

void loop() {
    display.clearDisplay();
    update_time_with_check_alarm();
    
    check_temp();
    
    if (digitalRead(PB_OK) == LOW) {
        delay(200);
        go_to_menu();
    }
    
    // Add a small delay to prevent CPU hogging
    delay(50);
}