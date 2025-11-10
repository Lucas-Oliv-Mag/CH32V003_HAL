
/*
___________________________________________________________________________________________________________________________________

    CRIADO POR: LUCAS O.M  | Data: 21/10/2025   | Brasil - SP

    TiTULO: Lib para utilizar o m®Ædulo I2C o CH32V0003

    DESC: 

    - OBS: Tem dependencia direta a GPIOs.h.

___________________________________________________________________________________________________________________________________

*/

/*


Basicamente configuramos o clock do perif®¶rico,

Escrevemos o endere?o do slave, junto ao 8°„Bit, que descreve a fun??o.

*/


#ifndef I2C1_src
#define I2C1_src

#include <Peripherics/inc/I2C1.h>
#include <Peripherics/inc/RCC.h>


// MSB First, LSB after.
/**
 * @brief Inicia o modulo I2C1,
 * 
 * @return unsigned int 
 */
unsigned int Init_I2C1_Master(){

    unsigned int tempreg;

    Peripheral_reset(I2C1_Peripheral);
    Peripheral_clock_enable(I2C1_Peripheral);
 
    Peripheral_clock_enable(GPIOC_Peripheral);
    Peripheral_clock_enable(AFIO_Peripheral);
 
    Pin_set(PORTC,2, Mult_Open_Drain,_10MHz); // Define SCL como push pull
    Pin_set(PORTC,1, Mult_Open_Drain,_10MHz); // Define SDA como saida dreno aberto


    // CONFIGURACAO DO CLOCK.
    // Obtem o clock em MHz 
    tempreg = PCLK/1000000; // Ortem MHz
    REG_I2C1_CTLR2 &= ~((unsigned int)0x3fU); // Limpa os bits de Frequencia
    REG_I2C1_CTLR2 |= (tempreg & 0x3fU);// Limpa os bits excedentes.

    tempreg = PCLK/200000;
    REG_I2C1_CKCFGR &= ~0xfff; // Limpa o valor de CCR.
    REG_I2C1_CKCFGR |= tempreg;// CKCFGR = CLock dos perifericos/( Velocidade desejada * 2)
    REG_I2C1_CKCFGR &= ~(1<<I2C1_FS); // Velocidade Standart

    REG_I2C1_CTLR1 |= (1<<I2C1_ACK);
    REG_I2C1_CTLR1 |= (1<<I2C1_PE);

    return 0;
}


void Stop_I2C1(){

        Peripheral_clock_stop(I2C1_Peripheral);
        Peripheral_reset(I2C1_Peripheral);
}

/**
 * @brief Escreve os chars contidos em Buffer para o dispositivo I2C mencionado em Adress
 * 
 * @param Adress 
 * @param Data 
 * @return Caso houver algum erro na trasmissao, retornara a messagem.
 */
I2C_msg_t Write_I2C1_polling(char Adress, char * Buffer){

   unsigned int Lenght =  String_counter(Buffer);
   unsigned int Trash; // Serve para somente limpar as flags dos registradores, por meio da leitura 

   // CONDICAO DE START.
    REG_I2C1_CTLR1 |= (1<<I2C1_START); // Inicia trasmiss?o.

    do{
        __asm__("nop");
    }while( ((REG_I2C1_STAR1 >> I2C1_SB) & 0x01) != 1 );

    // ENVIO DO ENDERECO E ESPERA DO ACK DO SLAVE
    REG_I2C1_DATAR = (Adress<<1);
    
    do{
        __asm__("nop");
    }while( ((REG_I2C1_STAR1 >> I2C1_ADDR) & 0x01) != 1); // Espera o ACK ou NACK do Slave

    if( ((REG_I2C1_STAR1 >> I2C1_AFO) & 0x01 ) == 1){ return SLAVE_NON_ADRR;} // Slave n?o respondeu.

    Trash = REG_I2C1_STAR2;  // Limpa as flags.
    if(Trash){ __asm__("nop");}


    // ENVIO DOS BYTES DE DADOS.
    for(unsigned int i = 0; i < Lenght; i++){ // Enviara todos os bytes pela serial

        REG_I2C1_DATAR = Buffer[i];
    
        do{
        __asm__("nop");
        }while( ((REG_I2C1_STAR1 >> I2C1_BTF) & 0x01 ) != 1);

        if( ((REG_I2C1_STAR1 >> I2C1_AFO) & 0x01 ) == 1){ 
            if(i == Lenght){return SLAVE_DATA_REJECT;}
            else{ return SLAVE_NON_ACK;}
        } // Slave n?o respondeu.

    }

    REG_I2C1_CTLR1 |= (1<<I2C1_STOP); // Finaliza comunicacao


    REG_I2C1_CTLR1 |= I2C1_SWRST;
    return NO_ERROR;
}

char Read_I2C1(unsigned int Adress, unsigned int reg){
   
   char Aux[1] = {reg};
    Write_I2C1_polling(Adress,Aux);

    return REG_I2C1_DATAR;
}



I2C_msg_t Write_I2C1(char Adress, char * Buffer, unsigned int Lenght_of_buffer){

    static unsigned int State = 0;
    static unsigned int Bytes;
    static unsigned int Lenght;
    static unsigned int Timeout;

    if(State == 0) {
        Timeout = 0U;
        Bytes   = 0U;
        Lenght  = Lenght_of_buffer;
    }

    switch (State) {

    case 0: // Ativar barramento i2c
        REG_I2C1_CTLR1 |= (1<<I2C1_START); // Inicia trasmiss?o.
        State++;
    break;

    case 1:// Enviar endereco do Slave
        if(((REG_I2C1_STAR1 >> I2C1_SB) & 0x01) == 1)
        { // Caso SB j? foi setado
         REG_I2C1_DATAR = (Adress<<1);
         State++;
        }else{ Timeout++; }
    break;
    case 2: // Enviar o primeiro Byte.

        if(((REG_I2C1_STAR1 >> I2C1_ADDR) & 0x01) == 1 ){// Espera o ACK ou NACK do Slave

             if( ((REG_I2C1_STAR1 >> I2C1_AFO) & 0x01 ) == 1){ // Caso der erro de ACK

                State = 0;
                return SLAVE_NON_ADRR;// Slave nao respondeu.

            }else{
                Timeout = REG_I2C1_STAR2 - REG_I2C1_STAR2; // Apenas para limpar a flag ADDR.

                REG_I2C1_DATAR = Buffer[0]; 
                Bytes++; State++;
                Timeout = 0;
            }
        }else{ Timeout ++;}

    break;

    case 3:// Envia os outros Bytes
        if(((REG_I2C1_STAR1 >> I2C1_BTF) & 0x01) == 1 ){


             if( ((REG_I2C1_STAR1 >> I2C1_AFO) & 0x01 ) == 1){ 

                State = 0;
                return SLAVE_NON_ACK;// Slave nao respondeu.

            }else{

               Timeout = 0;
               if(Bytes < Lenght){
                  REG_I2C1_DATAR = Buffer[Bytes]; 
                  Bytes++;
            
              }else{
                  State++;
                }
            }
        }else{ Timeout ++;}

    break;
    case 4: // Parar barramento
        REG_I2C1_CTLR1 |= (1<<I2C1_STOP); // Finaliza comunicacao
        State = 0;
        return NO_ERROR;
    break;
    }

    if(Timeout > 100){
        State = 0;
        return SLAVE_NO_RESPOND;
    }

    return BUSY;
}







#endif // Fim da lib.