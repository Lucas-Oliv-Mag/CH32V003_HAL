#ifndef ADC_inc
#define ADC_inc


#define CAL_bit      (1<<2)
#define RCAL_bit     (1<<3)
#define RCC_ADC_EN   (1<<9)
#define ALGN_Right  ~(1<<11)
#define AD_ON        (1<<0)


#define Continuos 1
#define Single    0

//O registrador ADC_RSQRx seleciona os canais que ser?o convertidos para o Grupo de regras de convers?o, e ent?o armazena o valor da leitura sequencialmente, e ativa a flag de interrup??o.


/**
 * @brief Inicializa o modulo ADC1
 * 
 * @param Channels 
 * @param Mode 
 * @param Trigger 
 * @return int 
 */
int Init_ADC(unsigned char Channels, unsigned int Mode, unsigned int Trigger);



unsigned int ADC_Read();


#endif