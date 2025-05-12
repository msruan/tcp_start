#ifndef TCP_H
#define TCP_H

#include "lwip/tcp.h"
#include "lwip/tcp.h"
#include "pico/cyw43_arch.h"

#define SERVER_PORT 80

void setup_tcp(tcp_accept_fn callback);
void process_tcp_events_on_loop();

#endif