
/*
___________________________________________________________________________________________________________________________________

    CRIADO POR: LUCAS O.M  | Data: 21/10/2025   | Brasil - SP

    TiTULO: HAL para GPIOs - CH32V003F4P6

    DESC: Inicialização, configuração, operação das GPIOs, desde configurar um port inteiro, a manipular apenas um pino.

    - OBS: Tem dependencia direta da biblioteca

___________________________________________________________________________________________________________________________________

*/

// ___________ Offset  dos Registradores de configuracao _________//
#define _INDR   0x08U
#define _OUTDR  0x0CU
#define _BSRH   0x10U
#define _BCR    0x14U
#define _LCKR   0x18U


// ___________ Definição dos estados lógicos _________//
#define OUTPUT 0x00U
#define INPUT  0x01U

#define HIGH 0x01U
#define LOW 0x00U

// ___________ Tipos de dados para configuração _________//

typedef enum PORT{ // Contem os endereços dos registradores de CGRL de cada PORT

PORTA=  0x40010800U,
PORTC=  0x40011000U,
PORTD=  0x40011400U
} GPIO_t;

typedef enum Pin_Type{

// OUTPUT MODEs
Push_Pull_out    = 0x0U, // Saida PUSH/PULL, Niveis lógicos ALTO e BAIXO somente.
Open_Drain_out   = 0x1U, // Saida com dreno aberto, apenas puxa para o nivel lógico BAIXO.

Mult_push_pull   = 0x2U, // Modo de saída PUSH/PULL multiplexada para outros periféricos.
Mult_Open_Drain  = 0x3U, // Modo de saída com dreno aberto multiplexada para outros perifericos.

// INPUT MODEs
Pull_up_in       = 0x2U, // Modo de entrada com resistor de pullup,   nescessario configurar.
Drop_Down_in     = 0x2U, // Modo de entrada com resistor de pulldown, nescessario configurar.
Floating_in      = 0x1U, // Modo de entrada flutuante, precisa de polarização externa.
Analog_in        = 0x0U  // Modo de entrada analógica para os conversores ADC, ou OPAMPs


} Pin_t;


typedef enum Pin_Speed{
   
_10MHz = 0x1U,
_30MHZ = 0x2U,
_50MHz = 0x3U

} Speed_t;





/**
 * @brief Configura um pino terminal I/O, com os parametros especificados (Não utilizar cast).
 * 
 * @param Port Qual GPIO esta se referenciando, Ex: PORTC.
 * @param Pin  Qual pino esta se referenciando, Ex: 0 ~ 7.
 * @param Type Qual a configuracao deste pino, Ex: Push_Pull_out.
 * @param Speed Velocidade do pino, Ex: _10MHz.
 * @return Retorna 1 em caso de erro.
 */
 unsigned int Pin_set (GPIO_t PORT, unsigned int Pin, unsigned int Type, Speed_t Speed){

    if(Pin > 7 || Type > 0x3U || Speed > 0x3U){ return 1;} // Caso os dados informados não forem validos, retornará flag de erro.

    unsigned int Mode = 0x00;
    Mode = (Type<<2) | Speed; // Cria a mask para a configuração do pino desejado.
   
   (*(volatile unsigned int*)PORT) &= ~(0xfU << (Pin * 4)); // Limpa a configuração do pino para reescreve-la.
   (*(volatile unsigned int*)PORT) |= (Mode<<(Pin*4)); // Escreve a programação no pino atual.

   return 0;
 }


/**
 * @brief Devolve o valor logico do pino especificado.
 * 
 * @param Port GPIO do pino em questao, ex: PORTC.
 * @param pin  Pino ao qual deve ser lido, ex: 0 ~ 7.
 * @return unsigned int (HIGH ou LOW).
 */
unsigned int Read_Pin(GPIO_t Port, unsigned int pin){

     if((((*(volatile unsigned int*)(Port + _INDR)) >> pin ) & 0x1U) == 1 )
       {
        return 1;
       }
   else{
       return 0;
       }
 }



/**
 * @brief Esta funcao configura os pinos do port com o tipo especificado em Type
 * 
 * @param Port GPIO que deseja configurar
 * @param Pins Pinos selecionados em formato binario, Ex: Pino 1 e 5 = 0x22 (0b00100010)
 * @param Type Configuracao de que tipo serao confingurados os pinos.
 * @return Retorna TRUE em caso de erro, e FALSE quando bem sucedido.
 */
unsigned int GPIO_set(GPIO_t Port, unsigned char Pins, Pin_t Type){ // HIGH = PUSH/PULL OUTUPUT, LOW = FLOATING INPUT

   unsigned int i, Shift;
   volatile unsigned int* GPIO = (volatile unsigned int*)Port;
   
   if (Pins == 0U || Type > 0xFU) return 1;

   for(i = 0; i < 8; i++){

      if((Pins >> i) & 0x1)// Itera Pins para ver se o pino deverá ser configurado.
      { 
         Shift = i*4;

         *GPIO &= ~(0xfU<<Shift); // Limpa a configuracao do pino.
         *GPIO |=  Type<<Shift; // Configura para o tipo certo.
     
      }

   }

   return 0;
}


/**
 * @brief Alterará o estado do pino terminal informado.
 * 
 * @param Port GPIO do pino, Ex: PORTC.
 * @param pin  O numero do pino, Ex: 1~7.
 * @param VALUE O estado lógico que o pino deve estar, Ex: HIGH
 */
void Write_Pin(GPIO_t Port, unsigned char pin, int VALUE){

   if(VALUE == HIGH){
      (*(volatile unsigned int*)(Port + _BSRH))  = 1<<pin;
   }else{
      (*(volatile unsigned int*)(Port + _BSRH)) = 1<<(pin + 16);
   }  
}

/**
 * @brief No GPIO informado, escrevera o valor de Data.
 * 
 * @param Port Informa a GPIO a ser utilizada, ex: PORTC
 * @param Data Qual valor sera impresso no GPIO escolhido.
 */
void Write_Port(GPIO_t Port, unsigned char Data){

   (*(volatile unsigned int*)(Port + _BSRH)) = ( (unsigned int)~Data << 16) | (unsigned int) Data;

}