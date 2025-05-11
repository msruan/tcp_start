#include "temp.h"

void init_temp_sensor()
{
    adc_init();
    adc_set_temp_sensor_enabled(true);
}

float read_internal_temperature()
{
    adc_select_input(ADC_TEMP_CHANNEL);
    float conversion_factor = ADC_VREF / ADC_RESOLUTION;
    uint16_t raw = adc_read();

    float voltage = raw * conversion_factor;
    float temperature = voltage_to_temperature_c(voltage);

    return temperature;
}

float voltage_to_temperature_c(float voltage)
{
    // acccording to the datasheet, the temperature is calculated as:
    float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;
    return temperature;
}