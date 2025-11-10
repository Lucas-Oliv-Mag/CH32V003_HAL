#ifndef PFIC_inc
#define PFIC_inc


#include <Core/Registers.h>

typedef enum IRQn_table
{
    /******  RISC-V Processor Exceptions Numbers *******************************************************/
    NonMaskableInt_IRQ = 2, /* 2 Non Maskable Interrupt                             */
    EXC_IRQ = 3,            /* 3 Exception Interrupt                                */
    SysTick_IRQ = 12,       /* 12 System timer Interrupt                            */
    Software_IRQ = 14,      /* 14 software Interrupt                                */

    /******  RISC-V specific Interrupt Numbers *********************************************************/
    WWDG_IRQ = 16,          /* Window WatchDog Interrupt                            */
    PVD_IRQ = 17,           /* PVD through EXTI Line detection Interrupt            */
    FLASH_IRQ = 18,         /* FLASH global Interrupt                               */
    RCC_IRQ = 19,           /* RCC global Interrupt                                 */
    EXTI_IRQ = 20,       /* External Line[7:0] Interrupts                        */
    AWU_IRQ = 21,           /* AWU global Interrupt                                 */
    DMA1_Ch1_IRQ = 22, /* DMA1 Channel 1 global Interrupt                      */
    DMA1_Ch2_IRQ = 23, /* DMA1 Channel 2 global Interrupt                      */
    DMA1_Ch3_IRQ = 24, /* DMA1 Channel 3 global Interrupt                      */
    DMA1_Ch4_IRQ = 25, /* DMA1 Channel 4 global Interrupt                      */
    DMA1_Ch5_IRQ = 26, /* DMA1 Channel 5 global Interrupt                      */
    DMA1_Ch6_IRQ = 27, /* DMA1 Channel 6 global Interrupt                      */
    DMA1_Ch7_IRQ = 28, /* DMA1 Channel 7 global Interrupt                      */
    ADC_IRQ = 29,           /* ADC global Interrupt                                 */
    I2C1_EV_IRQ = 30,       /* I2C1 Event Interrupt                                 */
    I2C1_ER_IRQ = 31,       /* I2C1 Error Interrupt                                 */
    USART1_IRQ = 32,        /* USART1 global Interrupt                              */
    SPI1_IRQ = 33,          /* SPI1 global Interrupt                                */
    TIM1_BRK_IRQ = 34,      /* TIM1 Break Interrupt                                 */
    TIM1_UP_IRQ = 35,       /* TIM1 Update Interrupt                                */
    TIM1_TRG_COM_IRQ = 36,  /* TIM1 Trigger and Commutation Interrupt               */
    TIM1_CC_IRQ = 37,       /* TIM1 Capture Compare Interrupt                       */
    TIM2_IRQ = 38,          /* TIM2 global Interrupt                                */

} IRQ_t;

typedef enum Priority_level_mode{High_Priority = 5, Extreme_Priority = 0, Low_Priority = 15, Medium_Priority = 7} Priority_t;
typedef enum Secure_mode_select{SECURE_MODE_ON, SECURE_MODE_OFF} Secure_t;
void IRQ_enable(IRQ_t IRQ); // Habilita a interrupcao


#define PFIC_SECURE_MODE_FLAG (unsigned int)0xFFU


void IRQ_enable(IRQ_t IRQ);


void IRQ_Disable(IRQ_t IRQ);


void IRQ_SetPriority(IRQ_t IRQn, Priority_t Priority);


unsigned int Secure_mode_set(Secure_t Mode);

void PFIC_Priority(Priority_t Minus_Priority);

void IRQ_Append(IRQ_t IRQ);

#endif