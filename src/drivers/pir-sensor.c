#include "pir-sensor.h"

int setup_pir_sensor(uint pir_pin)
{
    gpio_init(pir_pin);
    gpio_set_dir(pir_pin, GPIO_IN);

    gpio_set_pulls(pir_pin, false, true); // Ativa pull-down para evitar ruídos
    return PICO_OK;
}

bool pir_is_detecting(uint pir_pin)
{
    return gpio_get(pir_pin);
}