#ifndef REGISTERS_INC
#define REGISTERS_INC

// ______ RCC REGISTRADORES __________________________//
#define REG_RCC_CTLR        (*(volatile unsigned int*)0x40021000) //Clock control register                 - Reset value: 0x0000xx83
#define REG_RCC_CFGR0       (*(volatile unsigned int*)0x40021004) //Clock configuration register 0         - Reset value: 0x00000020
#define REG_RCC_INTR        (*(volatile unsigned int*)0x40021008) //Clock interrupt register               - Reset value: 0x00000000
#define REG_RCC_APB2PRSTR   (*(volatile unsigned int*)0x4002100C) //PB2 peripheral reset register          - Reset value: 0x00000000
#define REG_RCC_APB1PRSTR   (*(volatile unsigned int*)0x40021010) //PB1 peripheral reset register          - Reset value: 0x00000000
#define REG_RCC_AHBPCENR    (*(volatile unsigned int*)0x40021014)//HB peripheral clock enable register     - Reset value: 0x00000004
#define REG_RCC_APB2PCENR   (*(volatile unsigned int*)0x40021018) //PB2 peripheral clock enable register   - Reset value: 0x00000000
#define REG_RCC_APB1PCENR   (*(volatile unsigned int*)0x4002101C) //PB1 peripheral clock enable register   - Reset value: 0x00000000
#define REG_RCC_RSTSCKR     (*(volatile unsigned int*)0x40021024)// Control/status register                - Reset value: 0x0C000000
//_____________PFIC REGISTERS ______________________________//

#define PFIC_BASE 0xE000E000

#define REG_PFIC_ISR1      (*(volatile unsigned int*)(PFIC_BASE + 0x00)) //PFIC interrupt enable status register 1 0x0000000C
#define REG_RPFIC_ISR2     (*(volatile unsigned int*)(PFIC_BASE + 0x04)) //PFIC interrupt enable status register 2 0x00000000
#define REG_PFIC_IPR1      (*(volatile unsigned int*)(PFIC_BASE + 0x20)) //PFIC interrupt pending status register 1 0x00000000
#define REG_PFIC_IPR2      (*(volatile unsigned int*)(PFIC_BASE + 0x24)) //PFIC interrupt pending status register 2 0x00000000
#define REG_PFIC_ITHRESDR  (*(volatile unsigned int*)(PFIC_BASE + 0x40))//PFIC interrupt priority threshold configuration register 0x00000000
#define REG_PFIC_CFGR      (*(volatile unsigned int*)(PFIC_BASE + 0x48)) //PFIC interrupt configuration register 0x00000000
#define REG_PFIC_GISR      (*(volatile unsigned int*)(PFIC_BASE + 0x4C)) //PFIC interrupt global status register 0x00000000
#define REG_PFIC_VTFIDR    (*(volatile unsigned int*)(PFIC_BASE + 0x50)) //PFIC VTF interrupt ID configuration register 0x00000000
#define REG_PFIC_VTFADDRR0 (*(volatile unsigned int*)(PFIC_BASE + 0x60)) // PFIC VTF interrupt 0 offset address register 0x00000000
#define REG_PFIC_VTFADDRR1 (*(volatile unsigned int*)(PFIC_BASE + 0x64)) //PFIC VTF interrupt 1 offset address register 0x00000000
#define REG_PFIC_IENR1     (*(volatile unsigned int*)(PFIC_BASE + 0x100)) //PFIC interrupt enable setting register 1 0x00000000
#define REG_PFIC_IENR2     (*(volatile unsigned int*)(PFIC_BASE + 0x104)) //PFIC interrupt enable setting register 2 0x00000000
#define REG_PFIC_IRER1     (*(volatile unsigned int*)(PFIC_BASE + 0x180)) //PFIC interrupt enable clear register 1 0x00000000
#define REG_PFIC_IRER2     (*(volatile unsigned int*)(PFIC_BASE + 0x184)) //PFIC interrupt enable clear register 2 0x00000000
#define REG_PFIC_IPSR1     (*(volatile unsigned int*)(PFIC_BASE + 0x200)) //PFIC interrupt pending setting register 1 0x00000000
#define REG_PFIC_IPSR2     (*(volatile unsigned int*)(PFIC_BASE + 0x204)) //PFIC interrupt pending setting register 2 0x00000000
#define REG_PFIC_IPRR1     (*(volatile unsigned int*)(PFIC_BASE + 0x280)) //PFIC interrupt pending clear register 1 0x00000000
#define REG_PFIC_IPRR2     (*(volatile unsigned int*)(PFIC_BASE + 0x284)) //PFIC interrupt pending clear register 2 0x00000000
#define REG_PFIC_IACTR1    (*(volatile unsigned int*)(PFIC_BASE + 0x300)) //PFIC interrupt activation status register 
#define REG_PFIC_IACTR2    (*(volatile unsigned int*)(PFIC_BASE + 0x304)) //PFIC interrupt activation status register 
#define PFIC_IPRIORx_BASE  ( (volatile unsigned int*)(PFIC_BASE + 0x400)) //PFIC interrupt priority configuration register 0x00000000
#define PFIC_IPRIORx_TOP   (*(volatile unsigned int*)(PFIC_BASE + 0x4FF))
#define REG_PFIC_SCTLR     (*(volatile unsigned int*)(PFIC_BASE + 0xD10)) //PFIC system control register 0x00000000
// _____________________________________________________//


