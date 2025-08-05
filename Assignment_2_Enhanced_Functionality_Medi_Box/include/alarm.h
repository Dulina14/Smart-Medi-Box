#ifndef ALARM_H
#define ALARM_H

#include <Arduino.h>
#include "display.h"
#include "time_utils.h"

void ring_alarm();
void update_time_with_check_alarm();

extern bool alarm_enabled;
extern bool alarm_active[];

#endif