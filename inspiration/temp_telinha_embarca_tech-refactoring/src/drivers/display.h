#ifndef DISPLAY_H
#define DISPLAY_H

#include "ssd1306.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include "pico/stdlib.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C      // Endereço I2C do display
#define DISPLAY_FREQUENCY 400000 // 400 kHz
#define I2C_SDA 14               // Pino SDA
#define I2C_SCL 15               // Pino SCL

extern ssd1306_t display;
extern uint8_t global_display_x;
extern uint8_t global_display_y;

int init_display();
void show(const char *text, bool render_now);

// Calls ssd1306_clear(&display);
void clear_display(bool reset_screen);

#endif