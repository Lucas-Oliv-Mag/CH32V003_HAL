
/*
___________________________________________________________________________________________________________________________________

    CRIADO POR: LUCAS O.M  | Data: 21/10/2025   | Brasil - SP

    TiTULO: Lib para utilizar o m¨®dulo I2C o CH32V0003

    DESC: 

    - OBS: Tem dependencia direta a GPIOs.h.

___________________________________________________________________________________________________________________________________

*/


#ifndef I2C1_src
#define I2C1_src

#include <Peripherics/inc/I2C1.h>



#define START_CONDITION ((REG_I2C1_STAR1 >> I2C1_SB)   & 0x1U)
#define ADRESS_RESPOND  ((REG_I2C1_STAR1 >> I2C1_ADDR) & 0x1U)
#define BYTE_TRANSFERED ((REG_I2C1_STAR1 >> I2C1_BTF)  & 0x1U)
#define ACK_ERROR       ((REG_I2C1_STAR1 >> I2C1_AFO)  & 0x1U)
#define BYTE_RECEIVED   ((REG_I2C1_STAR1 >> I2C1_RxE)  & 0x1U)

#define CLEAR_ADDR() Timeout = REG_I2C1_STAR2 - REG_I2C1_STAR2;


// MSB First, LSB after.
/**
 * @brief Inicia o modulo I2C1,
 * 
 * @return unsigned int 
 */
unsigned int Init_I2C1_Master(){

    unsigned int tempreg;

    Peripheral_clock_enable(I2C1_Peripheral);
    Peripheral_reset(I2C1_Peripheral);

    // CONFIGURACAO DO CLOCK.
    // Obtem o clock em MHz 
    tempreg = PCLK/1000000; // Ortem MHz
    REG_I2C1_CTLR2 &= ~((unsigned int)0x3fU); // Limpa os bits de Frequencia
    REG_I2C1_CTLR2 |= (tempreg & 0x3fU);// Limpa os bits excedentes.

    tempreg = PCLK/200000;
    REG_I2C1_CKCFGR &= ~0xfff; // Limpa o valor de CCR.
    REG_I2C1_CKCFGR |= tempreg;// CKCFGR = CLock dos perifericos/( Velocidade desejada * 2)
    REG_I2C1_CKCFGR &= ~(1<<I2C1_FS); // Velocidade Standart

    REG_I2C1_CTLR1 |= (1<<I2C1_ACK) | (1<<I2C1_NOSTR);
    REG_I2C1_CTLR1 |= (1<<I2C1_PE);

    return 0;
}

void I2C1_IRQ_Enable(){
    REG_I2C1_CTLR2 |= (1<<I2C1_ITEVTEN) | (1<<I2C1_ITBUFEN);
    IRQ_enable(I2C1_EV_IRQ);
    IRQ_enable(I2C1_ER_IRQ);
}

void Stop_I2C1(){

        Peripheral_clock_stop(I2C1_Peripheral);
        Peripheral_reset(I2C1_Peripheral);
}

/**
 * @brief Escreve os chars contidos em Buffer para o dispositivo I2C mencionado em Adress
 * 
 * @param Adress 
 * @param Data 
 * @return Caso houver algum erro na trasmissao, retornara a messagem.
 */
