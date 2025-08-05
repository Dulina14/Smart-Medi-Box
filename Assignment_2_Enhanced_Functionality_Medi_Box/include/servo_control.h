#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h>
#include <ESP32Servo.h>


#define SERVO_PIN 14


void setup_servo();


void update_servo_position(float light_intensity, float temperature);

void set_min_angle(int angle);

void set_controlling_factor(float factor);


void set_ideal_temperature(float temp);

int get_servo_angle();

int get_min_angle();

float get_controlling_factor();

float get_ideal_temperature();



#endif