#include "SIM800L.h"
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <string.h>

struct s_server server;
struct s_input_dev gps_in;

int init_gps_in(){

}

int init_server(){
    server.dev = DEVICE_DT_GET(DT_ALIAS(sim800l));
    server.buffer_size = 50;
    server.buffer = malloc(50*sizeof(char));
    int ret = uart_callback_set(server.dev, server_callback, NULL);
    if(ret) return ret;

    char message[100];

    // TODO: substituir o delay por uma verificação de conexão
    k_msleep(10000);

    // Select TCIP Application Mode
    sprintf(message, "AT+CIPMODE=0\r\n");
    uart_tx(server.dev, message, strlen(message), 100);
    k_msleep(100);

    // Startup single IP connection
	sprintf(message, "AT+CIPMUX=0\r\n");
    uart_tx(server.dev, message, strlen(message), 100);
    k_msleep(100);

	// Attach from GPRS Service
	sprintf(message, "AT+CGATT=1\r\n");
    uart_tx(server.dev, message, strlen(message), 100);
    k_msleep(100);

	// Start task and set APN
	sprintf(message, "AT+CSTT=\"timbrasil.br\",\"tim\",\"tim\"\r\n");
    uart_tx(server.dev, message, strlen(message), 100);
    k_msleep(10000);

	// Bring up wireless connection with GPRS  or CSD
	sprintf(message, "AT+CIICR\r\n");
    uart_tx(server.dev, message, strlen(message), 100);
    k_msleep(100);

	// Get Local IP address
	sprintf(message, "AT+CIFSR\r\n");
    uart_tx(server.dev, message, strlen(message), 100);
    k_msleep(100);


	// Start up TCP connection
	sprintf(message, "AT+CIPSTART=\"TCP\",\"tcp://0.tcp.sa.ngrok.io\",\"00000\"\r\n");
    uart_tx(server.dev, message, strlen(message), 100);
    k_msleep(100);

	// TODO: Enviar mensagem pro servidor que é o baja que tá conectando
	sendServidor("[CONNECTION] Baja");
	painelStep(5);

    return 0;
}




