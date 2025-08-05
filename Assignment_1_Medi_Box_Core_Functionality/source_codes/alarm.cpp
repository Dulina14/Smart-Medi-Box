#include "alarm.h"
#include "pin.h"

// Define the variables
int notes[] = { 262, 294, 330, 349, 392, 440, 494, 523 }; // C4 to C5

int current_mode = 0;
int max_mode = 7;  
String modes[] = {"Set_time", "Alarm 1", "Alarm 2", "Delete Alarms", 
                   "View Alarms", "UTC Offset", "Show Temp"};

bool alarm_enabled = true;
int n_alarms = 2;
unsigned int alarm_hours[] = {0, 1};
unsigned int alarm_minutes[] = {0, 10};
bool alarm_triggered[] = {false, false};
bool alarm_active[] = {true, true};  // Track if each alarm is enabled

void ring_alarm() {
    display.clearDisplay();
    print_line("Medicine Time!", 10, 20, 2);
    
    bool break_happened = false;

    while (!break_happened && digitalRead(PB_CANCEL) == HIGH) {
        for (int i = 0; i < 8; i++) {
            if (digitalRead(PB_CANCEL) == LOW) {
                delay(200);
                break_happened = true;
                break;
            }
            tone(BUZZER, notes[i]);
            digitalWrite(LED_1, HIGH);
            delay(500);
            noTone(BUZZER);
            delay(2);
        }
    }
    digitalWrite(LED_1, LOW);
    display.clearDisplay();
}

void update_time_with_check_alarm() {
    update_time();
    print_time_now();

    if (alarm_enabled) {
        for (int i = 0; i < n_alarms; i++) {
            if (alarm_active[i] && !alarm_triggered[i] && 
                alarm_hours[i] == hours && alarm_minutes[i] == minutes) {
                ring_alarm();
                alarm_triggered[i] = true;
            }
        }
    }
    
    // Reset alarm triggers for the next day
    if (hours == 0 && minutes == 0 && seconds < 10) {
        for (int i = 0; i < n_alarms; i++) {
            alarm_triggered[i] = false;
        }
    }
}
