#ifndef USART1_SRC
#define USART1_SRC


#include <Peripherics/inc/USART1.h>



/**
 * @brief Calcula o valor do registrador responsavel por gerar o BaudRate do perif?rico USART.
 * 
 * @param pclk Escrever por extenso o HCLK.
 * @param baud Velocidade da comunica??o desejada Bits por segundo.
 * @return unsigned int Baudrate (Deve ser inserido no registrador USART).
 */
unsigned int BaudRate_Calc(unsigned int pclk, unsigned int baud)
{
    // Calcula USARTDIV em ponto flutuante
    double usartdiv = (double)pclk / (16.0 * (double)baud);

    // Parte inteira (mantissa)
    unsigned int mantissa = (unsigned int)usartdiv;

    // Parte fracion§Ú§Ória (x16, arredondada)
    unsigned int fraction = (unsigned int)((usartdiv - mantissa) * 16.0);

    // Ajuste de overflow da fracao
    if (fraction >= 16) {
        mantissa += 1;
        fraction = 0;
    }

    // Monta BRR (mantissa ocupa bits [15:4], fra??o [3:0])
    return (mantissa << 4) | (fraction & 0xF);
}


/**
 * @brief Inicia o perif?rico UART no modo de transmiss?o assincrona, TX + RX.
 * 
 * @param BaudRate A Velocidade desejada em bits por segundo.
 * @param Parity   
 * @param Stop_bits 
 * @param DataLenght 
 */
void Init_USART1(int BaudRate,int Parity,int Stop_bits, int DataLenght){

    // Liga o clock USART1 | port D | AFIO
    REG_RCC_APB2PCENR |= (1<<14) | (1<<5) | (1<<0);

    // Reset USART1
    REG_RCC_APB2PRSTR |=  (1<<14);
    REG_RCC_APB2PRSTR &= ~(1<<14);
  
    // Reseta o PORT D
    REG_RCC_APB2PRSTR |=  (1<<5);
    REG_RCC_APB2PRSTR &= ~(1<<5);

    // Reseta o o AFIO
    REG_RCC_APB2PRSTR |=  (1<<0);
    REG_RCC_APB2PRSTR &= ~(1<<0);

    Pin_set(PORTD,5,Mult_push_pull,_50MHz);// Configura PD5 (TX) como Alternate Function Push-Pull (50 MHz)

    Pin_set(PORTD,6,Floating_in,_50MHz); // Configura PD6 (RX) como entrada flutuante
    
    REG_USART_BRR  = BaudRate_Calc(PCLK,9600); // Calcula o BaudRate
   
    // Carrega as configuracoes de comunicacao

    REG_USART_CTRL1 = 0;       // limpa CTRL1
    REG_USART_CTRL2 = 0;       // ass?ncrono
    REG_USART_CTRL3 = 0;       // sem fun??es extras
    REG_USART_CTRL1 |= (1<<13) | (1<<3) | (1<<2); // UE + TE + RE
}


void Write_USART1(char Data){
    while(!((REG_USART_STATR >> 7) & 0x01)); // espera TXE
    REG_USART_DATAR = ((unsigned int)(Data & (unsigned int)0x00FFU));
   // REG_USART_CTRL1 |= (1<< Tx_EN_Bit);
}



char Receive_USART1(){
    
    do {
    
         __asm__("nop"); 

    }while ( ((REG_USART_STATR >> 5) & 0x01) == 0 );


    return (char)REG_USART_DATAR;
}



void Print_USART1(char* String){

    unsigned int tempreg = String_counter(String);

    for(unsigned int i = 0; i < tempreg; i++){
    
        Write_USART1(*(String + i));

    }

}




#endif //USART_LIB


