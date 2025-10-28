/*
 * pwm.h
 *
 * Created: 10/26/2025 10:43:49 PM
 *  Author: Ehab
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "../../Lib/STD_Types.h"

typedef struct {
	uint32 frequency;      // Desired PWM frequency in Hz
	uint8 duty_cycle;      // Initial duty cycle (0–100%)
} PWM_Config_t;

void PWM1_Init(PWM_Config_t config);
void PWM1_SetDutyCycle(uint8 duty);
void PWM1_Start(void);
void PWM1_Stop(void);


#endif /* PWM_H_ */