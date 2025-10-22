
/*
___________________________________________________________________________________________________________________________________

    CRIADO POR: LUCAS O.M  | Data: 03/10/2025   | Brasil - SP

    T?TULO: Lib para utilizar o Systick do CH32V003.

    DESC: Utilize as fun??es para manusear o systick timer, para gerar interrup??es, N?o h¨¢ nescessidade de configurar nada ¨¢ mais, 
    por¨¦m dever¨¢ criar a ISR para o Systick.

    - Normalmente utiliza-se para gerar interrup??es ciclicamentes, no periodo passado em Systick_init().

    - ? possivel utilizar est¨¢ lib para disparar uma unica vez a interrup??o programada, basta usar Systick_init(), e ap¨®s, na sua 
     ISR, utilizar o Systick_stop().


___________________________________________________________________________________________________________________________________

*/

#ifndef SYSTICK_H
#define SYSTICK_H

// Defini??o dos registradores do SYSTICK Timer.
#define REG_STK_CTRL  (*(volatile unsigned int*)0xE000F000)          // Configura??o do Systick.
#define REG_STK_SR    (*(volatile const unsigned int*)0xE000F004) // Somente leitura do status discreto da contagem.
#define REG_STK_CNTL  (*(volatile unsigned int*)0xE000F008)       // Valor atual do registrador de contagem.
#define REG_STK_CMPLR (*(volatile unsigned int*)0xE000F010)      // Valor de setpoint para estouro do systick.


// Bits do STK_CTRL - Registrador de configura??o.

#define SWIE  31    // Habilita a interrup??o via software do bit.
#define STRE  3     // Auto-Reload do timer (Ativa o modo ciclico).
#define STCKL 2     // Fonte do clock do Systimer. (1:1 ou 1:8).
#define STIE  1     // Habilita a interrupca do contador.
#define STE   0     // Bit que habilita o Systick.

// Bits do STK_SR - Registrador de status da contagem.

#define CNTIF 0     // Indica se houve ou n?o o estouro d systick.


typedef enum Time_Unit{ns = 0, us = 1, ms = 1000, s = 1000000} Time_t; 


extern unsigned int SYSCLK, PCLK;

/**
 * @brief Configura o timer systick para gerar interrup??o ciclicamente, pelo periodo passado
 * 
 * @param Period O Periodo
 * @param Unit   A Unidade de medida do periodo (ms, us, s)
 * @return Retorna 0x01 em caso de erro.
 */
unsigned int init_Systick(unsigned int Period, Time_t Unit){


    if(Period == 0 || Period > 999){return 1;}// Caso o periodo for invalido, retorna 1

    REG_STK_CTRL |= (1<<STCKL); // Define o clock do contador para SYSCKL

    REG_STK_CMPLR = 0x1000000; //(SYSCLK/1000000) * (Period * Unit);// Calcula o estouro

    REG_STK_CTRL |= (1<<STIE) | (1<<STE) | (1<<STRE); // Habilita a interrup??o, o ativamento ciclico.
    REG_STK_CNTL = (unsigned int)0x00;               // Limpa a contagem atual, zerando a contagem.


    return 0; // Caso tudo oK.
    
}



/**
 * @brief Interrompe o acionamento ciclico do Systick.
 * 
 */
void Systick_stop(){// Interrompe o acionamento ciclico do Systick.

 REG_STK_CTRL &= ~(1<<STIE) | ~(1<<STE); // Desabilita a interrup??o e o m¨®dulo.
 REG_STK_CNTL = (unsigned int)0x00; // Zera a contagem.

}



#endif // Fim da lib