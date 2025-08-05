#include "menu.h"
#include "display.h"
#include "alarm.h"
#include "pin.h"
#include "time_utils.h"
#include "temp_sensor.h"

extern int current_mode;
extern int max_mode;
extern String modes[];
extern unsigned int hours, minutes;
extern unsigned int alarm_hours[];
extern unsigned int alarm_minutes[];
extern bool alarm_enabled;
extern bool alarm_active[];
extern int n_alarms;
extern float current_utc_offset;

void display_temperature() {
    bool exit_to_menu = false;
    
    while (!exit_to_menu) {
        display.clearDisplay();
        float temp = get_temperature();
        float humidity = get_humidity();
        
        // Display temperature and humidity
        print_line("Temp: " + String(temp, 1) + "C", 10, 10, 1);
        print_line("Humidity: " + String(humidity, 1) + "%", 10, 30, 1);
        print_line("Press Cancel to exit", 10, 50, 1);
        
        // Check for Cancel button to exit
        if (digitalRead(PB_CANCEL) == LOW) {
            delay(200);
            exit_to_menu = true;
        }
        
        delay(500);  // Update every half second
    }
}

int wait_for_button_press() {
    while (true) {
        if (digitalRead(PB_UP) == LOW) { delay(200); return PB_UP; }
        if (digitalRead(PB_DOWN) == LOW) { delay(200); return PB_DOWN; }
        if (digitalRead(PB_OK) == LOW) { delay(200); return PB_OK; }
        if (digitalRead(PB_CANCEL) == LOW) { delay(200); return PB_CANCEL; }
        update_time();
        delay(10);  // Small delay to prevent CPU hogging
    }
}

void set_time() {
    int temp_hours = hours;
    int temp_minutes = minutes;
    bool exit_to_menu = false;
    
    while (!exit_to_menu) {
        display.clearDisplay();
        print_line("Enter hour: " + String(temp_hours), 10, 20, 2);
        int button_pressed = wait_for_button_press();
        if (button_pressed == PB_UP) temp_hours = (temp_hours + 1) % 24;
        else if (button_pressed == PB_DOWN) temp_hours = (temp_hours == 0) ? 23 : temp_hours - 1;
        else if (button_pressed == PB_OK) { hours = temp_hours; break; }
        else if (button_pressed == PB_CANCEL) { exit_to_menu = true; break; }
    }
    
    if (!exit_to_menu) {
        while (true) {
            display.clearDisplay();
            print_line("Enter minutes: " + String(temp_minutes), 10, 20, 2);
            int button_pressed = wait_for_button_press();
            if (button_pressed == PB_UP) temp_minutes = (temp_minutes + 1) % 60;
            else if (button_pressed == PB_DOWN) temp_minutes = (temp_minutes == 0) ? 59 : temp_minutes - 1;
            else if (button_pressed == PB_OK) { minutes = temp_minutes; break; }
            else if (button_pressed == PB_CANCEL) break;
        }
        display.clearDisplay();
        print_line("Time set!", 10, 20, 2);
        delay(1000);  // Show confirmation message for 1 second
    }
}

void set_utc_offset_menu() {
    float temp_offset = current_utc_offset;
    bool exit_to_menu = false;
    
    while (!exit_to_menu) {
        display.clearDisplay();
        print_line("UTC Offset:", 10, 10, 2);
        print_line(temp_offset >= 0 ? "+" + String(temp_offset) : String(temp_offset), 10, 30, 3);
        print_line("Up/Down to change", 10, 55, 1);
        
        int button_pressed = wait_for_button_press();
        if (button_pressed == PB_UP) {
            temp_offset = (temp_offset + 0.5 > 12) ? -12 : temp_offset + 0.5;
        }
        else if (button_pressed == PB_DOWN) {
            temp_offset = (temp_offset - 0.5 < -12) ? 12 : temp_offset - 0.5;
        }
        else if (button_pressed == PB_OK) {
            set_utc_offset(temp_offset);
            display.clearDisplay();
            print_line("Offset set to:", 10, 10, 1);
            print_line(temp_offset >= 0 ? "+" + String(temp_offset) : String(temp_offset), 10, 30, 2);
            delay(1000);
            exit_to_menu = true;
        }
        else if (button_pressed == PB_CANCEL) {
            exit_to_menu = true;
        }
    }
}

