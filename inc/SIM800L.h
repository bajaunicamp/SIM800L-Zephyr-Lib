#ifndef SIM800L_H
#define SIM800L_H

#include "zephyr/drivers/uart.h"

/**
 * @struct s_input_dev
 * @brief Representa a conexão UART com o GPS
 */
struct s_input_dev{
    /** Referência ao device da device tree que representa o canal UART sendo usado */
    const struct device *dev;
    /** Buffer no qual serão registradas mensagens recebidas através de callback*/
    char *buffer;
    /** Número de caracteres do buffer que armazena as mensagens recebidas por callback*/
    int buffer_size;
};

/**
 * @struct s_server
 * @brief Representa a conexão UART com o SIM800L
 */
struct s_server{
    /** Referência ao device da device tree que representa o canal UART sendo usado*/
    const struct device *dev;
    /** Buffer no qual serão registradas mensagens recebidas através de callback*/
    char *buffer;
    /** Número de caracteres do buffer que armazena as mensagens recebidas por callback*/
    int buffer_size;
    /** Booleano que registra se há conexão com o servidor*/
    bool connected;
};
// TODO: Criar as funções que lidam com os dados vindo do GPS
int init_gps_in();
void gps_in_callback(const struct device *dev, struct uart_event *evt, void *user_data);

/**
 * @brief Estabelece o canal de comunicação UART do STM com o SIM800L e estabelece uma conexão entre o SIM800L e o servidor
 */
int init_server();

// TODO: Criar callback do servidor para poder ler as respostas
void server_callback(const struct device *dev, struct uart_event *evt, void *user_data);

/**
 * @brief Envia uma mensagem ao servidor
 * @param message Mensagem a ser enviada ao servidor
 */
void send_server(char *message);

#endif