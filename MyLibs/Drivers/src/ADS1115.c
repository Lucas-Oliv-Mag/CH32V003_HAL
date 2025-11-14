#ifndef ADS1115_src
#define ADS1115_src

#include <Drivers/inc/ADS1115.h>

I2C_msg_t Config_ADS115(ADS1115_t* ADC, unsigned int* Buffer_out){

   // char Buffer[3];
   // I2C_msg_t Request;
    unsigned int Reg = 0U;
    Reg |= ((1<<ADS1115_OS)                       | // Tira o modulo do power-down.
            (ADC->Programable_gain<<ADS1115_PGA)  |                        // Configura o ganho programavel
            (ADC->Sample_rate<<ADS1115_DATA_RATE) |                 // Configura a taxa de amostragem
            (ADC->Actual_Channel<<ADS1115_MUX)    |                // Configura o pino
            (((ADC->COMP_POLARITY & 0x01U)<<ADS1115_COMP_POL))); // Configura a polaridade.

    switch (ADC->Actual_Mode) {

    case Single_Shot:
        Reg |= ( (1<<ADS1115_MODE) | (0x3U<<ADS1115_COMP_QUE));  // Precisa enviar comando de trigger para iniciar a conversao
        break;
    case Continuos_mode: 
        Reg |= (0x3U<<ADS1115_COMP_QUE); // Pino de Alert indica quando uma conversao esta pronta.
        break;
    case Windows_Comparator:
        Reg |= (1<<ADS1115_COMP_MODE); // Modo de comparador janela.
        break;
    case Hysteresi_Comparator: break;
    }

    Buffer_out[0] = REG_ADS1115_CONFIGURATION; // Armazena o valor do registrador de config.

    Buffer_out[1] = ((Reg & 0xff00)>>8); // Obtem MSB

    Buffer_out[2] = (Reg & 0x00ff); // Obtem LSB

    Buffer_out[3] = '\0';

    ADC->Config = Reg;

    return 0;
}



#endif