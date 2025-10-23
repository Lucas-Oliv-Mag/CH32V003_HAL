#ifndef USART_INC
#define USART_INC

#include <Core/Lib_config.h>
#include <Core/Registers.h>
#include <Peripherics/inc/GPIOs.h> 
#include <Utilitys/Utilitys.h>   


// CTRL 1 bits
#define Odd           0x01
#define Even          0x00

#define No_Parity     0xff

#define _8bits_lenght 0
#define _9bits_lenght 1
#define Tx_EN_Bit     3
#define Rx_EN_Bit     2  

// CTRL 2 bits

#define _1Stop_bit 0x00
#define _2Stop_bit 0x02
#define CLK_EN_bit  11
#define CLK_POL_bit 10

extern unsigned int SYSCLK;
extern unsigned int HCLK;
extern unsigned int PCLK; // Clock dos perif¨¦ricos, SYSCKL depois do HPRE, em Hz


/**
 * @brief Calcula o valor do registrador responsavel por gerar o BaudRate do perif?rico USART.
 * 
 * @param pclk Escrever por extenso o HCLK.
 * @param baud Velocidade da comunica??o desejada Bits por segundo.
 * @return unsigned int Baudrate (Deve ser inserido no registrador USART).
 */
unsigned int BaudRate_Calc(unsigned int pclk, unsigned int baud);


/**
 * @brief Inicia o perif?rico UART no modo de transmiss?o assincrona, TX + RX.
 * 
 * @param BaudRate A Velocidade desejada em bits por segundo.
 * @param Parity   
 * @param Stop_bits 
 * @param DataLenght 
 */
void Init_USART1(int BaudRate,int Parity,int Stop_bits, int DataLenght);


void Write_USART1(char Data);


char Receive_USART1();


void Print_USART1(char* String);




#endif //USART_LIB
