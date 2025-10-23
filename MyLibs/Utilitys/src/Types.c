#ifndef TYPE_SRC
#define TYPE_SRC



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
























#endif