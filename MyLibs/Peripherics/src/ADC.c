#ifndef ADC_src
#define ADC_src

#include <Core/Registers.h>
#include <Peripherics/inc/ADC.h>

//O registrador ADC_RSQRx seleciona os canais que ser?o convertidos para o Grupo de regras de convers?o, e ent?o armazena o valor da leitura sequencialmente, e ativa a flag de interrup??o.

int Init_ADC(unsigned char Channels, unsigned int Mode, unsigned int Trigger){


    REG_RCC_APB2PCENR   |= RCC_ADC_EN;     // liga o clock do ADC.
    REG_RCC_CFGR0 |=    (0x01100<<11);     // Preescaler para 1:8
    REG_ADC_CTRL2    |= AD_ON;         // Liga o modulo, para poder ser configurado.  
   // REG_ADC_CTRL2    &= ALGN_Right;   // Alinha os bits a direita, tendo o bit 0 no LSB do registrador (Como tudo deve ser ).
    
     REG_ADC_CTRL2 |= RCAL_bit; // Reinica a calibra??o
     do{ __asm__("nop"); }while(((REG_ADC_CTRL2 >> 3) & 0x01));
     
    
    REG_ADC_CTRL2 |= CAL_bit; // Inicia a calibra??o, depois tem que chechar se RSTCAL do registrador ADC_RDATAR foi a 0, indicando o fim da calibra??o.
    do{ __asm__("nop"); } while(((REG_ADC_CTRL2 >> 2) & 0x01));

    // MUDAR ESTA PARTE DEPOIS HEIN.

    REG_ADC_RSQR3 = 0x01; // Define o canal 1, como o primeiro a ser lido.

    return 1;
}



unsigned int ADC_Read(){


     REG_ADC_CTRL2 |= AD_ON;// Inicia a convers?o ADC

     do{

        __asm__("nop");

     }while( (REG_ADC_STATR & 0x02) != 0x02);

    return REG_ADC_RDATAR;
}


/*
Caracteristicas gerais do mÜ‡dulo ADC:

? semelhante ao empregado na familia STM8

Possui 10 bits de resolu??o, possui 8 canais externos e 2 internos.
O Clock do ADC n?o deve ultrapassar os 24MHz.

possui dois modos:

  RULE GROUP MODE: Neste modo, vocÄÇ define os canais de convers?o e a sequencia deles
  e quando iniciar a leitura, o ADC devolverÉÖ a convers?o de todos os canais no 
  registrador ADC_RDATAR, por sequencia, recomenda-se utilizar o DMA, para
  que os valores n?o sejam sobre-escritos.

  INJECTION  MODE: Neste modo, o ADC irÉÖ ler todos os canais de uma vez,
  e disponibilizar o resultado em registradores separados.

Tamb¹Èm ¹È possivel configurar o trigger do mÜ‡dulo para:

Single: Dispara o ADC 1 vez, com o ADON bit.
Single extern: Dispara o ADC 1 vez, se houver interrup??o externa.
Continuos: O Rulegroup se ativa sÜ‡zinho continuamente.


** Qualquer valor escolhido de sampletiming serÉÖ incrementado pela constante 12,5 Ciclos
** Formula para calcular o tempo de amostragem ¹È Tconv = Sampling time + 11 adc_clocktime

----------

FLUXOGRAMA PARA UTILIZAR O M?DULO ADC EM RULE GROUP MODE

-- Etapas de config --
0¡« - Ativar o clock para o mÜ‡dulo no RCC_APB2PCENR[ADC1EN] E apÜ‡s, o Prescaler do ADC no RCC_CFGR0[ADCPRE].
1¡« - Ligar o mÜ‡dulo com o ADC_CTRL2[ADON], pois se n?o estiver ligado, ele n?o retem as configura??es.
2¡« - Definir o alinhamento do resultado do registrador ADC_RDATAR, se ¹È de esquerda ou direita.
3¡« - Resetar a calibra?ao e iniciar uma nova calibra??o do mÜ‡dulo ADC. *N?o confundir o bit RESET CAL com o INIT CAL.
4¡« - Definir o modo do ADC, se ¹È rule group ou injection mode.
5¡« - Definir ordem dos canais ADCs, usando os registradores RSQRx.

-- Leitura

6¡« - Iniciar a leitura, setando novamente o ADON_bit
7¡« - Esperar a flag de fim de convers?o ser setada
8¡« - Ler o resultado do registrador ADC_RDATAR
9¡« - Resetar todas as flags envolvidas.
*/













































#endif