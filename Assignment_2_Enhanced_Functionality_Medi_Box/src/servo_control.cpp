#include "servo_control.h"
#include "ldr_sensor.h"
#include <cmath>
 

Servo servo;
int current_angle = 0;

// Default parameter values
int default_min_angle = 30;             // Default minimum angle
float default_controlling_factor = 0.75; // Default controlling factor
float default_ideal_temperature = 30.0;  // Default ideal temperature

// Declare global variables used across functions
int min_angle;
float controlling_factor;
float ideal_temperature;

void setup_servo() {
    servo.attach(SERVO_PIN);
    servo.write(default_min_angle);
    current_angle = default_min_angle;
    
    Serial.print("Servo initialized at angle: ");
    Serial.println(default_min_angle);

    // Initialize parameters with default values
    set_min_angle(default_min_angle);
    set_controlling_factor(default_controlling_factor);
    set_ideal_temperature(default_ideal_temperature);
}

void update_servo_position(float light_intensity, float temperature) {
    // Get sampling and sending intervals in seconds
    unsigned long ts = get_ldr_sampling_interval();  
    unsigned long tu = get_ldr_sending_interval();
    
    // Prevent division by zero
    if (tu == 0) tu = 1;
    
    // Calculate the logarithm part (ln(ts/tu))
    float log_ratio = log((float)ts / (float)tu);
    
    // Calculate the temperature ratio (T/Tmed)
    float temp_ratio = temperature / ideal_temperature;
    
    // Calculate the angle using the provided equation
    float angle = min_angle + (180 - min_angle) * light_intensity * controlling_factor * log_ratio * temp_ratio;
    
    // Ensure angle is within valid range
    angle = constrain(angle, 0, 180);
    
    // Round to nearest integer and update servo
    int new_angle = round(angle);
    
    // Only move servo if angle has changed
    if (new_angle != current_angle) {
        Serial.print("Updating servo angle to: ");
        Serial.print(new_angle);
        Serial.print(" (light: ");
        Serial.print(light_intensity, 2);
        Serial.print(", temp: ");
        Serial.print(temperature, 1);
        Serial.print("°C, log_ratio: ");
        Serial.print(log_ratio, 3);
        Serial.print(", temp_ratio: ");
        Serial.print(temp_ratio, 3);
        Serial.println(")");
        
        servo.write(new_angle);
        current_angle = new_angle;
    }
}

void set_min_angle(int angle) {
    min_angle = constrain(angle, 0, 120);
}

void set_controlling_factor(float factor) {
    controlling_factor = constrain(factor, 0, 1);
}

void set_ideal_temperature(float temp) {
    ideal_temperature = constrain(temp, 10, 40);
}

int get_servo_angle() {
    return current_angle;
}

int get_min_angle() {
    return min_angle;
}

float get_controlling_factor() {
    return controlling_factor;
}

float get_ideal_temperature() {
    return ideal_temperature;
}