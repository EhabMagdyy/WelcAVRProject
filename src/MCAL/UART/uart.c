/*
 * uart.c
 *
 * Created: 9/6/2025 1:59:59 PM
 *  Author: Ehab
 */ 

#include "../../Lib/SystemConfig.h"
#include <avr/interrupt.h>
#include "../../Lib/STD_Types.h"
#include "../../Lib/BIT_Math.h"
#include "uart.h"

static void (*UART_RecInterruptHandlerFP)(void) = NULL;

void UART_Init(UART_Config_t config)
{
    // 1. Calculate baudrate for ATmega328P
    uint16 ubrr = (F_CPU / (16UL * config.baudrate)) - 1;
    UBRR0H = (uint8)(ubrr >> 8);
    UBRR0L = (uint8)ubrr;

    // 2. Enable transmitter and receiver
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // 3. Set frame format
    uint8 ucsrc = 0; // URSEL not needed in ATmega328P
    
    // 4. Configure data bits
    switch (config.data_bits)
    {
        case UART_DATA_5BIT:
            ucsrc &= ~((1 << UCSZ01) | (1 << UCSZ00));
            UCSR0B &= ~(1 << UCSZ02);
            break;
        case UART_DATA_6BIT:
            ucsrc |= (1 << UCSZ00);
            ucsrc &= ~(1 << UCSZ01);
            UCSR0B &= ~(1 << UCSZ02);
            break;
        case UART_DATA_7BIT:
            ucsrc |= (1 << UCSZ01);
            ucsrc &= ~(1 << UCSZ00);
            UCSR0B &= ~(1 << UCSZ02);
            break;
        case UART_DATA_8BIT:
            ucsrc |= (1 << UCSZ01) | (1 << UCSZ00);
            UCSR0B &= ~(1 << UCSZ02);
            break;
        default:
            break;
    }

    // 5. Configure parity
    switch (config.parity)
    {
        case UART_PARITY_NONE:
            ucsrc &= ~((1 << UPM01) | (1 << UPM00));
            break;
        case UART_PARITY_EVEN:
            ucsrc |= (1 << UPM01);
            ucsrc &= ~(1 << UPM00);
            break;
        case UART_PARITY_ODD:
            ucsrc |= (1 << UPM01) | (1 << UPM00);
            break;
        default:
            break;
    }

    // 6. Configure stop bits
    switch (config.stop_bits)
    {
        case UART_STOP_1BIT:
            ucsrc &= ~(1 << USBS0);
            break;
        case UART_STOP_2BIT:
            ucsrc |= (1 << USBS0);
            break;
        default:
            break;
    }

    // Write to UCSR0C
    UCSR0C = ucsrc;
}

void UART_SendByte(uint8 data)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait for empty tx buffer
    UDR0 = data;
}

uint8 UART_ReceiveByte()
{
    while (!(UCSR0A & (1 << RXC0))); // Wait for data to be received
    return UDR0;
}

void UART_SendString(const char* str)
{
    while (*str != '\0')
    {
        UART_SendByte(*str);
        str++;
    }
}

void UART_EnableRxInterrupt(void (*UART_InterruptHandler)(void))
{
	// Set ISR handler callback function
	UART_RecInterruptHandlerFP = UART_InterruptHandler;
    SET_BIT(UCSR0B, RXCIE0);	// Enable receive interrupt
	sei();
}

ISR(USART_RX_vect)
{
	if (NULL != UART_RecInterruptHandlerFP)
	{
		UART_RecInterruptHandlerFP();
	}
}