//_______________ SYSTICK Timer Registradores  ________//
#define REG_STK_CTRL  (*(volatile unsigned int*)0xE000F000)          // Configura??o do Systick.
#define REG_STK_SR    (*(volatile const unsigned int*)0xE000F004) // Somente leitura do status discreto da contagem.
#define REG_STK_CNTL  (*(volatile unsigned int*)0xE000F008)       // Valor atual do registrador de contagem.
#define REG_STK_CMPLR (*(volatile unsigned int*)0xE000F010)      // Valor de setpoint para estouro do systick.
// _____________________________________________________//

// _________ Registradores do EXTI _____________________//
#define REG_EXTI_INTENR (*(volatile unsigned int *)0x40010400) //Interrupt enable register 0x00000000
#define REG_EXTI_EVENR  (*(volatile unsigned int *)0x40010404) //Event enable register 0x00000000
#define REG_EXTI_RTENR  (*(volatile unsigned int *)0x40010408) //Rising edge trigger enable register 0x00000000
#define REG_EXTI_FTENR  (*(volatile unsigned int *)0x4001040C) //Falling edge trigger enable register 0x00000000
#define REG_EXTI_SWIEVR (*(volatile unsigned int *)0x40010410) //Soft interrupt event register 0x00000000
#define REG_EXTI_INTFR  (*(volatile unsigned int *)0x40010414) //Interrupt flag register 0x0000XXXX


// ___________ TIM2 REGISTRADORES _____________________//
#define _TIM2_BASE 0x40000000

// Registradores de configuracao
#define REG_TIM2_CTRL1      *((volatile unsigned int*)(_TIM2_BASE + 0x00)) // Configuracoes gerais 1
#define REG_TIM2_CTRL2      *((volatile unsigned int*)(_TIM2_BASE + 0x04)) // Configuracoes gerais 2
#define REG_TIM2_SMCFGR     *((volatile unsigned int*)(_TIM2_BASE + 0x08))
#define REG_TIM2_DMAINTENR  *((volatile unsigned int*)(_TIM2_BASE + 0x0C)) // Configura o DMA
#define REG_TIM2_PSC        *((volatile unsigned int*)(_TIM2_BASE + 0x28)) // Registrador de prescaler que divide o clock para o perif§Ú§Ørico.
//Registradores funcionais
#define REG_TIM2_INTFR      *((volatile unsigned int*)(_TIM2_BASE + 0x10)) // Exibe as interrupcoes.
#define REG_TIM2_CNT        *((volatile unsigned int*)(_TIM2_BASE + 0x24)) // Registrador de contagem.
#define REG_TIM2_SWEVGR     *((volatile unsigned int*)(_TIM2_BASE + 0x24)) // Registrador de geracao de eventos.
#define REG_TIM2_ATRLR      *((volatile unsigned int*)(_TIM2_BASE + 0x2C)) // Registrador de Auto Reload, define o teto maximo de contagem.

