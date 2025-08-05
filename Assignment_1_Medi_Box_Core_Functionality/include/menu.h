// UPDATES FOR menu.h
#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
void set_time();
void set_alarm(int alarm_number);
int wait_for_button_press();
void run_mode(int mode);
void go_to_menu();
void set_utc_offset_menu();
void view_alarms();
void delete_alarms();

#endif