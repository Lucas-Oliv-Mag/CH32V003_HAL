
/*
___________________________________________________________________________________________________________________________________

    CRIADO POR: LUCAS O.M  | Data: 22/09/2025   | Brasil - SP

    TiTULO: Lib para utilizar o RCC

    DESC: Inicializa??o do clock, perif¨¦ricos, al¨¦m de reset dos mesmos!

___________________________________________________________________________________________________________________________________

*/


#ifndef RCC_LIB
#define RCC_LIB


#include <Core/Lib_config.h>
#include <Core/Registers.h>



// ___________ Offset Marcador de registrador  _________//

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


/**
 * @brief Funcao para udar o clock do microcontrolador em 24Mhz
 * 
 * @return unsigned int retorna true se houver algum erro.
 */
unsigned int StartUp_HSI_24Mhz();

/**
 * @brief Funcao para udar o clock do microcontrolador em 48Mhz
 * 
 * @return unsigned int retorna true se houver algum erro.
 */
unsigned int StartUp_PLL_48MHz();

/**
 * @brief Define o prescaler do barramento de clock dos perifericos.
 * 
 */
void HBB_PRESCALER_CFG(unsigned int Prescaler);


/**
 * @brief Habilita o clock do periferico informado.
 * 
 * @param Peripheral Exemplo: USART1_Peripheral
 * @attention  Nunca utilizar conversao de dados cast.
 */
void Peripheral_clock_enable(Peripheral_t Peripheral);



/**
 * @brief Desabilita o clock do periferico informado.
 * 
 * @param Peripheral Exemplo: USART1_Peripheral
 * @attention nunca utilizar conversao de dados cast.
 */
void Peripheral_clock_stop(Peripheral_t Peripheral);


/**
 * @brief Reinicia o periferico informado.
 * 
 * @param Peripheral Exemplo: USART1_Peripheral
 * @attention nunca utilizar conversao de dados cast
 */
void Peripheral_reset(Peripheral_t Peripheral);
  




#endif
