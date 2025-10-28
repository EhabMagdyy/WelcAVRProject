/*
 * uart.h
 *
 * Created: 9/6/2025 1:59:04 PM
 *  Author: Ehab
 */ 


#ifndef UART_H_
#define UART_H_

#include "../../Lib/STD_Types.h"

typedef enum {
    UART_DATA_5BIT = 0,
    UART_DATA_6BIT,
    UART_DATA_7BIT,
    UART_DATA_8BIT
} UART_DataBits_t;

typedef enum {
    UART_PARITY_NONE = 0,
    UART_PARITY_EVEN,
    UART_PARITY_ODD
} UART_Parity_t;

typedef enum {
    UART_STOP_1BIT = 0,
    UART_STOP_2BIT
} UART_StopBits_t;

typedef struct {
    uint32 baudrate;
    UART_DataBits_t data_bits;
    UART_Parity_t parity;
    UART_StopBits_t stop_bits;
} UART_Config_t;

void UART_Init(UART_Config_t config);
void UART_SendByte(uint8 data);
uint8 UART_ReceiveByte();
void UART_SendString(const char* str);
void UART_EnableRxInterrupt();

#endif /* UART_H_ */