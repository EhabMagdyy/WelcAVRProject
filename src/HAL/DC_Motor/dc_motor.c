
#include <avr/io.h>
#include "../../MCAL/DIO/dio.h"
#include "dc_motor.h"

void DC_Motor_Initiliaze(motor_t* motor){
	motor->motor_pin[MOTOR_PIN_1].direction = DIO_DIRECTION_OUTPUT;
	motor->motor_pin[MOTOR_PIN_2].direction = DIO_DIRECTION_OUTPUT;
	DIO_Init(&(motor->motor_pin[MOTOR_PIN_1]));
	DIO_Init(&(motor->motor_pin[MOTOR_PIN_2]));
}

void DC_Motor_Move_CW(motor_t* motor){
	motor->motor_pin[MOTOR_PIN_1].logic = DIO_HIGH;
	motor->motor_pin[MOTOR_PIN_2].logic = DIO_LOW;
	DIO_SetPinValue(&(motor->motor_pin[MOTOR_PIN_1]));
	DIO_SetPinValue(&(motor->motor_pin[MOTOR_PIN_2]));
}

void DC_Motor_Move_CCW(motor_t* motor){
	motor->motor_pin[MOTOR_PIN_1].logic = DIO_LOW;
	motor->motor_pin[MOTOR_PIN_2].logic = DIO_HIGH;
	DIO_SetPinValue(&(motor->motor_pin[MOTOR_PIN_1]));
	DIO_SetPinValue(&(motor->motor_pin[MOTOR_PIN_2]));
}

void DC_Motor_Stop(motor_t* motor){
	motor->motor_pin[MOTOR_PIN_1].logic = DIO_LOW;
	motor->motor_pin[MOTOR_PIN_2].logic = DIO_LOW;
	DIO_SetPinValue(&(motor->motor_pin[MOTOR_PIN_1]));
	DIO_SetPinValue(&(motor->motor_pin[MOTOR_PIN_2]));
}