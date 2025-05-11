#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/cyw43_arch.h"

#include "drivers/wifi.h"
#include "drivers/display.h"


const WifiConnectionConfig wifi_config = {
    .SSID = "DEUS E FIEL",
    .password = "89banana"
};


void setup(){
    stdio_init_all();
    init_display();
    show("HELLO!", true);
    setup_wifi_on_sta_mode(wifi_config);
}

int main()
{
    setup();
    
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
