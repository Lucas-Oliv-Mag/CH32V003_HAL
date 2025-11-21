#ifndef TIM2_src
#define TIM2_src

#include <Peripherics/inc/TIM2.h>

extern unsigned int PCLK, SYSCLK; 


unsigned int Cilic_TIM2(unsigned int Period, Time_t Unidade){

    unsigned int PSC;

    if(Period > 1000){return 1;}
    
    switch(Unidade){

        case us:   PSC = 2000000; break; // 500nS ou 2MHz de frequencia de tick 


        case ms:   PSC = 2000; break;


        default: return 1; 

    }

    Peripheral_clock_enable(TIM2_Peripheral);
    Peripheral_reset(TIM2_Peripheral);
    
    REG_TIM2_CTRL1 |= TIM2_APRE_bit; // Ativa o Autoreload.

    REG_TIM2_PSC = ((PCLK/PSC) - 1); // Carrega o valor do Prescaler

    REG_TIM2_ATRLR = ((Period << 1) - 1); // Carrega o valor de AutoReload.

    REG_TIM2_CTRL1 |= TIM2_CEN_bit; // Liga o timer 2

    REG_TIM2_DMAINTENR |= TIM2_UIE_bit;
    IRQ_enable(TIM2_IRQ);
    return (unsigned int)0x0;
}



void Stop_cliclic_TIM2(){

    IRQ_Disable(TIM2_IRQ);
    REG_TIM2_CTRL1 &= ~TIM2_CEN_bit;

}





















#endif