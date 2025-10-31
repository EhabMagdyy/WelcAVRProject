/*
 * pwm.c
 *
 * Created: 10/26/2025 10:43:35 PM
 *  Author: Ehab
 */ 

#include "../../Lib/SystemConfig.h"
#include "../../Lib/BIT_Math.h"
#include "pwm.h"

#define TIMER1_PRESCALER 8

static PWM_Config_t pwmConfig;

void PWM1_Init(PWM_Config_t* config)
{
	pwmConfig = *config;

 	SET_BIT(DDRB, PB1);

	TCCR1A = (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12);

	TCCR1A |= (1 << COM1A1);

	uint16 prescaler_val = TIMER1_PRESCALER;  // timer clock -> 2 MHz
	uint32 top = (F_CPU / (prescaler_val * config->frequency)) - 1;
	ICR1 = (uint16)top;

	PWM1_SetDutyCycle(config->duty_cycle);
}

void PWM1_SetDutyCycle(uint8 duty)
{
	if (duty > 100){
		 duty = 100;
	}
	else { /* Nothing */ }

	OCR1A = (uint16)((duty / 100.0) * ICR1);
}

void PWM1_Start(void)
{
	TCCR1B = (TCCR1B & 0xF8) | (1 << CS11);
}

void PWM1_Stop(void)
{
	TCCR1B &= 0xF8;
}
