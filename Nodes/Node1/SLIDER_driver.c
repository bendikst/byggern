/*
 * SLIDER_driver.c
 *
 * Created: 20.09.2017 10:56:51
 *  Author: aleksra
 */ 


#include "SLIDER_driver.h"
#include "ADC.h"
void SLIDER_init(void){
	
	
}



int SLIDER_pos(bool isright){
	if (isright){
		return adc_read(R_slide)/(double)(255)*100;
	}else{
		return adc_read(L_slide)/(double)(255)*100;
	}
	
}