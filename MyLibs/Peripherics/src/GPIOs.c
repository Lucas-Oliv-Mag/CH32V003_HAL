#ifndef GPIOS_src
#define GPIOS_src

#include <Peripherics/inc/GPIOs.h>

unsigned int Pin_set (GPIO_t PORT, unsigned int Pin, unsigned int Type, Speed_t Speed){

    if(Pin > 7 || Type > 0x3U || Speed > 0x3U){ return 1;} // Caso os dados informados n?o forem validos, retornar¨¢ flag de erro.

    unsigned int Mode = 0x00;
    Mode = (Type<<2) | Speed; // Cria a mask para a configura??o do pino desejado.
   
   (*(volatile unsigned int*)PORT) &= ~(0xfU << (Pin * 4)); // Limpa a configura??o do pino para reescreve-la.
   (*(volatile unsigned int*)PORT) |= (Mode<<(Pin*4)); // Escreve a programa??o no pino atual.

   return 0;
}


volatile unsigned int Read_Pin(GPIO_t Port, unsigned int pin){

     if((( (*(volatile unsigned int*)(Port + _INDR)) >> pin ) & 0x1U) == 1 )
       {
        return 1;
       }
   else{
        return 0;
       }
}


unsigned int PORT_set(GPIO_t Port, unsigned char Pins, Pin_t Type){ // HIGH = PUSH/PULL OUTUPUT, LOW = FLOATING INPUT

   unsigned int i, Shift;
   volatile unsigned int* GPIO = (volatile unsigned int*)Port;
   
   if (Pins == 0U || Type > 0xFU) return 1;

   for(i = 0; i < 8; i++){

      if((Pins >> i) & 0x1)// Itera Pins para ver se o pino dever¨¢ ser configurado.
      { 
         Shift = i*4;

         *GPIO &= ~(0xfU<<Shift); // Limpa a configuracao do pino.
         *GPIO |=  Type<<Shift; // Configura para o tipo certo.
     
      }

   }

   return 0;
}


void Write_Pin(GPIO_t Port, unsigned char pin, unsigned int VALUE){

   if(VALUE == HIGH){
      (*(volatile unsigned int*)(Port + _BSRH)) |= 1<<pin;
   }else{
      (*(volatile unsigned int*)(Port + _BSRH)) |= 1<<(pin + 16);
   }  
   
}


void Write_Port(GPIO_t Port, unsigned char Data){

   (*(volatile unsigned int*)(Port + _BSRH)) = ( (unsigned int)~Data << 16) | (unsigned int) Data;

}


#endif // Fim da lib.