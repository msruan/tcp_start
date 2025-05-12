#pragma once

#include "pico/stdlib.h"
#include "string.h"

#include "drivers/tcp.h"
#include "drivers/button.h"
#include "drivers/wifi.h"
#include "drivers/pir-sensor.h"
#include "drivers/joystick.h"

#include "config.h"

typedef enum
{
    DIRECTION_NW,     // Noroeste
    DIRECTION_N,      // Norte
    DIRECTION_NE,     // Nordeste
    DIRECTION_W,      // Oeste
    DIRECTION_CENTER, // Centro
    DIRECTION_E,      // Leste
    DIRECTION_SW,     // Sudoeste
    DIRECTION_S,      // Sul
    DIRECTION_SE      // Sudeste
} JoystickDirection;

// Função para retornar a string associada à direção
const char *joystick_direction_to_string(JoystickDirection direction)
{
    switch (direction)
    {
    case DIRECTION_NW:
        return "Noroeste";
    case DIRECTION_N:
        return "Norte";
    case DIRECTION_NE:
        return "Nordeste";
    case DIRECTION_W:
        return "Oeste";
    case DIRECTION_CENTER:
        return "Centro";
    case DIRECTION_E:
        return "Leste";
    case DIRECTION_SW:
        return "Sudoeste";
    case DIRECTION_S:
        return "Sul";
    case DIRECTION_SE:
        return "Sudeste";
    default:
        return "Desconhecido";
    }
}

JoystickDirection check_joystick_direction()
{
    uint8_t vrx = read_bdl_joystick_x();
    uint8_t vry = read_bdl_joystick_y();

    const uint8_t CENTER_TOLERANCE = 2;

    bool on_east = vrx >= JOYSTICK_MAX_VALUE - CENTER_TOLERANCE;
    bool on_west = vrx <= JOYSTICK_MIN_VALUE + CENTER_TOLERANCE;
    bool on_north = vry >= JOYSTICK_MAX_VALUE - CENTER_TOLERANCE;
    bool on_south = vry <= JOYSTICK_MIN_VALUE + CENTER_TOLERANCE;

    if (on_north)
    {
        return DIRECTION_N; // Norte
    }
    else if (on_south)
    {
        return DIRECTION_S; // Sul
    }
    else if (on_west)
    {
        return DIRECTION_W; // Oeste
    }
    else if (on_east)
    {
        return DIRECTION_E; // Leste
    }

    const uint8_t JOYSTICK_CENTER = JOYSTICK_MAX_VALUE / 2;

    bool on_right = vrx >= JOYSTICK_CENTER;
    bool on_left = vrx < JOYSTICK_CENTER;
    bool on_top = vry >= JOYSTICK_CENTER;
    bool on_bottom = vry < JOYSTICK_CENTER;

    if (on_top && on_right)
    {
        return DIRECTION_NE; // Nordeste
    }
    else if (on_top && on_left)
    {
        return DIRECTION_NW; // Noroeste
    }
    else if (on_bottom && on_right)
    {
        return DIRECTION_SE; // Sudeste
    }
    else if (on_bottom && on_left)
    {
        return DIRECTION_SW; // Sudoeste
    }
    else
    {
        return DIRECTION_CENTER; // Centro
    }
}

static err_t tcp_server_recv_monitor(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t error)
{
    if (!p)
    {
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
             "   <p> Joystick X: %d </p>\r\n"
             "   <p> Joystick Y: %d </p>\r\n"
             "   <p> Rosa dos ventos: %s </p>\r\n"
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
             read_bdl_joystick_x(),
             read_bdl_joystick_y(),
             joystick_direction_to_string(check_joystick_direction()),
             get_current_ip());

    tcp_write(tpcb, html, strlen(html), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);

    free(request);
    pbuf_free(p);

    return ERR_OK;
}

static err_t tcp_server_accept_monitor(void *arg, struct tcp_pcb *newpcb, err_t error)
{
    tcp_recv(newpcb, tcp_server_recv_monitor);

    return ERR_OK;
}