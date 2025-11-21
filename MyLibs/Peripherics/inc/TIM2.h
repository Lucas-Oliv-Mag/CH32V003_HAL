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

#include <Core/Registers.h>
#include <Peripherics/inc/RCC.h>
#include <Peripherics/inc/Systick.h>
#include <Peripherics/inc/PFIC.h>

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


// __________ Bits do DMA __________________//

#define TIM2_UIE_bit (1<<0) // Ativa as interrupcoes do TIM2
/*





*/

//________________________________________________//



extern unsigned int PCLK, SYSCLK; 


unsigned int Cilic_TIM2(unsigned int Period, Time_t Unidade);



void Stop_cliclic_TIM2();




#endif // Fim da lib.