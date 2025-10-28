/*
 * pwm.c
 *
 * Created: 10/26/2025 10:43:35 PM
 *  Author: Ehab
 */ 

#include "../../Lib/SystemConfig.h"
#include "pwm.h"

#define TIMER1_PRESCALER 8

static PWM_Config_t g_pwmConfig;

void PWM1_Init(PWM_Config_t config)
{
	g_pwmConfig = config;

	// Configure OC1A (PB1) as output for Timer1 PWM on ATmega328P
	DDRB |= (1 << PB1);

	// Set Fast PWM mode using ICR1 as TOP "Mode 14"
	TCCR1A = (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12);

	// Non-inverting mode on OC1A (Clear on compare)
	TCCR1A |= (1 << COM1A1);

	// Calculate prescaler & ICR1 "TOP"
	uint16 prescaler_val = TIMER1_PRESCALER;  // timer clock -> 1 MHz
	uint32 top = (F_CPU / (prescaler_val * config.frequency)) - 1;
	ICR1 = (uint16)top;

	// Set initial duty cycle
	PWM1_SetDutyCycle(config.duty_cycle);
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
