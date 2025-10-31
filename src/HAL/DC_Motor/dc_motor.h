/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : dc_motor.h		**************
************	Data  : 26 Aug, 2023	**************
******************************************************/

/********************  Includes **********************/
#include "../../Lib/STD_Types.h"
#include "../../MCAL/DIO/dio.h"

/************** Macro definitions ********************/
#define MOTOR_OFF    0x00
#define MOTOR_ON     0x01

#define MOTOR_PIN_1  0x00
#define MOTOR_PIN_2  0x01

/*************** Data Types Declarations **************/
typedef struct{
	pin_config_t motor_pin[2];
} motor_t;

/************** Functions Decelerations **************/
void DC_Motor_Initiliaze(motor_t* motor);
void DC_Motor_Move_CW(motor_t* motor);
void DC_Motor_Move_CCW(motor_t* motor);
void DC_Motor_Stop(motor_t* motor);
