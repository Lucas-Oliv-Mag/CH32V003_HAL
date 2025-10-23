
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


struct _74HC595{ // Cria a definição da estrutura de inicialização do shiftregister

  unsigned int ST_Pin,SH_Pin,Data_Pin;
  GPIO_t SH_Port, ST_Port, Data_Port;

}ShiftReg;  // Cria um elemento utilizavel.


/**
 * @brief Envia ao ShiftRegister o valor de data, primeiro o LSB.
 * 
 * @param data Char de 8 bits
 */
void Write_74HC595(unsigned char data){

  if(data > 0xff){return;} // Caso o valor enviado não seja um caracter.

   Write_Pin(ShiftReg.ST_Port,ShiftReg.ST_Pin,LOW); //
   Write_Pin(ShiftReg.SH_Port,ShiftReg.SH_Pin,LOW); // 


   for(unsigned int i=7 ;i >= 0; i--){// Repete para cada bit de data
   Write_Pin(ShiftReg.Data_Port,ShiftReg.Data_Pin, (data>>i) & 0x1);// Envia o I-ижsimo bit de data (LSB first)
   Write_Pin(ShiftReg.SH_Port,ShiftReg.SH_Pin,HIGH); // Envia o clock
   Write_Pin(ShiftReg.SH_Port,ShiftReg.SH_Pin,LOW);
   }

   Write_Pin(ShiftReg.ST_Port,ShiftReg.ST_Pin,HIGH); // Ativa as saикdas, revelando o valor.
   Write_Pin(ShiftReg.ST_Port,ShiftReg.ST_Pin,LOW); // Ativa as saикdas, revelando o valor.
  

  // Envia (LSB -> MSB).
}


void Write_74HC595_LSB_First(unsigned char data){
  unsigned int i;

   Write_Pin(ShiftReg.ST_Port,ShiftReg.ST_Pin,0); // Desliga o enable para desligar as saикdas

   for(i=0;i<=7;i++){// Repete para cada bit de data
   Write_Pin(ShiftReg.Data_Port,ShiftReg.Data_Pin, (data>>i) & 0x1);// Envia o I-ижsimo bit de data (LSB first)
   Write_Pin(ShiftReg.SH_Port,ShiftReg.SH_Pin,1); // Envia o clock
   Write_Pin(ShiftReg.SH_Port,ShiftReg.SH_Pin,0);
   }

   Write_Pin(ShiftReg.ST_Port,ShiftReg.ST_Pin,1); // Ativa as saикdas, revelando o valor.
  

  // Envia (LSB -> MSB).
}


/**
 * @brief Inicializa o 74HC595 com todos os pinos no mesmo grupo GPIO (PORT).
 * @param ST_Pin Pino para o Latch clock (ST_CP).
 * @param Data_Pin Pino de dados (DS).
 * @param SH_Pin Pino de clock de deslocamento (SH_CP).
 * @param PORT Grupo GPIO a ser utilizado para todos os pinos.
 * @return Retorna 1 se a configura??o for bem-sucedida, ou 0 caso contrивrio.
 */
unsigned int _74HC595_Init(unsigned int ST_Pin, unsigned int Data_Pin, unsigned int SH_Pin,GPIO_t PORT_FOR_ALL){

    if(ST_Pin > 7 || Data_Pin >7 || SH_Pin >7){return 1;}
    if(PORT_FOR_ALL > 0x40011400U || PORT_FOR_ALL <0x40010800U){return 1;}// Retorna ERRO, pois nao foi possivel configurar os pinos do 74HC595

     ShiftReg.ST_Pin = ST_Pin;      // Configura os pinos que
     ShiftReg.Data_Pin = Data_Pin; //  Irao realizer interface
     ShiftReg.SH_Pin = SH_Pin;    // Com o Shiftregister.
  
     ShiftReg.ST_Port = PORT_FOR_ALL;   // Define Qual PORT 
     ShiftReg.Data_Port = PORT_FOR_ALL; // Utilizado em conjunto
     ShiftReg.SH_Port = PORT_FOR_ALL;   // Com os pinos acima.

     return 0;
}