/*
 * timer.h
 *
 * Created: 10/21/2025 12:00:00 PM
 *  Author: Ehab
 */ 


#ifndef TIMER_H_
#define TIMER_H_

void Timer0_Init();
void Timer0_WriteValue(uint8 value);
uint8 Timer0_ReadValue();
uint8 Timer0_CheckOverFlow();
void Timer0_ClearOverFlowFlag();

#endif /* TIMER_H_ */