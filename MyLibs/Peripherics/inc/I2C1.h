#ifndef I2C1_inc
#define I2C1_inc

#include <Core/Registers.h>
#include <Core/Lib_config.h>
#include <Peripherics/inc/GPIOs.h>




/*
___________________________________________________________________________________________________________________________________

    CRIADO POR: LUCAS O.M  | Data: 21/10/2025   | Brasil - SP

    TiTULO: Lib para utilizar o m§Ú§àdulo I2C o CH32V0003

    DESC: 

    - OBS: Tem dependencia direta a GPIOs.h.

___________________________________________________________________________________________________________________________________

*/


// Bits de controle

#define I2C1_ST 8
#define I2C1_PE 0

#define I2C1_FS 15

#define I2C1_ACK 10

extern unsigned int PCLK;
extern unsigned int SYSCLK;

typedef enum SERIAL_BUS_MODE I2C_t;

unsigned int Init_I2C1(I2C_t Mode);

void Stop_I2C1();

char Read_I2C1(unsigned int Adress, unsigned int reg);


// MSB First, LSB after.



#endif // Fim da lib.
