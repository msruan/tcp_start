#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "hardware/adc.h"

#define JOYSTICK_MAX_VALUE 99
#define JOYSTICK_MIN_VALUE 0

void setup_bdl_joystick();

// Return joystick X value clamped between 0 and 99 
uint8_t read_bdl_joystick_x();

// Return joystick X value clamped between 0 and 99 
uint8_t read_bdl_joystick_y();

#endif