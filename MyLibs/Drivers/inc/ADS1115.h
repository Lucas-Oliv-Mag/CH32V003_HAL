#ifndef ADS1115_inc
#define ADS1115_inc


#include <Peripherics/inc/I2C1.h>

#define MAX_Positive_scale 0x7FFFU
#define MIN_Negative_scale 0x8000U

#define ADS1115_Addres 0x48U // Endereco do modulo qunado pino ADDR esta em GND.

#define REG_ADS1115_CONVERTION 0x00U    // endereco do registrador que armazena o valor da ultima conversao.
#define REG_ADS1115_CONFIGURATION 0x01U // Enderec do registrador de configuracao.
#define REG_ADS1115_THRESHOLD_LSB 0x02U // Armazena o valor MSB do registrador de 16 bits que aciona o comparador.
#define REG_ADS1115_THRESHOLD_MSB 0x03U // Aramzena o LSB do comparador.

// Bits do registrador de configuracao.
#define ADS1115_OS         15 
#define ADS1115_MUX        12
#define ADS1115_PGA        9 // Diz o ganho de amplificao das entradas
#define ADS1115_MODE       8 // Define se eh modo single shoot(1) ou modo conversao continua (0)
#define ADS1115_DATA_RATE  5 // Inicio dos 3 bits que Define a taxa de sample 8 ~ 860 samples por segundo.
#define ADS1115_COMP_MODE  4 // Define o modo do comparador, se eh modo janela, ou modo tradicional com histerese
#define ADS1115_COMP_POL   3// Controla a polaridade do sinal de aviso do comparador, set = saida em high.
#define ADS1115_COMP_LATCH 2 // Quando setado, a saida do comparador so ira para low quando o SMbus for limpado.
#define ADS1115_COMP_QUE   0 // 2 bits que definem quantas vezes as conversoes tem ativar para ativar a saida ALERT, ou desativar o comparador em '11'

#define ADS_1115_START_CONVERSION (1<<15)

typedef enum ADS1115_SAMPLERATE{ // Taxa de amostras por segundo.
    _8SPS  = 0b000,
    _16SPS = 0b001,
    _32SPS = 0b010,
    _64SPS = 0b011,
    _128SPS= 0b100, // Default
    _250SPS= 0b101,
    _475SPS=0b110,
    _860SPS=0b111,
} ADS1115_SPS_t;

typedef enum ADS1115_PGA_{     //Ganho do PGA
    X0 = 0x0U, // ?6.144ÿVmax	?187.5ÿ?V
    X1 = 0x1U, // ?4.096ÿVmax	?125.0ÿ?V
    X2 = 0x2U,//  ?2.048 Vmax   ?62.50 ?V
    X4 = 0x3U,//  ?1.024ÿVmax	?31.25ÿ?V
    X8 = 0x4U,//  ?0.512ÿVmax 	?15.625ÿ?V
    X16 =0x5U//   ?0.256ÿVmax 	?7.8125ÿ?V
} ADS1115_PGA_t;


typedef enum ADS115_MODES_{
    Single_Shot,
    Continuos_mode,
    Windows_Comparator,
    Hysteresi_Comparator, // O comparador aciona
     }ADS1115_mode_t;
typedef enum ADS1115_CHANNELs{

  // Modo referencia a GND
    AIN0 = 0b100, // Entrada de sinal AIN0, referencia a GND
    AIN1 = 0b101, // Entrada de sinal AIN1, referencia a GND
    AIN2 = 0b110, // Entrada de sinal AIN2, referencia a GND
    AIN3 = 0b111, // Entrada de sinal AIN3, referencia a GND

    // Modo diferencial
    AIN0_1 = 0b000, // Entrada de sinal AIN0, referencia a AIN1
    AIN0_3 = 0b001, // Entrada de sinal AIN0, referencia a AIN3
    AIN1_3 = 0b010, // Entrada de sinal AIN1, referencia a AIN3
    AIN2_3 = 0b011  // Entrada de sinal AIN2, referencia a AIN3
    }ADS1115_pins_t;


typedef struct ADS1115_setup{
    unsigned int Adress;// Armazena o valor do ADC

    ADS1115_PGA_t  Programable_gain; // Armazena o ganho do PGA.
    ADS1115_SPS_t  Sample_rate; // Armazena o sample rate.
    ADS1115_pins_t  Actual_Channel; // Armazena o canal atual.
    ADS1115_mode_t Actual_Mode;    // Armazena o modo atual.

    unsigned int COMP_POLARITY;

    unsigned int Config; // Atual configuracao
}ADS1115_t;


I2C_msg_t Config_ADS115(ADS1115_t * ADC, unsigned int* Buffer_out);







#endif 


