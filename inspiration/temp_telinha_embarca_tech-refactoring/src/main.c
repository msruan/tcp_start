#include <stdio.h>
#include "pico/stdlib.h"

#include "drivers/display.h"
#include "drivers/temp.h"

#include "ws2812b_animation.h"

void init_led_matrix()
{
    ws2812b_init(pio0, 7, 25);
    ws2812b_set_global_dimming(7);
    ws2812b_fill_all(GRB_BLACK);
}

void draw_square()
{
    ws2812b_fill(6, 8, GRB_GREEN);
    ws2812b_fill(11, 13, GRB_GREEN);
    ws2812b_fill(16, 18, GRB_GREEN);
}

void update_led_matrix()
{
    ws2812b_render();
}

void setup()
{
    stdio_init_all();
    init_temp_sensor();
    init_display();
    init_led_matrix();
}

int main()
{
    setup();
    draw_square();
    update_led_matrix();

    while (true)
    {
        clear_display(true);
        char msg[20];
        float temperature = read_internal_temperature();
        snprintf(msg, sizeof(msg), "Temp: %.2f C", temperature);

        show(msg, false);
        show("Refatorando...", true);
        sleep_ms(500);
    }
}
