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

}




/**
 * @brief Esta funcao escreve a string no array de chars indicado.
 * 
 * @param Container Array de caracteres
 * @param String   String ao qual deseja imprimir no Array
 */
void String_set(char* Container, char* String){

    String_clear(Container);

    unsigned int Lenght = String_counter(String);

    for(unsigned int i = 0; i < Lenght ; i++){

       *(Container+1) = *(String+i);
    
    }

}


/**
 * @brief Limpa todos os valores de um buffer com o valor 0x00.
 * 
 * @param Buffer O Buffer de chars que deseja limpar.
 * @return int retorna zero caso consiga limpar.
 */
int Clear_buffer(void* Buffer){
    
    for( char * temp = Buffer; *temp != '\n'; temp ++)

        *temp = 0x00; // Limpa o buffer com o valor NULL.
    
    return 0;
}

#endif