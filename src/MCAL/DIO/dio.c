/*
 * dio.c
 *
 * Created: 9/6/2025 1:57:21 PM
 *  Author: Ehab
 */ 

#include <avr/io.h>
#include "../../Lib/BIT_Math.h"
#include "dio.h"

static volatile uint8* DDR_Registers[3] = { &DDRB, &DDRC, &DDRD};
static volatile uint8* PORT_Registers[3] = {&PORTB, &PORTC, &PORTD};
static volatile uint8* PIN_Registers[3] = {&PINB, &PINC, &PIND};
	
void DIO_Init(pin_config_t* dioPin)
{
	if (dioPin->port < MAX_PORT_NUMBER && dioPin->pin < MAX_PIN_NUMBER)
	{
		switch (dioPin->direction)
		{
			case DIO_DIRECTION_INPUT:  CLEAR_BIT(*(DDR_Registers[dioPin->port]), dioPin->pin); break;
			case DIO_DIRECTION_OUTPUT: SET_BIT(*(DDR_Registers[dioPin->port]), dioPin->pin);   break;
			default: /* invalid argument */ break;
		}
		switch (dioPin->logic)
		{
			case DIO_LOW:  CLEAR_BIT(*(PORT_Registers[dioPin->port]), dioPin->pin); break;
			case DIO_HIGH: SET_BIT(*(PORT_Registers[dioPin->port]), dioPin->pin);   break;
			default: /* invalid argument */ break;
		}
	}
	else
	{
		/* invalid argument */
	}
}

void DIO_SetPinDirection(pin_config_t* dioPin)
{
    if (dioPin->port < MAX_PORT_NUMBER && dioPin->pin < MAX_PIN_NUMBER)
    {
        switch (dioPin->direction)
        {
            case DIO_DIRECTION_INPUT:  CLEAR_BIT(*(DDR_Registers[dioPin->port]), dioPin->pin); break;
            case DIO_DIRECTION_OUTPUT: SET_BIT(*(DDR_Registers[dioPin->port]), dioPin->pin);   break;
            default: /* invalid argument */ break;
        }
    }
    else
    {
        /* invalid argument */
    }
}

void DIO_SetPinValue(pin_config_t* dioPin)
{
    if (dioPin->port < MAX_PORT_NUMBER && dioPin->pin < MAX_PIN_NUMBER)
    {
        switch (dioPin->logic)
        {
            case DIO_LOW:  CLEAR_BIT(*(PORT_Registers[dioPin->port]), dioPin->pin); break;
            case DIO_HIGH: SET_BIT(*(PORT_Registers[dioPin->port]), dioPin->pin);   break;
            default: /* invalid argument */ break;
        }
    }
    else
    {
        /* invalid argument */
    }
}

uint8 DIO_GetPinLogic(uint8 port, uint8 pin)
{
    uint8 pin_value = READ_BIT(port, pin);
    return pin_value;
}

void DIO_TogglePinValue(pin_config_t* dioPin)
{
    if (dioPin->port < MAX_PORT_NUMBER && dioPin->pin < MAX_PIN_NUMBER)
    {
        TOGGLE_BIT(*(PORT_Registers[dioPin->port]), dioPin->pin);
    }
    else
    {
        /* invalid argument */
    }
}