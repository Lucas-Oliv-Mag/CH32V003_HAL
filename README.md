# CH32V003_HAL
   Biblioteca para abstração de hardware própria, otimizada para ser simples e eficiente, evitando as padronizações e sobrecargas da HAL Oficial da WCH, muito inspirada na HAL dos MCUs STM32.
Assim abstraindo complexidades, diminuindo a curva de aprendizado de MCUs de 32Bits para quem está vindo dos MCUs de 8bits.

- Está em desenvolvimento desde 22/09/2025.

 Atualmente comporta os seguintes periféricos:

- Systick     (10%)
- USART1      (70%)
- I2C1        (100%)
- ADC         (5%)
- GPIOs       (100%)
- RCC         (100%)
- PFIC        (100%)
- EXTI        (100%)
- TIM2        (50%)

Também incluem bibliotecas para fazer interface com dispositivos externos como:

- Display LCD - HD44780 (100%)
- ShiftRegister - 74HC595 (100%)
- ADC I2C 16 bits - ADS1115 (100)%
  
A documentação está em português por enquanto, posteriormente será refeita em inglês.