void view_alarms() {
    bool exit_to_menu = false;
    
    while (!exit_to_menu) {
        display.clearDisplay();
        print_line("Active Alarms:", 10, 0, 1);
        
        bool has_active_alarms = false;
        for (int i = 0; i < n_alarms; i++) {
            if (alarm_active[i]) {
                has_active_alarms = true;
                String alarm_text = "Alarm " + String(i+1) + ": " + 
                                    (alarm_hours[i] < 10 ? "0" : "") + String(alarm_hours[i]) + ":" + 
                                    (alarm_minutes[i] < 10 ? "0" : "") + String(alarm_minutes[i]);
                print_line(alarm_text, 10, 12 + (i * 10), 1);
            }
        }
        
        if (!has_active_alarms) {
            print_line("No active alarms", 10, 20, 1);
        }
        
        print_line("Alarm is " + String(alarm_enabled ? "enabled" : "disabled"), 10, 40, 1);
        print_line("Press Cancel to exit", 10, 55, 1);
        
        // Check for Cancel button to exit
        if (digitalRead(PB_CANCEL) == LOW) {
            delay(200);
            exit_to_menu = true;
        }
        
        delay(100);
    }
}

void delete_alarms() {
    bool exit_to_menu = false;
    int current_alarm = 0;
    
    while (!exit_to_menu) {
        display.clearDisplay();
        
        String status = alarm_active[current_alarm] ? "ACTIVE" : "DISABLED";
        print_line("Alarm " + String(current_alarm + 1) + ": " + status, 10, 10, 1);
        
        if (alarm_active[current_alarm]) {
            print_line(String(alarm_hours[current_alarm]) + ":" + 
                      (alarm_minutes[current_alarm] < 10 ? "0" : "") + 
                      String(alarm_minutes[current_alarm]), 10, 25, 2);
        }
        
        print_line("UP: Next  DOWN: Toggle", 10, 45, 1);
        print_line("OK: Set  CANCEL: Exit", 10, 55, 1);
        
        int button_pressed = wait_for_button_press();
        
        if (button_pressed == PB_UP) {
            current_alarm = (current_alarm + 1) % n_alarms;
        }
        else if (button_pressed == PB_DOWN) {
            alarm_active[current_alarm] = !alarm_active[current_alarm];
            display.clearDisplay();
            print_line("Alarm " + String(current_alarm + 1), 10, 10, 2);
            print_line(alarm_active[current_alarm] ? "Activated" : "Disabled", 10, 30, 2);
            delay(1000);
        }
        else if (button_pressed == PB_OK) {
            alarm_active[current_alarm] = true;  // Enable alarm when setting it
            set_alarm(current_alarm);
        }
        else if (button_pressed == PB_CANCEL) {
            exit_to_menu = true;
        }
    }
}

void set_alarm(int alarm_number) {
    int temp_hours = alarm_hours[alarm_number];
    int temp_minutes = alarm_minutes[alarm_number];
    bool exit_to_menu = false;
    
    while (!exit_to_menu) {
        display.clearDisplay();
        print_line("Enter hour: " + String(temp_hours), 10, 20, 2);
        int button_pressed = wait_for_button_press();
        if (button_pressed == PB_UP) temp_hours = (temp_hours + 1) % 24;
        else if (button_pressed == PB_DOWN) temp_hours = (temp_hours == 0) ? 23 : temp_hours - 1;
        else if (button_pressed == PB_OK) { alarm_hours[alarm_number] = temp_hours; break; }
        else if (button_pressed == PB_CANCEL) { exit_to_menu = true; break; }
    }
    
    if (!exit_to_menu) {
        while (true) {
            display.clearDisplay();
            print_line("Enter minutes: " + String(temp_minutes), 10, 20, 2);
            int button_pressed = wait_for_button_press();
            if (button_pressed == PB_UP) temp_minutes = (temp_minutes + 1) % 60;
            else if (button_pressed == PB_DOWN) temp_minutes = (temp_minutes == 0) ? 59 : temp_minutes - 1;
            else if (button_pressed == PB_OK) { alarm_minutes[alarm_number] = temp_minutes; break; }
            else if (button_pressed == PB_CANCEL) break;
        }
        display.clearDisplay();
        print_line("Alarm set!", 10, 20, 2);
        delay(1000);  // Show confirmation message for 1 second
    }
}

void run_mode(int mode) {
    switch (mode) {
        case 0: set_time(); break;
        case 1: set_alarm(0); alarm_active[0] = true; break;
        case 2: set_alarm(1); alarm_active[1] = true; break;
        case 3: delete_alarms(); break;

        case 4: view_alarms(); break;
        case 5: set_utc_offset_menu(); break;
        case 6: display_temperature(); break;
        default: break;
    }
}

void go_to_menu() {
    bool exit_menu = false;
    
    while (!exit_menu) {
        display.clearDisplay();
        print_line(modes[current_mode], 10, 20, 2);
        int button_pressed = wait_for_button_press();
        
        if (button_pressed == PB_UP) {
            current_mode = (current_mode + 1) % max_mode;
        }
        else if (button_pressed == PB_DOWN) {
            current_mode = (current_mode == 0) ? max_mode - 1 : current_mode - 1;
        }
        else if (button_pressed == PB_OK) {
            delay(200);
            run_mode(current_mode);
        }
        else if (button_pressed == PB_CANCEL) {
            exit_menu = true;
        }
    }
    
    // Clear display when exiting menu
    display.clearDisplay();
}

