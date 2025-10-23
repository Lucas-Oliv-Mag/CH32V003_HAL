#ifndef MATH_SRC
#define MATH_SRC



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
 * @param Array A Matriz ao qual deseja extrair a m§Ú§Ødia
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























#endif