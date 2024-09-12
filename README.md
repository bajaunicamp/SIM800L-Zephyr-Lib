# Biblioteca para uso do SIM800L

Essa biblioteca fornece o código necessário para controlar um GPRS SIM800L a partir de um STM Blue Pill (STM32F103C6T6 ou STM32F103C8T6). 

## Como conectar o STM
- Conecte o pino B10 (TX do STM) ao RX do SIM800L
- Conecte o pino B11 (RX do STM) ao TX do SIM800L
- Caso queira ler os logs do STM, conecte o RX de um leitor UART ao pino A9
- Energize ambas as placas (importante!!)

## Como usar a biblioteca
1. Antes de se comunicar com o servidor, é necessário executar a função **init_server(porta, operadora)**. Note que essa função presume que o servidor está sendo hosteado pela Ngrok. Caso não seja esse o caso, basta alterar a string do endereço do servidor no arquivo SIM800L.c. Outro detalhe importante é que essa função leva um tempo considerável para ser executada, pois ela requer delays para que as conexões se estabeleçam.

2. Em seguida, para enviar uma string qualquer ao servidor basta utilizar a função **send_server(mensagem)**. Note que essa função também apresenta um pequeno delay

## Sobre os logs do STM
Logs que servem para mostrar o que está acontecendo no código sendo executado pelo STM serão exibidos na forma:
    <center> "[TEMPO DE EXECUÇÃO] < tipo da mensagem > : MENSAGEM" </center>



Logs que mostram o que o SIM800L está enviando para o STM serão exibidos na forma:
    <center> "Mensagem recebida: [MENSAGEM]" </center>


## Possíveis problemas / problemas conhecidos
- Os delays presentes nas funções podem tornar o processo lento. Para atenuar esse problema, seria ideal substituir os delays com tempo fixo no código por uma lógica que espere receber uma confirmação do SIM800L para prosseguir.
- As funções não verificam se o estabelecimento da conexão ou o envio de mensagens foi bem sucedido. Para saber se está tudo rodando corretamente é necessário estar constantemente observando o que o servidor está recebendo.
- Por algum motivo, meu chip (Lucas) da Vivo não está conseguindo providenciar conexão a internet ao SIM800L. Talvez haja um problema com chips da Vivo.
- Este código foi testado com um chip da TIM
