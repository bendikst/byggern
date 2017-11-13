/*
 * PID_controller.h
 *
 * Created: 08.11.2017 16:30:33
 *  Author: alexjoha
 */ 


#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

void PID_init(void);
void PID_update_reference(uint8_t pos);
void PID_regulator(void);

#endif /* PID_CONTROLLER_H_ */