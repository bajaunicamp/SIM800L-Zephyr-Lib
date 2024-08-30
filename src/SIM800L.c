#include "SIM800L.h"
#include <stdlib.h>

struct s_server server;
struct s_input input_channel;

int init_input(){

}

int init_server(){
    server.dev = DEVICE_DT_GET(DT_ALIAS(sim800l));
    server.buffer_size = 50;
    server.buffer = malloc(50*sizeof(char));
    int ret = uart_callback_set(server.dev, input_callback, NULL);
    if(ret) return ret;
    return 0;
}

void sensor_callback(const struct device *dev, struct uart_event *evt, void *user_data);


