#define CMD    0
#define DATA   1

#define _row1  0x00
#define _row2  0x40   // Endere?o inicial do primeiro caracter da segunda linha do display (Caso tenha 2 linhas)


#define DDRAM_limit_2lines 0x67 // Define o ultimo endere?o de DDRAM que o LCD de 2 linhas suporta conporta
#define DDRAM_limit_1lines 0x4F // Ultimo endere?o em um display de 1 linha



#define Empyt 0
// MSB dos registradores alvos
#define Clear_Cmd    (1<<0)
#define Return_home  (1<<1)
#define Entry_mode   (1<<2)
#define Disp_ctrl    (1<<3)
#define Def_shift    (1<<4)
#define Fx_set       (1<<5)
#define GCRAM_set    (1<<6)
#define AC_set       (1<<7) // 0x80h  128dec 


//---- Bits do Fx_set (Function_set)-----
// 1бу a ser declarado
#define _8bit_bus   1
#define _4bit_bus   0
// 2бу a ser declarado
#define _2Lines     1
#define _1Line      0
// 3бу a ser declarado
#define Font_5x8    0
#define Font_10x8   1

// ---- Bits do Entry mode----
// 1бу a ser declarado
#define Flw_right   0
#define Flw_left    1
// 2бу a ser declarado
#define Increment   1
#define Decrement   0

// ----Bits do Disp_Ctrl------
// 1бу a ser declarado
#define LCD_On      1
#define LCD_Off     0
// 2бу a ser declarado
#define Cursor_off  0
#define Cursor_on   1
// 3бу a ser declarado
#define Chr_blink   1
#define Chr_off     0

// ---- Bits do Def_shfit -----
// 1бу bit
#define Cursor_shift  0 // Escolhe o Cursor para ser movido (AC иж incrementado)
#define Display_shift 1 // Escolhe o Display para ser movido
// 2бу bit
#define Shift_left    0 // Move para a esquerda
#define Shift_right   1 // Move para a direita
// ----------------------------



struct HD4478{

    int RS, EN; //Define o pino/bit
    int DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7; // Define o bit/pino
    GPIO_t RS_Port, EN_Port,DATA_PORT;
    char Function_set_reg, Display_Control_reg, Shifter_reg, Entry_mode_reg; // Armazena ass configuracoes atuais.

} LCD;




void LCD_Write_4b(int Type, char Data){ // Envia fun??es de comando e dados.

  char aux;

 // Write_74HC595(0 | (1<< LCD.EN)); // Zera o barramento, incluindo o pino de enable.

// -------- ENVIA O MSB -----------//
    aux = Data >> 4;  // Limpa Data e envia o MSB primeiro.
    aux |= (Type<<LCD.RS); // Seleciona o registrador certo

    Write_74HC595(aux | (1 << LCD.EN)); // Escreve no shiftreg o MSB
    Write_74HC595(aux & ~(1 << LCD.EN)); //Atualizar o clock
    Delay_Ms(1);


// -------- ENVIA O LSB -----------//

    aux = Data & 0x0F; // Limpa Data para enviar o LSB
    aux |= (Type<<LCD.RS); // Seleciona o registrador certo

    Write_74HC595(aux | (1<< LCD.EN));
    Write_74HC595(aux & ~(1 << LCD.EN)); // Reinicia o clock
    Delay_Ms(1);
}


void Init_LCD_4b(){

   int i;

   for(i=0;i< 3; i++){  
    Write_74HC595(0x03); 
    Delay_Us(50);} 

    Write_74HC595(0x02 | (1 << LCD.EN));
    Delay_Ms(1);
    Write_74HC595(0x02 & ~(1 << LCD.EN));
    Delay_Ms(1);

    LCD_Write_4b(CMD,0x28); // Modo de 4 bits
    LCD_Write_4b(CMD,0x0C); // Modo de 4 bits
    LCD_Write_4b(CMD,0x01); // Modo de 4 bits
    Delay_Ms(2);
    LCD_Write_4b(CMD,0x06); // Modo de 4 bits
    Delay_Ms(1);
    LCD_Write_4b(DATA,'A'); // Modo de 4 bits

}



