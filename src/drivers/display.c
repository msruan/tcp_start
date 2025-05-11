#include "display.h"

ssd1306_t display;
uint8_t global_display_x = 0;
uint8_t global_display_y = 0;

const uint8_t line_spacing = 3;

void init_i2c()
{
    i2c_init(i2c1, DISPLAY_FREQUENCY);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

int init_display()
{
    init_i2c();
    // Inicializa o display
    if (!ssd1306_init(&display, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_ADDRESS, i2c1))
    {
        printf("Falha ao inicializar o display SSD1306\n");
        return PICO_ERROR_GENERIC; // Sai do programa
    }
    clear_display(false);
    return PICO_OK;
}

void clear_display(bool reset_screen)
{
    ssd1306_clear(&display);
    show("==================", false);
    if (reset_screen)
    {
        global_display_x = 0;
        global_display_y = 0;
    }
}

void show(const char *text, bool render_now)
{
    ssd1306_draw_string(&display, 0, global_display_y, 1, text);
    global_display_y += line_spacing * 5;
    if (render_now)
    {
        ssd1306_show(&display);
    }
}