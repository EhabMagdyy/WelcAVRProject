/*
 * dio.h
 *
 * Created: 9/6/2025 1:57:37 PM
 *  Author: Ehab
 */ 


#ifndef DIO_H_
#define DIO_H_


#include "../../Lib/STD_Types.h"

/* ----------------------------------------------------
 *                CONSTANTS & DEFINITIONS
 * --------------------------------------------------*/
#define MAX_PORT_NUMBER   3  /* ATmega328P has 3 ports: B, C, D */
#define MAX_PIN_NUMBER    8

/* Pin Direction */
#define DIO_DIRECTION_INPUT   0
#define DIO_DIRECTION_OUTPUT  1

/* Pin Value */
#define DIO_LOW   0
#define DIO_HIGH  1

/* ----------------------------------------------------
 *                ENUMS
 * --------------------------------------------------*/
typedef enum {
    PORT_B = 0,  /* Port B: Digital pins 8 to 13 */
    PORT_C,      /* Port C: Analog input pins */
    PORT_D       /* Port D: Digital pins 0 to 7 */
} DIO_Port_t;

typedef enum {
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7
} DIO_Pin_t;

/********************* Data Types Declarations ********************/
typedef struct{
	DIO_Port_t port      :3;
	DIO_Pin_t  pin       :3;
	uint8    direction   :1;
	uint8    logic       :1;
} pin_config_t;

/**********************  FUNCTION PROTOTYPES  *********************/
void DIO_Init(pin_config_t* dioPin);
void DIO_SetPinDirection(pin_config_t* dioPin);
void DIO_SetPinValue(pin_config_t* dioPin);
uint8 DIO_GetPinLogic(pin_config_t* dioPin);
void DIO_TogglePinValue(pin_config_t* dioPin);


#endif /* DIO_H_ */