#ifndef EXTI_inc
#define EXTI_inc

typedef enum EXTI_TRIGGERS{Rising_Edge, Falling_Edge, Rising_Faling_Edge} EXTI_Trigger_t;

void External_interrupt_set(GPIO_t PORT, unsigned int Pin, EXTI_Trigger_t Trigger){

    if(Pin > 7){ return; }

    unsigned int tempreg = (1<<Pin); // Mascara para manipular os bits.

    REG_EXTI_EVENR  |= tempreg; // Habilita o evento
    REG_EXTI_INTENR |= tempreg; // Habilita a interrupcao

    if(Trigger == Rising_Edge  || Trigger == Rising_Faling_Edge){ REG_EXTI_RTENR |= (1<<Pin);} // Habilita detector de borda de subida
    if(Trigger == Falling_Edge || Trigger == Rising_Faling_Edge){ REG_EXTI_FTENR |= (1<<Pin);} // Habilita a borda de descida

    switch (PORT) {
    
        case PORTA: tempreg = (unsigned int)0x00U; break;
        case PORTC: tempreg = (unsigned int)0x02U; break;
        case PORTD: tempreg = (unsigned int)0x03U; break;

    }

    REG_AFIO_EXTICR &=  ~(0x03U<<(Pin*2));  //Limpa a selecao do PORT 
    REG_AFIO_EXTICR |= (tempreg<<(Pin*2)); // Seleciona o PORT do canal EXTI
}


void External_interrupt_clear(GPIO_t PORT, unsigned int Pin){

 if(Pin > 7){ return; }

    unsigned int tempreg = ~(1<<Pin); // Mascara para manipular os bits.

    REG_EXTI_EVENR  &= tempreg; // Habilita o evento
    REG_EXTI_INTENR &= tempreg; // Habilita a interrupcao

    REG_AFIO_EXTICR &=  ~(0x03U<<(Pin*2));  //Limpa a selecao do PORT 

}














#endif