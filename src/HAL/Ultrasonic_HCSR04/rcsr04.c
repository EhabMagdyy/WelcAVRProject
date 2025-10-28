/*
 * rcsr04.c
 *
 * Created: 10/26/2025 1:11:47 PM
 *  Author: Ehab
 */ 

#include "../../Lib/SystemConfig.h"
#include "../../Lib/STD_Types.h"
#include "../../MCAL/Timer0/timer0.h"
#include "rcsr04.h"

static TIMER0_Config_t timerConfig = {
	.mode = TIMER0_NORMAL,
	.prescaler = TIMER0_PRESCALER_8,       // 1 us per tick
	.oc_mode = TIMER0_OC_DISCONNECTED,
	.initial_value = 0,
	.compare_value = 0,
	.enable_overflow_interrupt = 0,
	.enable_compare_interrupt = 0
};

void Ultrasonic_Init(ultrasonic_t obj)
{
	DIO_Init(obj.trigger);
	DIO_Init(obj.echo);
	TIMER0_Init(timerConfig);
}

uint16 Ultrasonic_Calculate_Distance(ultrasonic_t obj)
{	
	uint16 Timer0_Value = 0, distance = 0;
	uint8 EchoPinLogic = DIO_LOW;
	
	/* Send Trigger Signal to the Ultrasonic Trigger Pin */
	obj.trigger.logic = DIO_HIGH;
	DIO_SetPinValue(obj.trigger);
	_delay_us(15);
	obj.trigger.logic = DIO_LOW;
	DIO_SetPinValue(obj.trigger);
		
	/* Wait the Echo pin to be High */
	while(DIO_LOW == EchoPinLogic){
		EchoPinLogic = DIO_GetPinLogic(obj.echo);
	}
		
	/* Clear Timer0 Ticks */
	TIMER0_WriteValue(0);

	/* Wait the Echo pin to be Low */
	while(DIO_HIGH == EchoPinLogic)
	{
		EchoPinLogic = DIO_GetPinLogic(obj.echo);
	}
		
	/* Read the time */
	Timer0_Value = TIMER0_ReadValue();
		
	/* Calculate the distance */
	distance = (uint16)((Timer0_Value - 192) / 57) + 3;

	return distance;
}