I2C_msg_t Write_I2C1_polling(char Adress, char * Buffer, unsigned int Lenght){

   unsigned int Trash, Timeout = 0; // Serve para somente limpar as flags dos registradores, por meio da leitura 

   // CONDICAO DE START.
    REG_I2C1_CTLR1 |= (1<<I2C1_START); // Inicia trasmiss?o.

    do{
        __asm__("nop");
    }while( ((REG_I2C1_STAR1 >> I2C1_SB) & 0x01) != 1 );
    // ENVIO DO ENDERECO E ESPERA DO ACK DO SLAVE
    REG_I2C1_DATAR = (Adress<<1);

    do{

         Timeout++;
         if(Timeout > I2C1_TIMEOUT_LIMIT){
             REG_I2C1_CTLR1 |= (1<<I2C1_STOP); // Finaliza comunicacao
             return SLAVE_NON_ADRR;
         }

    }while( ((REG_I2C1_STAR1 >> I2C1_ADDR) & 0x01) != 1); // Espera o ACK ou NACK do Slave

    if( ((REG_I2C1_STAR1 >> I2C1_AFO) & 0x01 ) == 1) // Se houve erro de ACK
    {
        
        REG_I2C1_CTLR1 |= (1<<I2C1_STOP); // Finaliza comunicacao
        return SLAVE_NON_ADRR;

    }
    else
    {
        Timeout = 0;
    } // Slave n?o respondeu.

    Trash = REG_I2C1_STAR2;  // Limpa as flags.
    if(Trash){ __asm__("nop");}

        
    // ENVIO DOS BYTES DE DADOS.
    for(unsigned int i = 0; i < Lenght; i++){ // Enviara todos os bytes pela serial

        Timeout = 0;
        REG_I2C1_DATAR = Buffer[i];
    
        do{
         Timeout++;
         if(Timeout > I2C1_TIMEOUT_LIMIT)
         { 
            REG_I2C1_CTLR1 |= (1<<I2C1_STOP); // Finaliza comunicacao
            return BUS_ERROR;
         }
        }while( ((REG_I2C1_STAR1 >> I2C1_BTF) & 0x01 ) != 1);

        if( ((REG_I2C1_STAR1 >> I2C1_AFO) & 0x01 ) == 1){ 
            
            REG_I2C1_CTLR1 |= (1<<I2C1_STOP); // Finaliza comunicacao
            if(i == Lenght)
            {
            return SLAVE_DATA_REJECT;
            }
            else
            { 
            return SLAVE_NON_ACK;
            }

        }else
        {
            Timeout = 0;
        } // Slave n?o respondeu.

    }

    REG_I2C1_CTLR1 |= (1<<I2C1_STOP); // Finaliza comunicacao

    //REG_I2C1_CTLR1 |= I2C1_SWRST; Reset via software
    return NO_ERROR;
}

I2C_msg_t Read_I2C1(unsigned int Adress, unsigned int Read_Sequence[], unsigned int Lenght_of_buffer, unsigned int Output_buffer[], unsigned int Bytes_to_read){
   
    static unsigned int State = 0;
    static unsigned int Bytes;
    static unsigned int Lenght_W, Lenght_R;
    static unsigned int Timeout;


    switch (State) {
        
    case 0: // Ativar barramento i2c
        // Inicializa as variaveis.
        Timeout = 0U;
        Bytes   = 0U;
        Lenght_W  = Lenght_of_buffer;
        Lenght_R  = Bytes_to_read; 


        REG_I2C1_CTLR1 |= (1<<I2C1_START); // Inicia trasmiss?o.
        REG_I2C1_CTLR1 |= (1<<I2C1_ACK); // Permite o ACK do master.
        State++;

    break;

    case 1:// Enviar endereco do Slave
        if(START_CONDITION == 1)
        { // Caso SB j? foi setado
         REG_I2C1_DATAR = (Adress<<1); // Envia comando de escrita para apontar ao ponteiro.
         State++;
        }else{ Timeout++; }
    break;
    case 2: // Enviar o primeiro Byte.

        if(ADRESS_RESPOND == 1 ){// Espera o ACK ou NACK do Slave

             if(ACK_ERROR == 1){ // Caso der erro de ACK

                State = 0;
                REG_I2C1_CTLR1 |= (1<<I2C1_STOP);
                return SLAVE_NON_ADRR;// Slave nao respondeu.

            }else{
                 // Apenas para limpar a flag ADDR.
                CLEAR_ADDR();
                REG_I2C1_DATAR = Read_Sequence[0]; 
                Bytes++; 
                State++;
                Timeout = 0;
            }
        }else{ Timeout ++;}

    break;

    case 3:// Envia os outros Bytes
        if(BYTE_TRANSFERED == 1 ){

            if(ACK_ERROR == 1){ 

                State = 0;
                return SLAVE_NON_ACK;// Slave nao respondeu.

            }else{

               Timeout = 0;

               if(Bytes < Lenght_W){
                  REG_I2C1_DATAR = Read_Sequence[Bytes]; 
                  Bytes++;
            
              }else{
                  REG_I2C1_CTLR1 |= (1<<I2C1_START); // reinicia trasmissao.
                  State++;
                }
            }
        }else{ Timeout ++;}

    break;

    case 4: // RESTART agora para leitura

        if(START_CONDITION == 1)
        { // Caso SB j? foi setado
         REG_I2C1_DATAR |= ((Adress<<1) | 0x01U); // Envia comando de leituta para apontar ao ponteiro.
         State++;

           if(Lenght_R == 1) REG_I2C1_CTLR1 &= ~(1<<I2C1_ACK); // Desabilita o ack, pois o ?ltimo byte n?o tem.
             
        }else{ Timeout++; }


    break;
    case 5: // Ap?s o Slave confirmar o comando

        if(ADRESS_RESPOND == 1){
        CLEAR_ADDR();
        Bytes = 0;
        State++;
        Timeout = 0;
        }

    break;

    case 6:

     if (Lenght_R > 1 && Bytes == Lenght_R - 2)
    {
         REG_I2C1_CTLR1 &= ~(1<<I2C1_ACK); // Desabilita o ACK
    }

        if(BYTE_RECEIVED == 1){

                
            Output_buffer[Bytes] = REG_I2C1_DATAR;
            Bytes++;

            if(Bytes >= Lenght_R)
             {
                REG_I2C1_CTLR1 |= (1<<I2C1_STOP); // Finaliza comunicacao
                REG_I2C1_CTLR1 |= (1<<I2C1_ACK);
                State = 0;
                return NO_ERROR;
             }
        }else{

            Timeout++;
            
        }
        

    break;
    }

    if(Timeout > 100){
        State = 0;
        return SLAVE_NO_RESPOND;
    }

    return BUSY;
}




