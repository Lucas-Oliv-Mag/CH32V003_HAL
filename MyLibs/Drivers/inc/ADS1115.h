#ifndef ADS1115_inc
#define ADS1115_inc


#define MAX_Positive_scale 0x7FFFU
#define MIN_Negative_scale 0x8000U

#define ADS1115_Addres 0x48U // Endereco do modulo qunado pino ADDR esta em GND.
#define REG_ADS1115_CONVERTION 0x00U    // endereco do registrador que armazena o valor da ultima conversao.
#define REG_ADS1115_CONFIGURATION 0x01U // Enderec do registrador de configuracao.
#define REG_ADS1115_THRESHOLD_LSB 0x02U // Armazena o valor MSB do registrador de 16 bits que aciona o comparador.
#define REG_ADS1115_THRESHOLD_MSB 0x03U // Aramzena o LSB do comparador.

// Bits do registrador de configura??o.
#define ADS1115_PGA        9 // Diz o ganho de amplifica??o das entradas
#define ADS1115_MODE       8
#define ADS1115_DATA_RATE  5
#define ADS1115_COMP_MODE  4
#define ADS1115_COMP_POL   3// Controla a polaridade do sinal de aviso do comparador, set = saida em high.
#define ADS1115_COMP_LATCH 2 // Quando setado, a sa¨ªda do comparador so ira para low quando o SMbus for limpado.
#define ADS1115_COMP_QUE   0

// SampleRate do ADC.
#define _8SPS   0b000
#define _16SPS  0b001
#define _32SPS  0b010
#define _64SPS  0b011
#define _128SPS 0b100 // Default
#define _250SPS 0b101
#define _475SPS 0b110
#define _860SPS 0b111






#endif 