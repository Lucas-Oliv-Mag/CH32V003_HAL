
/*
___________________________________________________________________________________________________________________________________

    CRIADO POR: LUCAS O.M  | Data: 22/09/2025   | Brasil - SP

    TiTULO: Lib para utilizar o RCC

    DESC: Inicializa??o do clock, perif¨¦ricos, al¨¦m de reset dos mesmos!

___________________________________________________________________________________________________________________________________

*/


#ifndef RCC_LIB
#define RCC_LIB

// ___________ Registradores de configuracao _________//
#define REG_RCC_CTLR        (*(volatile unsigned int*)0x40021000) //Clock control register                 - Reset value: 0x0000xx83
#define REG_RCC_CFGR0       (*(volatile unsigned int*)0x40021004) //Clock configuration register 0         - Reset value: 0x00000020
#define REG_RCC_INTR        (*(volatile unsigned int*)0x40021008) //Clock interrupt register               - Reset value: 0x00000000
#define REG_RCC_APB2PRSTR   (*(volatile unsigned int*)0x4002100C) //PB2 peripheral reset register          - Reset value: 0x00000000
#define REG_RCC_APB1PRSTR   (*(volatile unsigned int*)0x40021010) //PB1 peripheral reset register          - Reset value: 0x00000000
#define REG_RCC_AHBPCENR    (*(volatile unsigned int*)0x40021014)//HB peripheral clock enable register     - Reset value: 0x00000004
#define REG_RCC_APB2PCENR   (*(volatile unsigned int*)0x40021018) //PB2 peripheral clock enable register   - Reset value: 0x00000000
#define REG_RCC_APB1PCENR   (*(volatile unsigned int*)0x4002101C) //PB1 peripheral clock enable register   - Reset value: 0x00000000
#define REG_RCC_RSTSCKR     (*(volatile unsigned int*)0x40021024)// Control/status register                - Reset value: 0x0C000000


// ___________ Bits de ativa??o _________//

//  HB Peripheral Clock Enable Register (RCC_AHBPCENR).
#define SRAM_EN_bit   (1<<2)
#define DMA1_EN_bit   (1<<0)
//--
//PB2 Peripheral Clock Enable Register (RCC_APB2PCENR).
#define TIM1_EN_bit   (1<<11)
#define TIM2_EN_bit   (1<<0 )
#define ADC1_EN_bit   (1<<9 )
#define USART1_EN_bit (1<<14)
#define GPIOD_EN_bit  (1<<5 )
#define GPIOC_EN_bit  (1<<4 )
#define GPIOA_EN_bit  (1<<2 )
#define AFIOEN_EN_bit (1<<0 )
#define SPI1_EN_bit   (1<<12)
#define WWDG_EN_bit   (1<<11 )
//--
//PB1 Peripheral Clock Enable Register (RCC_APB1PCENR).
#define PWR_EN_bit    (1<<28)
#define I2C1_EN_bit   (1<<21)


// ___________ Marcador de registrador  _________//

#define PB1_OFFSET 100U
#define PB2_OFFSET 200U
#define  HB_OFFSET 33U

//--


typedef enum Peripherics {
  // -- Perifericos do HB, Sem OFFSET por quest?es de condicionamento
  DMA_Peripheral  = 0,
  SRAM_Peripheral = 2,
  // -- Perifericos do PB2 
  USART1_Peripheral= PB2_OFFSET + 14, 
  SPI1_Peripheral  = PB2_OFFSET + 12,
  TIM1_Peripheral  = PB2_OFFSET + 11,
  ADC1_Peripheral  = PB2_OFFSET + 9, 
  GPIOD_Peripheral = PB2_OFFSET + 5, 
  GPIOC_Peripheral = PB2_OFFSET + 4,
  GPIOA_Peripheral = PB2_OFFSET + 2,
  AFIO_Peripheral  = PB2_OFFSET + 0,
  // Perifericos do PB1
  PWR_Peripheral  = PB1_OFFSET + 28, 
  I2C1_Peripheral = PB1_OFFSET + 21,
  WWDG_Peripheral = PB1_OFFSET + 11,
  TIM2_Peripheral = PB1_OFFSET +  0
  
  } Peripheral_t;



unsigned int SYSCLK; // Clock do processador em Hz
unsigned int PCLK; // Clock dos perif¨¦ricos, SYSCKL depois do HPRE, em Hz

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


/**
 * @brief Habilita o clock do periferico informado.
 * 
 * @param Peripheral Exemplo: USART1_Peripheral
 * @attention  Nunca utilizar conversao de dados cast.
 */
void Peripheral_clock_enable(Peripheral_t Peripheral){
 
  if(Peripheral < HB_OFFSET){ // Perifericos do registrador HB

   REG_RCC_AHBPCENR |= (1<<Peripheral) ;

  }else if( Peripheral >= PB2_OFFSET){ // Perifericos do registrador PB2

  REG_RCC_APB2PCENR |= (1<<(Peripheral-PB2_OFFSET));
  
  }else if(Peripheral >= PB1_OFFSET){ // Perifericos do registrador PB1

  REG_RCC_APB1PCENR |= (1<<(Peripheral-PB1_OFFSET));

  }

}



/**
 * @brief Desabilita o clock do periferico informado.
 * 
 * @param Peripheral Exemplo: USART1_Peripheral
 * @attention nunca utilizar conversao de dados cast.
 */
void Peripheral_clock_stop(Peripheral_t Peripheral){

 
  if(Peripheral < HB_OFFSET){ // Perifericos do registrador HB

   REG_RCC_AHBPCENR &= ~(1<<Peripheral) ;

  }else if( Peripheral >= PB2_OFFSET){ // Perifericos do registrador PB2

   REG_RCC_APB2PCENR &= ~(1<<(Peripheral-PB2_OFFSET));

  }else if(Peripheral >= PB1_OFFSET){ // Perifericos do registrador PB1

   REG_RCC_APB1PCENR &= ~(1<<(Peripheral-PB1_OFFSET));

  }

}


/**
 * @brief Reinicia o periferico informado.
 * 
 * @param Peripheral Exemplo: USART1_Peripheral
 * @attention nunca utilizar conversao de dados cast
 */
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
