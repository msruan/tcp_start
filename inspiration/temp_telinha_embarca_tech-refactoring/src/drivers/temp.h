#ifndef TEMP_H
#define TEMP_H

#include "hardware/adc.h"
#include "pico/stdlib.h"

#define ADC_TEMP_CHANNEL 4
#define ADC_VREF 3.3f
#define ADC_RESOLUTION 4096.0f // 12-bit resolution

void init_temp_sensor();

float read_internal_temperature();

float voltage_to_temperature_c(float voltage);

#endif