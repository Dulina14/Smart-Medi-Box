#ifndef LDR_SENSOR_H
#define LDR_SENSOR_H
#include <Arduino.h>


#define LDR_PIN 35


void setup_ldr_sensor();


float get_light_intensity();


void sample_ldr_reading();


float calculate_and_send_ldr_avg();


void set_ldr_sampling_interval(unsigned long interval);


void set_ldr_sending_interval(unsigned long interval);


unsigned long get_ldr_sampling_interval();


unsigned long get_ldr_sending_interval();

#endif