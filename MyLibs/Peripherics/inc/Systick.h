
/*
___________________________________________________________________________________________________________________________________

    CRIADO POR: LUCAS O.M  | Data: 03/10/2025   | Brasil - SP

    T?TULO: Lib para utilizar o Systick do CH32V003.

    DESC: Utilize as fun??es para manusear o systick timer, para gerar interrup??es, N?o h¨¢ nescessidade de configurar nada ¨¢ mais, 
    por¨¦m dever¨¢ criar a ISR para o Systick.

    - Normalmente utiliza-se para gerar interrup??es ciclicamentes, no periodo passado em Systick_init().

    - ? possivel utilizar est¨¢ lib para disparar uma unica vez a interrup??o programada, basta usar Systick_init(), e ap¨®s, na sua 
     ISR, utilizar o Systick_stop().


___________________________________________________________________________________________________________________________________

*/

#ifndef SYSTICK_inc
#define SYSTICK_inc



// Bits do STK_CTRL - Registrador de configura??o.

#define SWIE  31    // Habilita a interrup??o via software do bit.
#define STRE  3     // Auto-Reload do timer (Ativa o modo ciclico).
#define STCKL 2     // Fonte do clock do Systimer. (1:1 ou 1:8).
#define STIE  1     // Habilita a interrupca do contador.
#define STE   0     // Bit que habilita o Systick.

// Bits do STK_SR - Registrador de status da contagem.

#define CNTIF 0     // Indica se houve ou n?o o estouro d systick.

typedef enum Time_Unit{ns = 0, us = 1, ms = 1000, s = 1000000} Time_t; 


extern unsigned int SYSCLK, PCLK;

unsigned int init_Systick(unsigned int Period, Time_t Unit); // Inicializa o Systick Ciclicamente.


void Systick_stop(); // Interrompe o systick.


#endif // Fim da lib