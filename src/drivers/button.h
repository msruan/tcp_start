#ifndef BUTTON_H
#define BUTTON_H

#include "pico/stdlib.h"

#define BDL_GPIO_BTN_A_PIN 5
#define BDL_GPIO_BTN_B_PIN 6

enum ButtonActivationMode
{
    ActivateA,
    ActivateB,
    ActivateBoth
};

bool button_is_pressed(uint pin);

// Setup a generic button
void setup_button(uint pin);

// Setup BitDogLab buttons
void setup_bdl_buttons(enum ButtonActivationMode mode);

#endif