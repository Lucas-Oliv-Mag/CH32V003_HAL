
/*
___________________________________________________________________________________________________________________________________

    CRIADO POR: LUCAS O.M  | Data: 21/10/2025   | Brasil - SP

    TiTULO: HAL para GPIOs - CH32V003F4P6

    DESC: Inicialização, configuração, operação das GPIOs, desde configurar um port inteiro, a manipular apenas um pino.

    - OBS: Tem dependencia direta da biblioteca

___________________________________________________________________________________________________________________________________

*/
#ifndef GPIOs_INC
#define GPIOs_INC 

#include <Core/Registers.h>

// ___________ Definição dos estados lógicos _________//
#define OUTPUT 0x00U
#define INPUT  0x01U

#define HIGH 0x01U
#define LOW 0x00U

// ___________ Tipos de dados para configuração _________//

typedef enum PORT{ // Contem os endereços dos registradores de CGRL de cada PORT

PORTA=  REG_GPIO_PORTA,
PORTC=  REG_GPIO_PORTC,
PORTD=  REG_GPIO_PORTD
} GPIO_t;

typedef enum Pin_Speed{
   
_10MHz = 0x1U,
_30MHZ = 0x2U,
_50MHz = 0x3U

} Speed_t;

typedef enum Pin_Type{

// OUTPUT MODEs
Push_Pull_out    = 0x0U, // Saida PUSH/PULL, Niveis lógicos ALTO e BAIXO somente.
Open_Drain_out   = 0x1U, // Saida com dreno aberto, apenas puxa para o nivel lógico BAIXO.

Mult_push_pull   = 0x2U, // Modo de saída PUSH/PULL multiplexada para outros periféricos.
Mult_Open_Drain  = 0x3U, // Modo de saída com dreno aberto multiplexada para outros perifericos.

// INPUT MODEs
Pull_up_in       = 0x2U, // Modo de entrada com resistor de pullup,   nescessario configurar.
Drop_Down_in     = 0x2U, // Modo de entrada com resistor de pulldown, nescessario configurar.
Floating_in      = 0x1U, // Modo de entrada flutuante, precisa de polarização externa.
Analog_in        = 0x0U  // Modo de entrada analógica para os conversores ADC, ou OPAMPs


} Pin_t;



/**
 * @brief Configura um pino terminal I/O, com os parametros especificados (Não utilizar cast).
 * 
 * @param Port Qual GPIO esta se referenciando, Ex: PORTC.
 * @param Pin  Qual pino esta se referenciando, Ex: 0 ~ 7.
 * @param Type Qual a configuracao deste pino, Ex: Push_Pull_out.
 * @param Speed Velocidade do pino, Ex: _10MHz.
 * @return Retorna 1 em caso de erro.
 */
unsigned int Pin_set (GPIO_t PORT, unsigned int Pin, unsigned int Type, Speed_t Speed); // Define a configuração de um pino


/**
 * @brief Devolve o valor logico do pino especificado.
 * 
 * @param Port GPIO do pino em questao, ex: PORTC.
 * @param pin  Pino ao qual deve ser lido, ex: 0 ~ 7.
 * @return unsigned int (HIGH ou LOW).
 */
unsigned int Read_Pin(GPIO_t Port, unsigned int pin);


/**
 * @brief Esta funcao configura os pinos do port com o tipo especificado em Type
 * 
 * @param Port GPIO que deseja configurar
 * @param Pins Pinos selecionados em formato binario, Ex: Pino 1 e 5 = 0x22 (0b00100010)
 * @param Type Configuracao de que tipo serao confingurados os pinos.
 * @return Retorna TRUE em caso de erro, e FALSE quando bem sucedido.
 */
unsigned int GPIO_set(GPIO_t Port, unsigned char Pins, Pin_t Type);

/**
 * @brief Alterará o estado do pino terminal informado.
 * 
 * @param Port GPIO do pino, Ex: PORTC.
 * @param pin  O numero do pino, Ex: 1~7.
 * @param VALUE O estado lógico que o pino deve estar, Ex: HIGH
 */
void Write_Pin(GPIO_t Port, unsigned char pin, int VALUE);


/**
 * @brief No GPIO informado, escrevera o valor de Data.
 * 
 * @param Port Informa a GPIO a ser utilizada, ex: PORTC
 * @param Data Qual valor sera impresso no GPIO escolhido.
 */
void Write_Port(GPIO_t Port, unsigned char Data);




#endif