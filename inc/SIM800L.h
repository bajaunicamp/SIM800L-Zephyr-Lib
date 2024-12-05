#ifndef SIM800L_H
#define SIM800L_H

#include "zephyr/drivers/uart.h"

enum OPERADORA{TIM, VIVO, CLARO, OUTRO};

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

/**
 * @brief Estabelece o canal de comunicação UART do STM com o SIM800L e estabelece uma conexão entre o SIM800L e o servidor
 * @param port Porta do servidor
 * @param op Operadora do chip sendo usado
 */
int init_server(unsigned int port, enum OPERADORA op);

/**
 * @brief Envia uma mensagem ao servidor
 * @param message Mensagem a ser enviada ao servidor
 */
void send_server(char *message);

#endif