// __________ USART1 REGISTERS ____________________//

#define REG_USART_STATR (*(volatile unsigned int*)0x40013800) // Registrador das flags
#define REG_USART_DATAR (*(volatile unsigned int*)0x40013804) // Registrador do valor
#define REG_USART_BRR   (*(volatile unsigned int*)0x40013808) // Registrador do baud rate
#define REG_USART_CTRL1 (*(volatile unsigned int*)0x4001380C) // Registrador de controle 1
#define REG_USART_CTRL2 (*(volatile unsigned int*)0x40013810) // Registrador de controle 2
#define REG_USART_CTRL3 (*(volatile unsigned int*)0x40013814) // Registrador de controle 3
#define REG_USART_GPR   (*(volatile unsigned int*)0x40013818) // Registrador do prescaler e fusebits

//____________________________________________________//

//_______________ I2C1 REGISTERS ____________________//
#define REG_I2C1_CTLR1   (*(volatile unsigned int*)0x40005400)  // I2C control register 1 0x0000
#define REG_I2C1_CTLR2   (*(volatile unsigned int*)0x40005404) //I2C control register 2 0x0000
#define REG_I2C1_OADDR1  (*(volatile unsigned int*)0x40005408) //I2C address register 1 0x0000
#define REG_I2C1_OADDR2  (*(volatile unsigned int*)0x4000540C) //I2C address register 2 0x0000
#define REG_I2C1_DATAR   (*(volatile unsigned int*)0x40005410)  //I2C data register 0x0000
#define REG_I2C1_STAR1   (*(volatile unsigned int*)0x40005414)  //I2C status register 1 0x0000
#define REG_I2C1_STAR2   (*(volatile unsigned int*)0x40005418)  //I2C status register 2 0x0000
#define REG_I2C1_CKCFGR  (*(volatile unsigned int*)0x4000541C) //I2C clock register 0x0000

// __________________________________________________//

// ______________ GPIO REGISTERS ______________________________//
/*
A manipulacao feita pela biblioteca das GPIOs precisa que seja definido
somente o endereco de hardware da biblioteca, para ser utilizado em conjunto
com os offsets, por favor nao alterar.
*/
#define REG_GPIO_PORTA 0x40010800U
#define REG_GPIO_PORTC 0x40011000U
#define REG_GPIO_PORTD 0x40011400U
// ___________ Offset  dos Registradores de configuracao ______//
#define _INDR   0x08U
#define _OUTDR  0x0CU
#define _BSRH   0x10U
#define _BCR    0x14U
#define _LCKR   0x18U
// ______________ AFIO REGISTERS ______________________________//

#define REG_AFIO_PCFR1  (*(volatile unsigned int*)0x40010004) // Registrador de reapeamento
#define REG_AFIO_EXTICR (*(volatile unsigned int*)0x40010008) // Registrador das interrupcoes externas.


// ___________________________________________________________//


// __________________ ADC REGISTERS _________________________//
#define REG_ADC_CTRL1  (*(volatile unsigned int*)0x40012404) // Define o endere?o de memoria do registrador ADC_CTRL1
#define REG_ADC_CTRL2  (*(volatile unsigned int*)0x40012408) // Define o endere?o de memoria do registrador ADC_CTRL2
#define REG_ADC_RDATAR (*(volatile unsigned int*)0x4001244C) // Define o endere?o de memoria do registrador de resultado do Rule group
#define REG_ADC_RSQR3  (*(volatile unsigned int*)0x40012434) // 
#define REG_ADC_STATR  (*(volatile unsigned int*)0x40012400) // 




#endif