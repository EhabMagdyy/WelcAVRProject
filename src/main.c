/*
 * RC_Car.c
 *
 * Created: 10/22/2025 12:27:41 PM
 * Author : Ehab
 */ 

#include "Lib/SystemConfig.h"
#include "Application/app.h"

volatile uint8 modeCommand = '6';
volatile uint8 RCCommand = 0;

void UART_InterruptHandler(void)
{
	uint8 recCommand = UDR0;

	switch(recCommand){
		case '6' ... '9':	modeCommand = recCommand; break;
		case 'A' ... 'Z':	
		case '1' ... '5':	
							RCCommand = recCommand;   break;
		default: 									  break;
	}
}


int main(void)
{	
	initialize_app();
	UART_EnableRxInterrupt(UART_InterruptHandler);
	
    while (1) {
		Car_Mode_RC();
		Car_Mode_OA();
		Car_Mode_LF();
		Car_Mode_Maze();
    }
}


