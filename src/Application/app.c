/*
 * app.c
 *
 * Created: 10/23/2025 3:57:35 PM
 *  Author: Ehab
 */ 

#include "../Lib/SystemConfig.h"
#include "app.h"

static void CAR_Move_Forward();
static void CAR_Move_Backward();
static void CAR_Move_Right();
static void CAR_Move_Left();
static void CAR_Stop();

motor_t motorLeft = {
	.motor_pin = {
		{ .port = PORT_B, .pin = PIN_0, .direction = DIO_DIRECTION_OUTPUT, .logic = DIO_LOW },
		{ .port = PORT_B, .pin = PIN_1, .direction = DIO_DIRECTION_OUTPUT, .logic = DIO_LOW }
	}
};

motor_t motorRight = {
	.motor_pin = {
		{ .port = PORT_B, .pin = PIN_2, .direction = DIO_DIRECTION_OUTPUT, .logic = DIO_LOW },
		{ .port = PORT_B, .pin = PIN_3, .direction = DIO_DIRECTION_OUTPUT, .logic = DIO_LOW }
	}
};

UART_Config_t bluetooth = {
	.baudrate = 9600,
	.data_bits = UART_DATA_8BIT,
	.parity = UART_PARITY_NONE,
	.stop_bits = UART_STOP_1BIT
};

pin_config_t test = {.port = PORT_B, .pin = PIN_5, .direction = DIO_DIRECTION_OUTPUT, .logic = DIO_LOW};
	
ultrasonic_t hcsr04 = {
	.trigger = { .port = PORT_B, .pin = PIN_0, .direction = DIO_DIRECTION_OUTPUT, .logic = DIO_LOW },
	.echo    = { .port = PORT_B, .pin = PIN_1, .direction = DIO_DIRECTION_INPUT,  .logic = DIO_LOW }
};

PWM_Config_t motorPWM = {
	.frequency = 1000,    
	.duty_cycle = 50      
};


void initialize_app(){
	DC_Motor_Initiliaze(motorLeft);
	DC_Motor_Initiliaze(motorRight);
	UART_Init(bluetooth);
	DIO_Init(test);
	Ultrasonic_Init(hcsr04);
	PWM1_Init(motorPWM);
	PWM1_Start();
}

void Car_Mode_RC(uint8 command){
	switch (command)
	{	
		case 'F': CAR_Move_Forward();  break;
		case 'B': CAR_Move_Backward(); break;
		case 'R': CAR_Move_Right();		   break;
		case 'L': CAR_Move_Left();		   break;
		case 'S': CAR_Stop();			   break;
		case '1': PWM1_SetDutyCycle(20);   break;
		case '2': PWM1_SetDutyCycle(40);   break;
		case '3': PWM1_SetDutyCycle(60);   break;
		case '4': PWM1_SetDutyCycle(80);   break;
		case '5': PWM1_SetDutyCycle(100);  break;
		default:  DIO_TogglePinValue(test);	break;
	}
}

void Car_Mode_OA(){
	uint16 distance = Ultrasonic_Calculate_Distance(hcsr04);
	UART_SendString("Distance: ");
	char buffer[10];
	sprintf(buffer, "%u", distance);
	UART_SendString(buffer);
	UART_SendString(" cm\n");
	//_delay_ms(10);
}

void Car_Mode_LF(){

}

void Car_Mode_Maze(){

}

static void CAR_Move_Forward(){
	DC_Motor_Move_CW(motorLeft);
	DC_Motor_Move_CW(motorRight);
}

static void CAR_Move_Backward(){
	DC_Motor_Move_CCW(motorLeft);
	DC_Motor_Move_CCW(motorRight);
}

static void CAR_Move_Right(){
	DC_Motor_Move_CW(motorLeft);
	DC_Motor_Move_CCW(motorRight);
}

static void CAR_Move_Left(){
	DC_Motor_Move_CCW(motorLeft);
	DC_Motor_Move_CW(motorRight);
}

static void CAR_Stop(){
	DC_Motor_Stop(motorLeft);
	DC_Motor_Stop(motorRight);
}