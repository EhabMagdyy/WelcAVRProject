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
	
ultrasonic_t hcsr04 = {
	.trigger = { .port = PORT_B, .pin = PIN_1, .direction = DIO_DIRECTION_OUTPUT, .logic = DIO_LOW },
	.echo    = { .port = PORT_B, .pin = PIN_2, .direction = DIO_DIRECTION_INPUT,  .logic = DIO_LOW }
};

PWM_Config_t motorPWM = {
	.frequency = 1000,    
	.duty_cycle = 50      
};

// received by isr
extern volatile uint8 modeCommand;
extern volatile uint8 RCCommand;

void initialize_app(){
	DC_Motor_Initiliaze(motorLeft);
	DC_Motor_Initiliaze(motorRight);
	UART_Init(bluetooth);
	Ultrasonic_Init(&ultrasonic_sensor);
	PWM1_Init(motorPWM);
	PWM1_Start();
}

void Car_Mode_RC(){
	while (CAR_MODE_RC == modeCommand) {
		UART_SendString("Command: ");
		char buffer[12];
		sprintf(buffer, "%c", RCCommand);
		UART_SendString(buffer);
		UART_SendString("\n");
        switch (RCCommand) {
            case 'F': CAR_Move_Forward(); 	 _delay_ms(20);  break;
            case 'B': CAR_Move_Backward(); 	 _delay_ms(20);  break;
            case 'R': CAR_Move_Right(); 	 _delay_ms(20);  break;
            case 'L': CAR_Move_Left(); 		 _delay_ms(20);  break;
            case 'S': CAR_Stop(); 			 _delay_ms(20);  break;
            case '1': PWM1_SetDutyCycle(20); _delay_ms(20);  break;
            case '2': PWM1_SetDutyCycle(40); _delay_ms(20);  break;
            case '3': PWM1_SetDutyCycle(60); _delay_ms(20);  break;
            case '4': PWM1_SetDutyCycle(80); _delay_ms(20);  break;
            case '5': PWM1_SetDutyCycle(100);_delay_ms(20);  break;
            default: break;
        }
    }
}

void Car_Mode_OA(){
	while (CAR_MODE_OA == modeCommand) {
		uint16 distance = Ultrasonic_Calculate_Distance(&ultrasonic_sensor);
		UART_SendString("Distance: ");
		char buffer[10];
		sprintf(buffer, "%u", distance);
		UART_SendString(buffer);
		UART_SendString(" cm\n");
		_delay_ms(50);
	}
}

void Car_Mode_LF(){
	while (CAR_MODE_LF == modeCommand) {
		
	}
}

void Car_Mode_Maze(){
	while (CAR_MODE_Maze == modeCommand) {
		
	}
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