I2C_msg_t Write_I2C1(char Adress, char * Buffer, unsigned int Lenght_of_buffer){

    static unsigned int State = 0;
    static unsigned int Bytes;
    static unsigned int Lenght;
    static unsigned int Timeout;


    if(State == 0) {
        Timeout = 0U;
        Bytes   = 0U;
        Lenght  = Lenght_of_buffer;
    }

    switch (State) {
        
    case 0: // Ativar barramento i2c
        REG_I2C1_CTLR1 |= (1<<I2C1_START); // Inicia trasmiss?o.
        State++;

    break;

    case 1:// Enviar endereco do Slave
        if(((REG_I2C1_STAR1 >> I2C1_SB) & 0x01) == 1)
        { // Caso SB j? foi setado
         REG_I2C1_DATAR = (Adress<<1);
         State++;
        }else{ Timeout++; }
    break;
    case 2: // Enviar o primeiro Byte.

        if(((REG_I2C1_STAR1 >> I2C1_ADDR) & 0x01) == 1 ){// Espera o ACK ou NACK do Slave

             if( ((REG_I2C1_STAR1 >> I2C1_AFO) & 0x01 ) == 1){ // Caso der erro de ACK

                State = 0;
                return SLAVE_NON_ADRR;// Slave nao respondeu.

            }else{
                Timeout = REG_I2C1_STAR2 - REG_I2C1_STAR2; // Apenas para limpar a flag ADDR.

                REG_I2C1_DATAR = Buffer[0]; 
                Bytes++; State++;
                Timeout = 0;
            }
        }else{ Timeout ++;}

    break;

    case 3:// Envia os outros Bytes
        if(((REG_I2C1_STAR1 >> I2C1_BTF) & 0x01) == 1 ){


             if( ((REG_I2C1_STAR1 >> I2C1_AFO) & 0x01 ) == 1){ 

                State = 0;
                return SLAVE_NON_ACK;// Slave nao respondeu.

            }else{

               Timeout = 0;
               if(Bytes < Lenght){
                  REG_I2C1_DATAR = Buffer[Bytes]; 
                  Bytes++;
            
              }else{
                  State++;
                }
            }
        }else{ Timeout ++;}

    break;
    case 4: // Parar barramento
        REG_I2C1_CTLR1 |= (1<<I2C1_STOP); // Finaliza comunicacao
        State = 0;
        return NO_ERROR;
    break;
    }

    if(Timeout > 100){
        State = 0;
        return SLAVE_NO_RESPOND;
    }

    return BUSY;
}



#endif // Fim da lib.