void LCD_Write_8b(int Type, char Data){

 Write_Pin(LCD.RS_Port,LCD.RS,Type);
 Write_Pin(LCD.EN_Port,LCD.EN,HIGH);
 Write_74HC595(Data);
 Delay_Us(5);
 Write_Pin(LCD.EN_Port,LCD.EN,LOW);

}



void LCD_New_Config(unsigned char Register, unsigned char config1,unsigned char config2, unsigned char config3){

    unsigned char Aux = 0;
    switch (Register) {

    case Entry_mode:Aux = Entry_mode| (config1 << 1) | config2;  LCD.Entry_mode_reg = Aux;                          break;
    case Disp_ctrl: Aux = Disp_ctrl | (config1 << 2) | (config2 << 1) | config3;  LCD.Display_Control_reg   = Aux;  break;
    case Def_shift: Aux = Def_shift | (config1 << 3) | (config2 <<2);   LCD.Shifter_reg = Aux;                      break;
    case Fx_set:    Aux = Fx_set    | (config1 << 4) | (config2 <<3) | (config3 <<2);  LCD.Function_set_reg = Aux;  break;
    case GCRAM_set: Aux = GCRAM_set | config1;                                                                      break;
    case AC_set:    Aux = AC_set    | config1;                                                                      break;
    }
    LCD_Write_8b(CMD,Aux);      
    Delay_Us(5);                                                              
}



void LCD_Custom_Init_8b(){

    LCD_Write_8b(CMD,LCD.Function_set_reg); // Apиоs enviar, estив a??o n?o pode ser desfeita sem reiniciar.
    Delay_Us(5);
    LCD_Write_8b(CMD,LCD.Shifter_reg);
    Delay_Us(5);
    LCD_Write_8b(CMD,LCD.Entry_mode_reg);
    Delay_Us(5);
    LCD_Write_8b(CMD,LCD.Display_Control_reg);// Clear display
    Delay_Us(5);

    LCD_Write_8b(CMD,Clear_Cmd);
    Delay_Ms(4);

}

void LCD_Init_8b(){

    LCD_Write_8b(CMD,0x38); LCD.Function_set_reg = 0x38;    // 2 linhas, 8 bits, 5 x 8 dots
    Delay_Us(5);
    LCD_Write_8b(CMD,0x0C); LCD.Display_Control_reg = 0x0C; // display ligado, cursor off, blink off
    Delay_Us(5);
    LCD_Write_8b(CMD,0x06); LCD.Entry_mode_reg = 0x06;     // incremento normal do AC (cursor anda para a direita, sem shift do display)
    Delay_Us(5);
    LCD_Write_8b(CMD,Clear_Cmd);// Clear display
    Delay_Ms(3);

}


void Print_LCD(unsigned char Row,unsigned char dot, char *String){
    
    unsigned int i;
    unsigned int Lenght;
    Lenght = String_counter(String); // Conta quantos chars tem em String

    // Irив definir o AC para o posi??o certa.
    if((LCD.Function_set_reg >> 3) & 0x01){ // Caso estejamos trabalhando com display de 2 linhas
        
        if(Row == 1 || Row == 0){
            LCD_New_Config(AC_set,dot,Empyt,Empyt);
            } 
        else if(Row == 2){  
             LCD_New_Config(AC_set,dot + _row2,Empyt,Empyt);
             }   
         //LCD_New_Config(AC_set,dot + _row2,Empyt,Empyt);}    // Define o AC para a posi??o, com o offset para a segunda linha             
    }else{ // Caso o display apenas tiver 1 linha.
        LCD_New_Config(AC_set,dot,Empyt,Empyt);
    }

    for(i = 0; i < Lenght ; i++){
        LCD_Write_8b(DATA,String[i]);
        Delay_Us(5);
    }

}