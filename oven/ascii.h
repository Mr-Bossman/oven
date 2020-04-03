#ifndef ASCII_H_
#define ASCII_H_
#include "commonH.h"


extern void Cprint(void (*function)(unsigned char),const char* str);
extern size_t int8_2_char(unsigned char arr[3], uint8_t value);
extern size_t int16_2_char(unsigned char arr[5], uint16_t value);
extern void print(void (*function)(unsigned char),unsigned char* arr,size_t size);
extern void memprint(void (*function)(unsigned char),unsigned char arr,size_t size);


#endif