/*
 * ADC.h
 *
 * Created: 13.09.2017 13:40:55
 *  Author: bendikss
 */ 
#ifndef ADC_H
#define ADC_H

#define ext_ram         ((volatile char*) 0x1800)
#define ext_ram_size    0x800
#define ext_adc         ((volatile char*) 0x1400)
#define ext_oled_cmd    ((volatile char*) 0x1000)
#define ext_oled_data ((volatile char*) 0x1200)


typedef enum{
	X_axis = 4, //axis 2 Joystick 
	Y_axis = 5, //axis 1 Joystick
	R_slide = 6, //right slider
	L_slide = 7, //left slider

}channel_type;

void ADC_init(void);
uint8_t adc_read(channel_type channel);

#endif /* ADC_H */