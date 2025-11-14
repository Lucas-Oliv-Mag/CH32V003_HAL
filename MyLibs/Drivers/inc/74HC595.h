#ifndef _74HC595_inc
#define _74HC595_inc
/*
___________________________________________________________________________________________________________________________________

    CRIADO POR: LUCAS O.M  | Data: 03/10/2025   | Brasil - SP

    TiTULO: Lib para utilizar o shiftregister 74HC595 e semelhantes.

    DESC: Inicialize a estrutura do shiftregister "ShiftReg", e após inicialize as rotinas 
    com o _74HC595_Init(), utilize os metodos Write_74HC595() para escrever Chars nas saídas do Shiftregister
    Existe a opção de enviar primeiro o LSB ou MSB.

    - OBS: Tem dependencia direta a GPIOs.h.

___________________________________________________________________________________________________________________________________

*/


#include <Peripherics/inc/GPIOs.h>

struct _74HC595{ // Cria a definição da estrutura de inicialização do shiftregister

  unsigned int ST_Pin,SH_Pin,Data_Pin;
  GPIO_t SH_Port, ST_Port, Data_Port;

}ShiftReg;  // Cria um elemento utilizavel.


void Write_74HC595(unsigned char data);

void Write_74HC595_LSB_First(unsigned char data);

unsigned int _74HC595_Init(unsigned int ST_Pin, unsigned int Data_Pin, unsigned int SH_Pin,GPIO_t PORT_FOR_ALL);



#endif