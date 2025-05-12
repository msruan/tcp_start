#include "tcp.h"

struct tcp_pcb *server = NULL;

void setup_tcp(tcp_accept_fn callback)
{

    server = tcp_new();

    hard_assert(server != NULL);

    hard_assert(tcp_bind(
                    server,
                    IP_ADDR_ANY,
                    SERVER_PORT) == ERR_OK);

    server = tcp_listen(server);

    tcp_accept(server, callback);
}

void process_tcp_events_on_loop()
{
    cyw43_arch_poll();
}