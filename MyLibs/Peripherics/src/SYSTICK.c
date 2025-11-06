#ifndef SYSTICK_src
#define SYSTICK_src

#include <Core/Registers.h>
#include <Peripherics/inc/Systick.h>

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

 REG_STK_CTRL &= ~(1<<STIE) | ~(1<<STE); // Desabilita a interrup??o e o m§Ú§àdulo.
 REG_STK_CNTL = (unsigned int)0x00; // Zera a contagem.

}






#endif