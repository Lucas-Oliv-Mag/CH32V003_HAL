#ifndef EXTI_inc
#define EXTI_inc


#include <Core/Registers.h>
#include <Peripherics/inc/GPIOs.h>

typedef enum EXTI_TRIGGERS{Rising_Edge, Falling_Edge, Rising_Faling_Edge} EXTI_Trigger_t;

void External_interrupt_set(GPIO_t PORT, unsigned int Pin, EXTI_Trigger_t Trigger);


void External_interrupt_clear(GPIO_t PORT, unsigned int Pin);

unsigned int EXTI_flags();

#endif