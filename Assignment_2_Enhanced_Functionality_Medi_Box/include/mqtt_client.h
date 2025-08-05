#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>
#include <WiFi.h>
#include "temp_sensor.h"

void setup_mqtt();


void connect_mqtt();


void check_mqtt_connection();


void mqtt_callback(char* topic, byte* payload, unsigned int length);


void publish_sensor_data();


void publish_servo_parameters();


void subscribe_to_topics();

#endif