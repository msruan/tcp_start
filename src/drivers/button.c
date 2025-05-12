#include "button.h"

bool button_is_pressed(uint pin)
{
    return !gpio_get(pin);
}

void setup_button(uint pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
}

void setup_bdl_buttons(enum ButtonActivationMode mode)
{
    switch (mode)
    {
    case ActivateA:
        setup_button(BDL_GPIO_BTN_A_PIN);
        break;
    case ActivateB:
        setup_button(BDL_GPIO_BTN_B_PIN);
    case ActivateBoth:
        setup_button(BDL_GPIO_BTN_A_PIN);
        setup_button(BDL_GPIO_BTN_B_PIN);
        break;
    }
}
