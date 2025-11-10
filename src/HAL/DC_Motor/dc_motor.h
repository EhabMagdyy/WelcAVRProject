
#include "../../Lib/STD_Types.h"
#include "../../MCAL/DIO/dio.h"

#define MOTOR_OFF    0x00
#define MOTOR_ON     0x01

#define MOTOR_PIN_1  0x00
#define MOTOR_PIN_2  0x01

typedef struct{
	pin_config_t motor_pin[2];
} motor_t;

void DC_Motor_Initiliaze(motor_t* motor);
void DC_Motor_Move_CW(motor_t* motor);
void DC_Motor_Move_CCW(motor_t* motor);
void DC_Motor_Stop(motor_t* motor);
