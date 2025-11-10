#ifndef I2C1_inc
#define I2C1_inc

#include <Core/Registers.h>
#include <Core/Lib_config.h>
#include <Peripherics/inc/GPIOs.h>
#include <Utilitys/inc/String.h>

/*
___________________________________________________________________________________________________________________________________

    CRIADO POR: LUCAS O.M  | Data: 21/10/2025   | Brasil - SP

    TiTULO: Lib para utilizar o m§Ú§àdulo I2C o CH32V0003

    DESC: 

    - OBS: Tem dependencia direta a GPIOs.h.

___________________________________________________________________________________________________________________________________

*/


// Bits do CTRL1


#define I2C1_FS 15 // Seleciona velocidade standard 100Khz (0x00), ou Fast 400Khz (0x01)

#define I2C1_SWRST 15 // Quando habilitado, dara um reset via software no modulo I2C.
#define I2C1_PEC 14 // Determina quando setado se tera ou nao o CRC Opicional do SMbus.
#define I2C1_POS
#define I2C1_ACK 10 // Determina se o master respondera com um ACK ao fim do recebimento.
#define I2C1_STOP 9 // Gera uma condicao de parada
#define I2C1_START 8 // Gera uma condicao de inicio
#define I2C1_NOSTR 7 // Determina se o clock sera paralizado se BTF ou ADDR nao forem limpos.
#define I2C1_ENGC 6  // Determina se o modulo I2C respondera a uma chamada de broadcast.
#define I2C1_ENPEC 5 // Habilita o PEC, que se trata de um CRC opicional para o protocolo I2C SMbus.
#define I2C1_PE 0 // Habilita o periferico quando setado.


// Bits do CTRL 2

#define I2C1_LAST     12 //
#define I2C1_DMAEN    11 // Habilita DMA para o modulo I2C1
#define I2C1_ITBUFEN  10 // Habilita interrupcao pelos evento de buffer (Tx e Rx)
#define I2C1_ITEVTEN   9 // Habilita interrupcao pelos eventos I2C
#define I2C1_ITERREN   8 // Habilita interrupcao pelos erros I2C
#define I2C1_FREQ  0

// bits do STATUS 1
#define IC21_PECER 12 // Caso houver erro de PEC na recepcao de dados
#define I2C1_OVR   11 // Caso houver erro de overun e underun
#define I2C1_AFO   10 // Caso houver erro de Acknowledge.
#define I2C1_ARLO   9 // Caso houver erro por perde de arbitro.
#define I2C1_BERR   8 // Caso houver erro no Start ou Stop condition
#define I2C1_TxE    7  // Registrador de transmissao esta vazio
#define I2C1_RxE    6 // Registrador de recebimento nao esta vazio
#define I2C1_STPF   4 // Slave enviou uma condi??o de stop
#define I2C1_BTF    2 // Transferencia de byte completa
#define I2C1_ADDR   1 // Slave respondeu a chamada de endereco
#define I2C1_SB     0 // evento de Start condition 


// Bits do STATUS 2

#define I2C1_PEC_value  8 // Armazena o valor de CRC do I2C SMbus
#define I2C1_DUALF  7 // Dual flag dos enderecos OWN 1 & OWN 2
#define I2C1_GENCAL 4 // Indica uma chamada de broadcast
#define I2C1_TRA    2 // Trasmitter/receiver bit
#define I2C1_BUSY   1 // Indica se esta havendo comunicao I2C
#define I2C1_MSL    0 // Indica se esta como master ou slave





extern unsigned int PCLK;
extern unsigned int SYSCLK;

typedef enum SERIAL_BUS_MODE I2C_t;

typedef enum I2C_MSG {
    NO_ERROR, // Mensagem enviada com sucesso
    SLAVE_NON_ACK, // Dispositivo slave nao confirmou a mensagem (No acknowledge)
    SLAVE_NON_ADRR,// Dispositivo slave nao respondeu a chama de endereco (No Acknowledge)
    SLAVE_DATA_REJECT, // O slave rejeitou os dados (No acknowLedge)
    SLAVE_NO_RESPOND,  // O dispositivo slave demorou demais para responder.
    BUSY // O Barramento ainda esta ocupado.
} I2C_msg_t;

unsigned int Init_I2C1_Master();

void Stop_I2C1();

char Read_I2C1(unsigned int Adress, unsigned int reg);

I2C_msg_t Write_I2C1_polling(char Adress, char * Buffer);

I2C_msg_t Write_I2C1(char Adress, char * Buffer, unsigned int Lenght_of_buffer);


// MSB First, LSB after.



#endif // Fim da lib.
