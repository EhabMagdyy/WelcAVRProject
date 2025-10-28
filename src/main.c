/*
 * RC_Car.c
 *
 * Created: 10/22/2025 12:27:41 PM
 * Author : Ehab
 */ 

#include "Lib/SystemConfig.h"
#include "Application/app.h"

volatile uint8 receivedCommand = 0;

// ISR for UART receive interrupt
void UART_InterruptHandler(void)
{
	// Read received byte
	receivedCommand = UDR0;
	
	switch (receivedCommand)
	{
		case CAR_MODE_RC: Car_Mode_RC(receivedCommand); break;
		case CAR_MODE_OA: Car_Mode_OA();				break;
		case CAR_MODE_LF: Car_Mode_LF();				break;
		case CAR_MODE_Maze: Car_Mode_Maze();			break;
		default: 										break;
	}
}


int main(void)
{	
	initialize_app();
	UART_EnableRxInterrupt(UART_InterruptHandler);
	
    while (1) 
    {
		
    }
}


