#include "wifi.h"

#include "display.h"

#define LED_ON 1
#define LED_OFF 0

int init_wifi_arch();
int connect_wifi(WifiConnectionConfig config);

void setup_wifi_on_sta_mode(const WifiConnectionConfig config)
{
    // show("SETUP: Iniciando Wifi", true);
    hard_assert(init_wifi_arch() == PICO_OK);

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, LED_ON);
    
    hard_assert(connect_wifi(config) == PICO_OK);
    show("OK", true);


    printf("SETUP: Conexão WiFi bem sucedida! ");
    printf("IP atual é %s", get_current_ip());
    show(get_current_ip(), true);
}

int init_wifi_arch()
{
    // cyw43_arch_deinit(); // Desativa o Wi-Fi

    if (cyw43_arch_init() != PICO_OK) // EM produção, talvez seja melhor usar com with_country
    {
        printf("SETUP: Falha ao inicializar Wi-Fi\n");
        sleep_ms(100);
        return PICO_ERROR_GENERIC;
    }

    printf("SETUP: Arquitetura WiFi inicializada!");

    return PICO_OK;
}

int connect_wifi(const WifiConnectionConfig config)
{
    printf("SETUP: Conectando à rede WiFi %s usando a senha %s!", config.SSID, config.password);
    return cyw43_arch_wifi_connect_timeout_ms(
        config.SSID,
        config.password,
        WIFI_AUTHORIZATION_TYPE,
        WIFI_CONNECTION_TIMEOUT);
}

void shutdown_wifi()
{
    cyw43_arch_deinit();
    printf("TEARDOWN: WiFi desligado!");
}

char* get_current_ip(){
    if(netif_default){
        return ipaddr_ntoa(&netif_default->ip_addr);
    }
    return NULL;
}