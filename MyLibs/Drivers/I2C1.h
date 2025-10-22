
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


#ifndef I2C1_LIB
#define I2C1_LIB

#define REG_I2C_CTLR1   (*(volatile unsigned int*)0x40005400)  // I2C control register 1 0x0000
#define REG_I2C_CTLR2   (*(volatile unsigned int*)0x40005404) //I2C control register 2 0x0000
#define REG_I2C_OADDR1  (*(volatile unsigned int*)0x40005408) //I2C address register 1 0x0000
#define REG_I2C_OADDR2  (*(volatile unsigned int*)0x4000540C) //I2C address register 2 0x0000
#define REG_I2C_DATAR   (*(volatile unsigned int*)0x40005410)  //I2C data register 0x0000
#define REG_I2C_STAR1   (*(volatile unsigned int*)0x40005414)  //I2C status register 1 0x0000
#define REG_I2C_STAR2   (*(volatile unsigned int*)0x40005418)  //I2C status register 2 0x0000
#define REG_I2C_CKCFGR  (*(volatile unsigned int*)0x4000541C) //I2C clock register 0x0000




// MSB First, LSB after.


unsigned int Init_I2C1(I2C_t Mode){




    switch (Mode) {

        case Master: break;





        case Slave:  break;

        default: return 1;

    }
    return 0;
}


void Stop_I2C1(){



}



void Write_I2C1(){



}

char Read_I2C1(unsigned int Adress, unsigned int reg){



    //return data ;
}






#endif // Fim da lib.