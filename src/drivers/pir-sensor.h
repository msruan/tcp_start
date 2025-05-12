#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#include "pico/stdlib.h"

int setup_pir_sensor(uint sensor_gpio_port);

bool pir_is_detecting(uint pir_pin);

#endif