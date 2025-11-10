
#include "Lib/SystemConfig.h"
#include <avr/interrupt.h>
#include "../../Lib/STD_Types.h"
#include "timer0.h"

void Timer0_Init(){
    TCCR0A = 0;
    TCCR0B = (1 << CS01) | (1 << CS00);   // prescaler 64
    TCNT0 = 0;
}

void Timer0_WriteValue(uint8 value){
	TCCR0B = value;
}

uint8 Timer0_ReadValue(){
	return TCNT0;
}

uint8 Timer0_CheckOverFlow(){
	return TIFR0 & (1 << TOV0);
}

void Timer0_ClearOverFlowFlag(){
	TIFR0 |= (1 << TOV0);
}