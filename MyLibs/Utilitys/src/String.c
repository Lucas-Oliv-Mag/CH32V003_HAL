#ifndef STRING_SRC
#define STRING_SRC


#include <Utilitys/inc/String.h>

/**
 * @brief Conta a quantidade de caracteres validos em uma string.
 * 
 * @param Str Indique a string ao qual deve ser contada
 * @return unsigned int quantidade de caracteres (ignora o terminador \0).
 */
unsigned int String_counter(char *Str){

    char *P = Str;

    while(*P != '\0'){
     P++;
    }

    return P - Str;
}




/**
 * @brief Est? fun??o cria uma barra gr?fica de pontos,toda vez que chamada, 
 * 
 * @return char* em ASCII dos dots
 */
char* Dots(){

    static unsigned int dots_count    = 0;

    static char dots[3] ={' ',' ',' '};
    char *Pointer;


    if(dots_count < 3){
    
        dots[dots_count] = '.';
        dots_count ++;
    }else{  
         dots[0] = ' ';
         dots[1] = ' ';
         dots[2] = ' ';
         dots_count = 0;
    }

    Pointer = &dots[0];

    return Pointer;
}



/**
 * @brief Limpar uma string, ou seja, escreve " " em todos os seus caracteres.
 * 
 * @param String 
 */
void String_clear(char* String){

    unsigned int lenght;
    lenght = String_counter(String);

    for(unsigned int i = 0; i < lenght; i ++){

        *(String + i) = ' ';

    }

    *(String + lenght) = '\0';

}




/**
 * @brief Esta funcao escreve a string no array de chars indicado.
 * 
 * @param Container Array de caracteres
 * @param String   String ao qual deseja imprimir no Array
 */
void String_set(char* Container, char* String){

    unsigned int Lenght = String_counter(String);

    String_clear(Container);

    for(unsigned int i = 0; i < Lenght ; i++){

       *(Container+i) = *(String+i);
    
    }

}


/**
 * @brief Limpa todos os valores de um buffer com o valor 0x00.
 * 
 * @param Buffer O Buffer de chars que deseja limpar.
 * @return int retorna zero caso consiga limpar.
 */
void Clear_Array(void* Buffer, unsigned int Buffer_lenght){
    
    for( unsigned int temp = 0x00U; temp < Buffer_lenght; temp ++){

        *(unsigned int*)Buffer = 0x00; // Limpa o buffer com o valor NULL.
    
    }
}


/**
 * @brief  Escreve em Buffer_out, uma string que representa em binario o valor de Variable
 * 
 * @param Variable 
 * @param Buffer_out Bits MSB impressos primeiro.
 * @param Buffer_Lenght 
 */
void Bits_to_String(void* Variable, char* Buffer_out, unsigned int Buffer_Lenght){

    unsigned int Aux = 0;

    for(int i = Buffer_Lenght - 1; i >= 0x00; i--){

        Buffer_out[Aux]  = ((*(unsigned int*)Variable>>i) & 0x01U) + '0';
        Aux++;
    }

    Buffer_out[Buffer_Lenght] = '\0'; // Insere o terminador nulo, que indica o final da string.

}

#endif