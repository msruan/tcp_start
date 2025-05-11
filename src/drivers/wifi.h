#ifndef WIFI_H
#define WIFI_H

#include "pico/cyw43_arch.h"
#include "lwip/netif.h"


#define WIFI_SSID_MAX_SIZE 32
#define WIFI_PASSWORD_MAX_SIZE 64

#define WIFI_AUTHORIZATION_TYPE  CYW43_AUTH_WPA2_AES_PSK
#define WIFI_CONNECTION_TIMEOUT 20000

typedef struct {
    char SSID[WIFI_SSID_MAX_SIZE];
    char password[WIFI_PASSWORD_MAX_SIZE];
} WifiConnectionConfig;

void setup_wifi_on_sta_mode(WifiConnectionConfig config);
void shutdown_wifi();

// Returns NULL if not current connected.
char* get_current_ip();

#endif