#include "pico/stdlib.h"
#include "string.h"

#include "drivers/tcp.h"
#include "drivers/button.h"
#include "drivers/wifi.h"
#include "drivers/pir-sensor.h"

#include "config.h"


static err_t tcp_server_recv_btn_monitor(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t error){
    if(!p){
        tcp_close(tpcb);
        tcp_recv(tpcb, NULL);
        return ERR_OK;
    }

    char *request = (char *)malloc(p->len + 1);
    memcpy(request, p->payload, p->len);
    request[p->len] = '\0';

    printf("Request: %s\n", request);

    char html[1024];

    snprintf(html, sizeof(html),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Content-Length: %d\r\n"
        // "Connection: close\r\n"
        "\r\n"
        "<!DOCTYPE html>\r\n"
        "<html>\r\n"
        "<head>\r\n"
        "   <title> Button read </title>\r\n"
        // "   <meta http-equiv=\"refresh\" content=\"1\">\r\n"
        "<body>\r\n"
        "   <h1> Button READ Bitdoglab </h1>\r\n"
        "   <p> Botao A: %s </p>\r\n"
        "   <p> Botao B: %s </p>\r\n"
        "   <p> Sensor PIR: %s </p>\r\n"
        "   <script>\r\n"
        "       setInterval(() => {\r\n"
        "           window.location.reload();\r\n"
        "       }, 1000);\r\n"
        "   </script>\r\n"
        "</body>\r\n"
        "</html>\r\n",
        strlen(html),
        button_is_pressed(BDL_GPIO_BTN_A_PIN) ? "S" : "N",
        button_is_pressed(BDL_GPIO_BTN_B_PIN) ? "S" : "N",
        pir_is_detecting(PIR_SENSOR_GPIO_PIN) ? "S" : "N",
        get_current_ip()
    );

    tcp_write(tpcb, html, strlen(html), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);
    
    free(request);
    pbuf_free(p);

    return ERR_OK;
}

static err_t tcp_server_accept_btn_monitor(void *arg, struct tcp_pcb *newpcb, err_t error){
    tcp_recv(newpcb, tcp_server_recv_btn_monitor);

    return ERR_OK;
}