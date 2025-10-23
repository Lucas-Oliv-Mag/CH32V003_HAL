#ifndef HAL_MASTER_HEADER
#define HAL_MASTER_HEADER

#include "ch32v00x.h" // POR ENQUANTO, FUTURAMENTE N?O SER? NESCESSARIA.

#include <Core/Registers.h> // Define todos os registradores de hardware da biblioteca.
#include <Core/Lib_config.h> // Variaveis globais.

#include <Utilitys/Utilitys.h> // Fun??es auxiliares de manipula??o de dados.

// --- Perifericos basicos --- //
#include <Peripherics/inc/RCC.h>
#include <Peripherics/inc/GPIOs.h>

// --- Perifericos gerais --- //
#include <Peripherics/inc/USART1.h>
#include <Peripherics/inc/I2C1.h>
#include <Peripherics/inc/Systick.h>
#include <Peripherics/inc/TIM2.h>
#include <Peripherics/inc/ADC.h>

// --- Drivers para dispositivos externos --- //

#include <Drivers/Drivers.h>




#endif // Fim da lib HAL_MASTER_HEADER