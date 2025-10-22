/********************************** Uso livre!  *******************************
* File Name          : TIM2.h
* Author             : Lucas Oliveira Magalh?es
* Version            : V1.0
* Date               : 2025/10/07
* Description        : CH32V003 - Interface simplificada com o Timer de proposito geral TIM2.
*********************************************************************************
* 
* 
* 
*******************************************************************************/

#ifndef TIM2_LIB

#define TIM2_LIB


#define _TIM2_BASE 0x40000000

// ___________ Registradores de configuracao _________//
#define REG_TIM2_CTRL1      *((volatile unsigned int*)(_TIM2_BASE + 0x00)) // Configuracoes gerais 1
#define REG_TIM2_CTRL2      *((volatile unsigned int*)(_TIM2_BASE + 0x04)) // Configuracoes gerais 2

#define REG_TIM2_SMCFGR     *((volatile unsigned int*)(_TIM2_BASE + 0x08))
#define REG_TIM2_DMAINTENR  *((volatile unsigned int*)(_TIM2_BASE + 0x0C)) // Configura o DMA
#define REG_TIM2_PSC        *((volatile unsigned int*)(_TIM2_BASE + 0x28)) // Registrador de prescaler que divide o clock para o perif¨¦rico.

// __________Registradores funcionais ______________//

#define REG_TIM2_INTFR      *((volatile unsigned int*)(_TIM2_BASE + 0x10)) // Exibe as interrupcoes.
#define REG_TIM2_CNT        *((volatile unsigned int*)(_TIM2_BASE + 0x24)) // Registrador de contagem.
#define REG_TIM2_SWEVGR     *((volatile unsigned int*)(_TIM2_BASE + 0x24)) // Registrador de geracao de eventos.
#define REG_TIM2_ATRLR      *((volatile unsigned int*)(_TIM2_BASE + 0x2C)) // Registrador de Auto Reload, define o teto maximo de contagem.

// ______________ SETPOINTS _______________________//
#define MAX_PERIOD_TIM2_S  175 // Maxima temporiza??o permitida para o TIM2 em segundos.
#define MAX_PERIOD_TIM2_mS 999 // Maxima temporiza??o permitida para o TIM2 em milisegundos.
#define MAX_PERIOD_TIM2_uS 999 // Maxima temporiza??o permitida para o TIM2 em microsegundos.



//______________ Bits do CTRL1 __________________//

#define TIM2_APRE_bit (1<<7) // Ativa o AUTO-RELOAD.
#define TIM2_OPM_bit  (1<<3) // Ativa o modo de PULSO UNICO.
#define TIM2_UDIS_bit (1<<1) // Desabilita o "update" do timer2, assim travando os valores dos registradores funcionais
#define TIM2_CEN_bit  (1<<0) // Habilita o contador.

//______________ Bits do CTRL2 _________________//


// _____________ Bits do SMCFGR ________________//

#define TIM2_ECE_bit (1<<14)

// ____________ bits do INTF ____________________//

#define TIM2_UIF_bit (1<<0)

// ____________ bits do SWEVGR __________________//

#define TIM2_UG_bit (1<<0) // Atualiza a geracao do evento "Update", so pode ser setado


/*


Calculo do periodo de estourou "update" do tim 2


Uhz = CKL_INT/ PSC + 1




*/

//________________________________________________//


unsigned int Cilic_TIM2(int Period, time_t Unidade){


    REG_RCC_APB1PCENR  |= 0x01; // Liga o clock do TIM2.

    REG_RCC_APB2PRSTR  |=  (1<<0); // Reseta o modulo TIM2
    REG_RCC_APB2PRSTR  &= ~(1<<0); // Reseta o modulo TIM2

    NVIC_EnableIRQ(TIM2_IRQn); // Liga a interrup??o do TIM2.   


    REG_TIM2_CTRL2 &= ~0x7; // Define o clock do perif¨¦rico para o clock interno.
    REG_TIM2_CTRL2 &= ~TIM2_ECE_bit; // Define para modo interno.

    if(Period >= MAX_PERIOD_TIM2_uS || Period < 1){ return 1;}
    
    switch(Unidade){

        case us: 

        

        break;



        case ms: if(Period >= MAX_PERIOD_TIM2_mS || Period < 1){ return 1;}
       
       
       
       
        break;


        case s: if(Period >= MAX_PERIOD_TIM2_S   || Period < 1){ return 1;}


        
        break;


        default: return 1; 

    }

    REG_TIM2_CTRL1 |= TIM2_CEN_bit; // Liga o timer 2

    return (unsigned int)0x0;
}



int Stop_cliclic_TIM2(){




    return 0;
}



























#endif // Fim da lib.