#include "time_utils.h"

unsigned int seconds = 0;
unsigned int minutes = 0;
unsigned int hours = 0;
unsigned int days = 0;
float current_utc_offset = UTC_OFFSET_DEFAULT;

void update_time() {
    struct tm timeinfo;
    getLocalTime(&timeinfo);

    days = timeinfo.tm_mday;
    hours = timeinfo.tm_hour;
    minutes = timeinfo.tm_min;
    seconds = timeinfo.tm_sec;
}

void connect_wifi() {
    WiFi.begin("Wokwi-GUEST", "", 6);
    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
    }
}

void set_utc_offset(float offset) {
    current_utc_offset = offset;
    configTime(current_utc_offset * 3600, UTC_OFFSET_DST, NTP_SERVER);
    delay(500); // Give some time for the time to update
}