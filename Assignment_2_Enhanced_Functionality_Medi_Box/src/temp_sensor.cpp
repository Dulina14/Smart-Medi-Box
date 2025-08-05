#include "temp_sensor.h"
#include "pin.h"

DHTesp dhtSensor;

void setup_temp_sensor() {
    dhtSensor.setup(DHT, DHTesp::DHT22);
}

void check_temp() {
    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    bool all_good = true;

    if (data.temperature > 32) {
        all_good = false;
        digitalWrite(LED_1, HIGH);  // Turn on LED if temperature is high
        display.clearDisplay();
        print_line("High Temperature!", 10, 20, 2);
        delay(2000);
    } 
    else if (data.temperature < 24) {
        all_good = false;
        digitalWrite(LED_1, HIGH);  // Turn on LED if temperature is low
        display.clearDisplay();
        print_line("Low Temperature!", 10, 20, 2);
        delay(2000);
    } 
    else if (data.humidity < 65) {
        digitalWrite(LED_1, HIGH);
        all_good = false;
        display.clearDisplay();
        print_line("Low Humidity!", 10, 20, 2);
        delay(2000);
    }
    else if (data.humidity > 80) {
        digitalWrite(LED_1, HIGH);
        all_good = false;
        display.clearDisplay();
        print_line("High Humidity!", 10, 20, 2);
        delay(2000);        
    }

    if (all_good) {
        digitalWrite(LED_1, LOW);  // Turn off LED if all conditions are good
    }
}

float get_temperature() {
    return dhtSensor.getTemperature();
}

float get_humidity() {
    return dhtSensor.getHumidity();
}