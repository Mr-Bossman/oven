#include "UI.h"
#include "common.h"
#include "menus.h"
#include "temp_control.h"

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
			return menu2("Enter Time S:",240,10);
}
void Options(struct tempC * data){
	for(uint8_t i = 0; i < 6;i++){
		uint8_t option = menu1("Select an option:\n>Set target temp...\n Set rise time...\n Set temp...\n C or F...\n Start...",5);
		switch (option){
			case 0:{
				data[i].stableTemp = false;
				data[i].temp = getTemp();
				data[i].rise = getTempRise();
				continue;
			}
			case 1:{
				data[i].stableTemp = false;
				data[i].times = getTime();
				data[i].rise = getTempRise();
				continue;
			}
			case 2:{
				data[i].stableTemp = true;
				data[i].times = getTime();
				data[i].temp = getTemp();
				continue;
			}
			case 3:{
				C ^= true;
				continue;
			}
			case 4:{
				break;
			}
		}
		break;
	}
}