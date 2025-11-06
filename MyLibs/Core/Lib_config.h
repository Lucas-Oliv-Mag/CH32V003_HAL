
#ifndef LIB_CONFIG
#define LIB_CONFIG
// VARIAVEIS GLOBAIS 

// Clock & PLL
extern unsigned int SYSCLK; // Clock do sistema em Hertz
extern unsigned int PCLK; // Clock dos perifericos, SYSCKL depois do HPRE, em Hertz

enum SERIAL_BUS_MODE {Master, Slave};

#endif