
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


unsigned int Init_I2C1(I2C_t Mode){

    Peripheral_reset(I2C1_Peripheral);
    Peripheral_clock_enable(I2C1_Peripheral);
 
    Peripheral_clock_enable(GPIOC_Peripheral);
    Peripheral_clock_enable(AFIO_Peripheral);
 
    Pin_set(PORTC,5, Mult_Open_Drain,_50MHz); // Define SCL como push pull
    Pin_set(PORTC,6, Mult_Open_Drain,_50MHz); // Define SDA como saida dreno aberto


    REG_I2C1_CKCFGR &= ~(1<<I2C1_FS); // Velocidade Standart


    switch (Mode) {

        case Master: 

        REG_I2C1_CTLR1 = (1<<I2C1_PE);

        //REG_I2C1_CTRL2 = (1<<0x00U);
     

        break;

        case Slave:  break;





        default: return 1;

    }
    return 0;
}


void Stop_I2C1(){

        Peripheral_clock_stop(I2C1_Peripheral);
        Peripheral_reset(I2C1_Peripheral);

}


void Write_I2C1_polling(char Adress, char Data){

    REG_I2C1_CTLR1 |= (1<<I2C1_ST); // Inicia trasmiss?o.

    REG_I2C1_DATAR = Adress;
    

    
    REG_I2C1_DATAR = Data;

}

char Read_I2C1(unsigned int Adress, unsigned int reg){

    return REG_I2C1_DATAR;
}






#endif // Fim da lib.