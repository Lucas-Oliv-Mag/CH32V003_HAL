#ifndef RCC_SRC
#define RCC_SRC

#include <Peripherics/inc/RCC.h>


unsigned int SYSCLK; // Clock do processador em Hz
unsigned int PCLK; // Clock dos perifericos, SYSCKL depois do HPRE, em Hz

unsigned int StartUp_HSI_24Mhz(){

    REG_RCC_CTLR |= 0x1;  // liga o HSI
    REG_RCC_CTLR &= ~(1 << 16);                      // Desliga o HSE
    do { __asm__ ("nop"); } while ((REG_RCC_CTLR & 0x2) == 0);
    REG_RCC_CFGR0 &= ~0x3;                           // define o HSI como SYSCLK

    SYSCLK = 24000000;
    return 1;
}

       
unsigned int StartUp_PLL_48MHz(){


   REG_RCC_CFGR0 &= ~(1<<16); // Define o HSI como fonte de clock do PLL.
   REG_RCC_CTLR |= (1<<24); // Seta o bit 24 PLLON para ligar o PLL

   do{ __asm__("nop"); } 
   while((REG_RCC_CTLR & (1<<25)) == 0);// verifica se o PLL esta pronto.
   

   REG_RCC_CFGR0 &= ~0x3; // limpa os bits do SYSCLK
   REG_RCC_CFGR0 |=  0x2; // Define o PLL como fonte do SYSCLK


   SYSCLK = 48000000;
   return 1;
}


void HBB_PRESCALER_CFG(unsigned int Prescaler){

   REG_RCC_CFGR0 &= ~(0b1111 << 4); // Limpa os bits do HBCKL

   if(Prescaler < 8 && Prescaler > 1){
     REG_RCC_CFGR0 |= ((Prescaler - 1) << 4); 

   }else if(Prescaler == 16){

     REG_RCC_CFGR0 |= (((unsigned int)0b1011) << 4);
 
   }else if(Prescaler == 32){

     REG_RCC_CFGR0 |= (((unsigned int)0b1100) << 4);
   }

   if(Prescaler != 0){PCLK = PCLK/Prescaler;
   }else{ PCLK = SYSCLK; }
}


void Peripheral_clock_enable(Peripheral_t Peripheral){
 
  if(Peripheral < HB_OFFSET){ // Perifericos do registrador HB

   REG_RCC_AHBPCENR |= (1<<Peripheral) ;

  }else if( Peripheral >= PB2_OFFSET){ // Perifericos do registrador PB2

  REG_RCC_APB2PCENR |= (1<<(Peripheral-PB2_OFFSET));
  
  }else if(Peripheral >= PB1_OFFSET){ // Perifericos do registrador PB1

  REG_RCC_APB1PCENR |= (1<<(Peripheral-PB1_OFFSET));

  }

}



void Peripheral_clock_stop(Peripheral_t Peripheral){

 
  if(Peripheral < HB_OFFSET){ // Perifericos do registrador HB

   REG_RCC_AHBPCENR &= ~(1<<Peripheral) ;

  }else if( Peripheral >= PB2_OFFSET){ // Perifericos do registrador PB2

   REG_RCC_APB2PCENR &= ~(1<<(Peripheral-PB2_OFFSET));

  }else if(Peripheral >= PB1_OFFSET){ // Perifericos do registrador PB1

   REG_RCC_APB1PCENR &= ~(1<<(Peripheral-PB1_OFFSET));

  }

}


void Peripheral_reset(Peripheral_t Peripheral){

  unsigned int shifter_bit; // Variavel auxiliar, utilizada para extrair o bit que representa o periferico.

  if( Peripheral >= PB2_OFFSET){ // Perifericos do registrador PB2

   shifter_bit = Peripheral - PB2_OFFSET;   // Retira o offset para extrair o bit alvo.

   REG_RCC_APB2PRSTR |=  (1<<shifter_bit);  // Reseta o Periferico.
   REG_RCC_APB2PRSTR &= ~(1<<shifter_bit);  // Normaliza o Periferico.

  }
  else if(Peripheral >= PB1_OFFSET){ // Perifericos do registrador PB1

   shifter_bit = Peripheral - PB1_OFFSET;   // Retira o offset para extrair o bit alvo.
   REG_RCC_APB1PRSTR |=  (1<<shifter_bit);  // Reseta o Periferico.
   REG_RCC_APB1PRSTR &= ~(1<<shifter_bit);  // Normaliza o Periferico.

  }
  
}




#endif
