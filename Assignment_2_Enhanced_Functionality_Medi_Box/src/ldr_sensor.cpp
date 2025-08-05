#include "ldr_sensor.h"
#include <PubSubClient.h>
#include <WiFi.h>
#include "pin.h"
#include "mqtt_client.h"

unsigned long last_sample_time = 0;
unsigned long last_send_time = 0;
unsigned long sampling_interval = 5000;  // Default 5 seconds
unsigned long sending_interval = 120000; // Default 2 minutes (120 seconds)

// Array to store LDR samples
const int MAX_SAMPLES = 100;  
float ldr_samples[MAX_SAMPLES];
int sample_count = 0;
int sample_index = 0;

float current_average = 0.75f;  // Initial default average

extern PubSubClient mqtt_client;

void setup_ldr_sensor() {
    pinMode(LDR_PIN, INPUT);
}

float get_light_intensity() {
    int raw_value = analogRead(LDR_PIN);
    
    float normalized_value = map(raw_value, 0, 4095, 0, 100) / 100.0;
    
    normalized_value = constrain(normalized_value, 0.0, 1.0);
    
    return normalized_value;
}

void sample_ldr_reading() {
    unsigned long current_time = millis();
 
    if (current_time - last_sample_time >= sampling_interval) {
        float intensity = get_light_intensity();        
        ldr_samples[sample_index] = intensity;
        sample_index = (sample_index + 1) % MAX_SAMPLES;
        if (sample_count < MAX_SAMPLES) {
            sample_count++;
        }
        
        // Update last sample time
        last_sample_time = current_time;
    }
}

float calculate_and_send_ldr_avg() {
    unsigned long now = millis();

    if ((now - last_send_time >= sending_interval) && (sample_count > 0)) {
        float sum = 0.0f;
        for (int i = 0; i < sample_count; i++) {
            sum += ldr_samples[i];
        }

        float average = sum / sample_count;
        
        Serial.print("LDR average (");
        Serial.print(sample_count);
        Serial.print(" samples): ");
        Serial.println(average, 3);

        last_send_time = now;
        
        current_average = average;
        
        // Reset samples for next period
        sample_count = 0;
        sample_index = 0;
    }
    return current_average;
}

unsigned long get_ldr_sampling_interval() {
    return sampling_interval / 1000; // Return in seconds
}

unsigned long get_ldr_sending_interval() {
    return sending_interval / 1000; // Return in seconds
}

void set_ldr_sampling_interval(unsigned long interval) {
    sampling_interval = interval;
}

void set_ldr_sending_interval(unsigned long interval) {
    sending_interval = interval;
}