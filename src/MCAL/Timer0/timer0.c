/*
 * timer.c
 *
 * Created: 10/21/2025 12:00:00 PM
 *  Author: Ehab
 */ 

#include "Lib/SystemConfig.h"
#include <avr/interrupt.h>
#include "../../Lib/STD_Types.h"
#include "timer0.h"

void TIMER0_Init(TIMER0_Config_t config)
{
	// Set mode
	switch (config.mode)
	{
		case TIMER0_NORMAL:
		TCCR0A &= ~((1 << WGM00) | (1 << WGM01));
		TCCR0B &= ~(1 << WGM02);
		break;
		case TIMER0_PWM_PHASE_CORRECT:
		TCCR0A = (TCCR0A & ~(1 << WGM01)) | (1 << WGM00);
		TCCR0B &= ~(1 << WGM02);
		break;
		case TIMER0_CTC:
		TCCR0A = (TCCR0A & ~(1 << WGM00)) | (1 << WGM01);
		TCCR0B &= ~(1 << WGM02);
		break;
		case TIMER0_FAST_PWM:
		TCCR0A |= (1 << WGM00) | (1 << WGM01);
		TCCR0B &= ~(1 << WGM02);
		break;
	}

	// Configure compare output mode
	TCCR0A = (TCCR0A & ~((1 << COM0A0) | (1 << COM0A1))) | (config.oc_mode << COM0A0);

	// Set initial and compare values
	TCNT0 = config.initial_value;
	OCR0A = config.compare_value;

	// Interrupts
	if (config.enable_overflow_interrupt) TIMSK0 |= (1 << TOIE0);
	if (config.enable_compare_interrupt) TIMSK0 |= (1 << OCIE0A);

	// Prescaler
	TCCR0B = (TCCR0B & 0xF8) | config.prescaler;
}

void TIMER0_Delay_10us(void)
{
	// Start timer
	TCCR0B |= (1 << CS00); // prescaler = 1

	// Wait for compare flag
	while (!(TIFR0 & (1 << OCF0A)));

	// Clear flag
	TIFR0 |= (1 << OCF0A);

	// Stop timer
	TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
}

void TIMER0_WriteValue(uint8 value)
{
	TCNT0 = value;
}

uint8 TIMER0_ReadValue(void)
{
	return TCNT0;
}
