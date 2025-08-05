// UPDATES FOR time_utils.h
#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <WiFi.h>
#include <time.h>

#define NTP_SERVER "pool.ntp.org"
#define UTC_OFFSET_DEFAULT 0
#define UTC_OFFSET_DST 0

extern unsigned int seconds, minutes, hours, days;
extern float current_utc_offset;

void update_time();
void connect_wifi();
void set_utc_offset(float offset);

#endif