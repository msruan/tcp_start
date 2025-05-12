#include "joystick.h"

const uint8_t BDL_GPIO_JOYSTICK_VRX_PIN = 27;
const uint8_t BDL_GPIO_JOYSTICK_VRY_PIN = 26;

// Initialize BDL joystick using ADC
void setup_bdl_joystick()
{
    adc_init();
    adc_gpio_init(BDL_GPIO_JOYSTICK_VRX_PIN);
    adc_gpio_init(BDL_GPIO_JOYSTICK_VRY_PIN);
}

uint8_t read_bdl_joystick_x()
{
    adc_select_input(1);

    return adc_read() * 100 / 4095;
}

uint8_t read_bdl_joystick_y()
{
    adc_select_input(0);

    return adc_read() * 100 / 4095;
}