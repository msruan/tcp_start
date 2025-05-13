
#ifndef CONFIG_H
#define CONFIG_H

#include "drivers/wifi.h"

#define PIR_SENSOR_GPIO_PIN 8

const WifiConnectionConfig wifi_config = {
    .SSID = "thenameofyourwifinetwork",
    .password = "itspassword"
};

#endif
