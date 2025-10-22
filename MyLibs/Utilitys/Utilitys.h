unsigned int String_counter(char *Str){

    char *P = Str;

    while(*P != 0){
     P++;
    }

    return P - Str;
}


char* Number_to_ASCII(unsigned int Value){

    int k = 0;
    if(Value < 9999){
      static char Matriz[5];
      static char *Pointer;

     //Extrai algarismo da casa das unidades.
    
        Matriz[3] = Value % 10;             // Unidades
        Matriz[2] = (Value / 10) % 10;     // Dezenas
        Matriz[1] = (Value/ 100) % 10;    // Centenas
        Matriz[0] = Value/ 1000;         // Milhares  

        for(k = 0; k < 5; k++){
            Matriz[k] = Matriz[k] + '0';
        }   

        Matriz[4] = '\0';
       
        Pointer = &Matriz[0]; // O Ponteiro recebe o endere?o do primeiro indice da matriz.

        return Pointer; // A fun??o retorna o primeiro endere?o da matriz que contem os algarismos em sequencia do numero de entrada.
 }else return 0;
}


/**
 * @brief Retorna o maior valor inteiro deste array.
 * 
 * @param Array A matriz do qual se deseja extrair o maior valor.
 * @param indice O tamanho da sua matriz.
 * @return int 
 */
int Major_value(const int Array[], unsigned int indice){
   
    int Max = Array[0];

    for(unsigned int i = 0; i < indice; i++){
        if(Array[i] > Max) { Max = Array[i]; }
    }
    return Max;
}


/**
 * @brief Esta funcao te retorna o menor valor de uma matriz.
 * 
 * @param Array A Matriz ao qual deseja extrair o menor valor.
 * @param indice O tamanho da sua Matriz.
 * @return int 
 */
int Minor_value(const int Array[], unsigned int indice){
    int Min = Array[0];

    for(unsigned int i = 1; i < indice; i++){
        if( Array[i] < Min ){ Min = Array[i];}
    }

    return Min;
}


/**
 * @brief Esta funcao devolve a media do seu Array.
 * 
 * @param Array A Matriz ao qual deseja extrair a m¨¦dia
 * @param Indice O tamanho da sua Matriz
 * @return int 
 */
int Avarage_value(int Array[], unsigned int Indice){
    long counter = 0;


    for(unsigned int  i = 0; i < Indice; i++){
    counter += Array[i];
    }

    counter = counter/Indice;


    return (int)counter;
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