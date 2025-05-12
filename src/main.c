#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/cyw43_arch.h"

#include "drivers/tcp.h"
#include "drivers/wifi.h"
#include "drivers/button.h"
#include "drivers/display.h"
#include "drivers/pir-sensor.h"

#include "config.h"
#include "button_monitor.h"


void setup(){
    stdio_init_all();

    init_display();

    show("SETUP: Iniciando Wifi", true);
    setup_wifi_on_sta_mode(wifi_config);
    show(get_current_ip(), true);

    setup_tcp(tcp_server_accept_btn_monitor);
    show("SETUP: TCP ok", true);

    setup_bdl_buttons(ActivateBoth);

    setup_pir_sensor(PIR_SENSOR_GPIO_PIN);
}

int main()
{
    setup();
    
    while (true) {
        process_tcp_events_on_loop();
    }
}
