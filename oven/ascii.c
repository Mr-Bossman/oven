#include "ascii.h"
extern size_t int8_2_char(unsigned char arr[3], uint8_t value){
	register size_t i;
	if(value >= 100)i = 3;
	else if(value >= 10)i = 2;
	else i = 1;
	memset(arr,254,3);
	while(value){
		arr[--i] = (value % 10) + '0';
		value /= 10;
	}
	return 3;
}
extern void print(void (*function)(unsigned char),unsigned char* arr,size_t size){
	for(uint8_t i = 0; i < size;i++)(*function)(arr[i]);
	
}
extern void Cprint(void (*function)(unsigned char),const char* str) {
	register size_t size = strlen(str);
	for(uint8_t i = 0; i < size;i++)(*function)(str[i]);
}