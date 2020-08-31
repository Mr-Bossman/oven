#include "UI.h"
#include "common.h"
#include "menus.h"

static bool C = true;

static uint16_t getTemp(){
	if(C)
		return menu2("Enter Temp *C:",475,100);
	else 
		return ((menu2("Enter Temp *F:",885,215)-32)*5)/9;
}

static int16_t getTempRise(){
		if(C)
		return menu3("Enter *C/S:",500,-500,2);
		else
		return ((menu3("Enter *F/S:",900,-900,2))*5)/9;
}

static uint16_t getTime(){
			return menu2("Enter Duration S:",240,10);
}
extern void Options(uint32_t data[6]){
	
	for(uint8_t i = 0; i < 6;i++){
		uint8_t option = menu1("Select an option:\n>Set ramp Temp...\n Set Temp...\n C or F...\n Start...",4);
		switch (option){
			case 0:{
				data[i] = (uint32_t) getTemp() | ( ( (uint32_t)getTime() & ~(1ul << 15)) << 16) ;
				continue;
			}
			case 1:{
				data[i] = (uint32_t) getTemp() | ( ( (uint32_t)getTime() | (1ul << 15)) << 16) ;
				continue;
			}
			case 2:{
				C ^= true;
				continue;
			}
			case 3:{
				break;
			}
		}
		break;
	}
}