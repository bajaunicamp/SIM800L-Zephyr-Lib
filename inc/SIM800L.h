#ifndef SIM800L_H
#define SIM800L_H

#include "zephyr/drivers/uart.h"

struct s_input_dev{
    const struct device *dev;
    char *buffer;
    int buffer_size;
};

struct s_server{
    const struct device *dev;
    char *buffer;
    int buffer_size;
};

int init_gps_in();
int init_server();
void gps_in_callback(const struct device *dev, struct uart_event *evt, void *user_data);
void server_callback(const struct device *dev, struct uart_event *evt, void *user_data);

#endif