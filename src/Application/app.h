/*
 * app.h
 *
 * Created: 10/23/2025 3:57:46 PM
 *  Author: Ehab
 */ 


#ifndef APP_H_
#define APP_H_

#include "../HAL/DC_Motor/dc_motor.h"
#include "../MCAL/UART/uart.h"
#include "../HAL/Ultrasonic_HCSR04/rcsr04.h"
#include "../MCAL/PWM/pwm.h"

#define CAR_MODE_RC     '6'
#define CAR_MODE_OA     '7'
#define CAR_MODE_LF     '8'
#define CAR_MODE_Maze   '9'

motor_t motorLeft;
motor_t motorRight;

pin_config_t enLeft;
pin_config_t enRight;

UART_Config_t bluetooth;
pin_config_t test;

ultrasonic_t hcsr04;

PWM_Config_t motorPWM;


void initialize_app();

void Car_Mode_RC(uint8 command);
void Car_Mode_OA();
void Car_Mode_LF();
void Car_Mode_Maze();

#endif /* APP_H_ */