#include "ascii.h"
extern size_t int8_2_char(unsigned char** arr, uint8_t value){
	register size_t i;
	if(value >= 100)(*arr) = calloc(3,1), i = 3;
	else if(value >= 10)(*arr) = calloc(2,1), i = 2;
	else (*arr) = calloc(1,1),i = 1;
	register size_t b = i;
	while(b--){
		(*arr)[b] = (value % 10)+'0';
		value /= 10;
	}
	return i;
}
extern void print(void (*function)(unsigned char),unsigned char* arr,size_t size){
	for(uint8_t i = 0; i < size;i++)(*function)(arr[i]);
	
}
extern void Cprint(void (*function)(unsigned char),const char* str) {
	register size_t size = strlen(str);
	for(uint8_t i = 0; i < size;i++)(*function)(str[i]);
}