
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


#include <Core/Lib_config.h>

// MSB First, LSB after.

typedef enum SERIAL_BUS_MODE I2C_t;

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