#include "SIM800L.h"
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <string.h>

struct s_server server;
struct s_input_dev gps_in;

int init_server(){
    // Inicializando a comunicação UART
    server.dev = DEVICE_DT_GET(DT_ALIAS(sim800l));
    server.buffer_size = 50;
    server.buffer = malloc(50*sizeof(char));
    server.connected = false;
    int ret = uart_callback_set(server.dev, server_callback, NULL);
    if(ret) return ret;

    char temp[100];

    // TODO: substituir o delay por uma verificação de conexão
    k_msleep(10000);

    // Select TCIP Application Mode
    sprintf(temp, "AT+CIPMODE=0\r\n");
    uart_tx(server.dev, temp, strlen(temp), 100);
    k_msleep(100);

    // Startup single IP connection
	sprintf(temp, "AT+CIPMUX=0\r\n");
    uart_tx(server.dev, temp, strlen(temp), 100);
    k_msleep(100);

	// Attach from GPRS Service
	sprintf(temp, "AT+CGATT=1\r\n");
    uart_tx(server.dev, temp, strlen(temp), 100);
    k_msleep(100);

	// Start task and set APN
	sprintf(temp, "AT+CSTT=\"timbrasil.br\",\"tim\",\"tim\"\r\n");
    uart_tx(server.dev, temp, strlen(temp), 100);
    k_msleep(10000);

	// Bring up wireless connection with GPRS  or CSD
	sprintf(temp, "AT+CIICR\r\n");
    uart_tx(server.dev, temp, strlen(temp), 100);
    k_msleep(100);

	// Get Local IP address
	sprintf(temp, "AT+CIFSR\r\n");
    uart_tx(server.dev, temp, strlen(temp), 100);
    k_msleep(100);

	// Start up TCP connection
	sprintf(temp, "AT+CIPSTART=\"TCP\",\"tcp://0.tcp.sa.ngrok.io\",\"00000\"\r\n");
    uart_tx(server.dev, temp, strlen(temp), 100);
    server.connected = true;
    k_msleep(100);

	// Enviar mensagem pro servidor que é o baja que tá conectando
    send_server("[CONNECTION] Baja");

    return 0;
}

void send_server(char *message){
    char temp[100];

    sprintf(temp, "AT+CIPSEND=%d\r\n", strlen(message));
    uart_tx(server.dev, temp, strlen(temp), 100);
    k_msleep(100);

    sprintf(temp, "%s\r\n", message);
    uart_tx(server.dev, temp, strlen(temp));
    k_msleep(100);
}


