#ifndef STRING_INC
#define STRING_INC


unsigned int String_counter(char *Str); // Conta quantos Chrs tem em uma string

void String_clear(char* String);  // Limpa todos os espa?os da string por ' '

void String_set(char* Container, char* String); // Seta uma string com o array informado.

void Clear_Array(void* Buffer, unsigned int Buffer_lenght); // Limpa um array com 0x00.

char* Dots(); // Devolve uma animacao de pontos carregando usando uma string.

void Bits_to_String(void* Variable, char* Buffer_out, unsigned int Buffer_Lenght); // imprime me formato binario uma variavel.


#endif