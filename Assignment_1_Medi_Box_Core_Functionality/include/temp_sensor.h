#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <Arduino.h>
#include <DHTesp.h>
#include "display.h"

// Initialize the DHT sensor
void setup_temp_sensor();

// Check temperature and humidity, display warnings if needed
void check_temp();

// Get the current temperature
float get_temperature();

// Get the current humidity
float get_humidity();

#endif