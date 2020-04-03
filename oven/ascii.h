/*
 * IncFile1.h
 *
 * Created: 4/2/2020 11:13:55 PM
 *  Author: jesse
 */ 


#ifndef ASCII_H_
#define ASCII_H_
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

extern void Cprint(void (*function)(unsigned char),const char* str);
extern size_t int8_2_char(unsigned char** arr, uint8_t value);
extern void print(void (*function)(unsigned char),unsigned char* arr,size_t size);



#endif