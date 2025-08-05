#include "mqtt_client.h"
#include "ldr_sensor.h"
#include "servo_control.h"
#include "temp_sensor.h"

const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* client_id = "medibox_client";
const char* base_topic = "medibox";

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

void setup_mqtt() {
    mqtt_client.setServer(mqtt_server, mqtt_port);
    mqtt_client.setCallback(mqtt_callback);
    connect_mqtt();
}

void connect_mqtt() {
    while (!mqtt_client.connected()) {
        Serial.println("Connecting to MQTT broker...");
        if (mqtt_client.connect(client_id)) {
            Serial.println("Connected to MQTT broker");
            subscribe_to_topics();
        } else {
            Serial.print("Failed to connect to MQTT broker, rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" trying again in 5 seconds");
            delay(5000);
        }
    }
}

void check_mqtt_connection() {
    if (!mqtt_client.connected()) {
        connect_mqtt();
    }
    mqtt_client.loop();
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message received[");
    Serial.print(topic);
    Serial.print("]: ");
    char message[length + 1];
    for (int i = 0; i < length; i++) {
        message[i] = (char)payload[i];
        Serial.print((char)payload[i]);
    }
    message[length] = '\0';
    Serial.println();

    if (strcmp(topic, "medibox/sampling_interval") == 0) {
        unsigned long interval = strtoul(message, NULL, 10);
        if (interval > 0) {
            set_ldr_sampling_interval(interval * 1000);
        }
    }
    else if (strcmp(topic, "medibox/sending_interval") == 0) {
        unsigned long interval = strtoul(message, NULL, 10);
        if (interval > 0) {
            set_ldr_sending_interval(interval * 1000);
        }
    }
    else if (strcmp(topic, "medibox/min_angle") == 0) {
        int angle = atoi(message);
        if (angle >= 0 && angle <= 120) {
            set_min_angle(angle);
        }
    }
    else if (strcmp(topic, "medibox/controlling_factor") == 0) {
        float factor = atof(message);
        if (factor >= 0 && factor <= 1) {
            set_controlling_factor(factor);
        }
    }
    else if (strcmp(topic, "medibox/ideal_temperature") == 0) {
        float temp = atof(message);
        if (temp >= 10 && temp <= 40) {
            set_ideal_temperature(temp);
        }
    }

    delay(500);
    publish_servo_parameters();
}

void publish_sensor_data() {
    float temp = get_temperature();
    Serial.println(temp);
    float humidity = get_humidity();
    float light_avg = calculate_and_send_ldr_avg();
    if (mqtt_client.connected() && light_avg > 0) {
        char temp_str[10];
        char humidity_str[10];
        char light_str[10];
        dtostrf(temp, 1, 2, temp_str);
        dtostrf(humidity, 1, 2, humidity_str);
        dtostrf(light_avg, 1, 2, light_str);
        mqtt_client.publish("medibox/temperature", temp_str);
        mqtt_client.publish("medibox/humidity", humidity_str);
        mqtt_client.publish("medibox/light_intensity", light_str);
        char angle_str[10];
        itoa(get_servo_angle(), angle_str, 10);
        mqtt_client.publish("medibox/current_angle", angle_str);
    }
}

void publish_servo_parameters() {
    if (mqtt_client.connected()) {
        char min_angle_str[10];
        char controlling_factor_str[10];
        char ideal_temperature_str[10];
        char sampling_interval_str[10];
        char sending_interval_str[10];
        char angle_str[10];
        
        snprintf(min_angle_str, sizeof(min_angle_str), "%d", get_min_angle());
        dtostrf(get_controlling_factor(), 3, 2, controlling_factor_str);
        dtostrf(get_ideal_temperature(), 3, 1, ideal_temperature_str);
        
        // Corrected: Use intervals directly in seconds, no extra division
        snprintf(sampling_interval_str, sizeof(sampling_interval_str), "%d", (int)get_ldr_sampling_interval());
        snprintf(sending_interval_str, sizeof(sending_interval_str), "%d", (int)get_ldr_sending_interval());
        
        mqtt_client.publish("medibox/min_angle", min_angle_str, true);
        mqtt_client.publish("medibox/controlling_factor", controlling_factor_str, true);
        mqtt_client.publish("medibox/ideal_temperature", ideal_temperature_str, true);
        mqtt_client.publish("medibox/sampling_interval", sampling_interval_str, true);
        mqtt_client.publish("medibox/sending_interval", sending_interval_str, true);
        
        snprintf(angle_str, sizeof(angle_str), "%d", get_servo_angle());
        mqtt_client.publish("medibox/current_angle", angle_str);
        Serial.println(angle_str);
    }
}

void subscribe_to_topics() {
    mqtt_client.subscribe("medibox/sampling_interval");
    mqtt_client.subscribe("medibox/sending_interval");
    mqtt_client.subscribe("medibox/min_angle");
    mqtt_client.subscribe("medibox/controlling_factor");
    mqtt_client.subscribe("medibox/ideal_temperature");
}