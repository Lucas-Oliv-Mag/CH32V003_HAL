# CH32V003_HAL
   Biblioteca para abstração de hardware própria, otimizada para ser simples e eficiente, evitando as padronizações e sobrecargas da HAL Oficial da WCH, muito inspirada na HAL dos MCUs STM32.
Assim abstraindo complexidades, diminuindo a curva de aprendizado de MCUs de 32Bits para quem está vindo dos MCUs de 8bits.

- Está em desenvolvimento desde 22092025.

 Atualmente comporta os seguintes periféricos

- Systick     (100%)
- USART1      (70%)
- I2C1        (2%)
- ADC         (5%)
- GPIOs       (100%)
- RCC         (100%)

Também incluem bibliotecas para fazer interface com dispositivos externos como

- Display LCD - HD44780
- ShiftRegister - 74HC595
  
A documentação está em português por enquanto, posteriormente será refeita em inglês.