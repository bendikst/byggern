/*
 * SLIDER_driver.c
 *
 * Created: 20.09.2017 10:56:51
 *  Author: aleksra
 */ 

#include "SLIDER_driver.h"
#include "ADC.h"


int SLIDER_pos(bool isright)
{
	if (isright)
    {
		return adc_read(R_slide);
	}
    else
    {
		return adc_read(L_slide);
	}
}
