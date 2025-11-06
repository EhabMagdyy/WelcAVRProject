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
		{ .port = PORT_B, .pin = PIN_3, .direction = DIO_DIRECTION_OUTPUT, .logic = DIO_LOW },
		{ .port = PORT_B, .pin = PIN_4, .direction = DIO_DIRECTION_OUTPUT, .logic = DIO_LOW }
	}
};

motor_t motorRight = {
	.motor_pin = {
		{ .port = PORT_D, .pin = PIN_6, .direction = DIO_DIRECTION_OUTPUT, .logic = DIO_LOW },
		{ .port = PORT_D, .pin = PIN_7, .direction = DIO_DIRECTION_OUTPUT, .logic = DIO_LOW }
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

pin_config_t irLeft = { .port = PORT_C, .pin = PIN_2, .direction = DIO_DIRECTION_INPUT,  .logic = DIO_LOW };
pin_config_t irRight = { .port = PORT_C, .pin = PIN_3, .direction = DIO_DIRECTION_INPUT,  .logic = DIO_LOW };

// changed by uart isr
extern volatile uint8 modeCommand;
extern volatile uint8 RCCommand;

void initialize_app(){
	DC_Motor_Initiliaze(&motorLeft);
	DC_Motor_Initiliaze(&motorRight);
	UART_Init(bluetooth);
	IR_Init(&irLeft);
	IR_Init(&irRight);
}

void Car_Mode_RC(){
	PWM1_Init(&motorPWM);
	PWM1_Start();
	while (CAR_MODE_RC == modeCommand) {
#ifdef DEBUG_MESSAGES_ENABLED
		UART_SendString("Command: ");
		char debug[12];
		sprintf(debug, "%c", RCCommand);
		UART_SendString(debug);
		UART_SendString("\n");
#endif
        switch (RCCommand) {
            case 'F': CAR_Move_Forward(); 	 _delay_ms(50);  break;
            case 'B': CAR_Move_Backward(); 	 _delay_ms(50);  break;
            case 'R': CAR_Move_Right(); 	 _delay_ms(50);  break;
            case 'L': CAR_Move_Left(); 		 _delay_ms(50);  break;
            case 'S': CAR_Stop(); 			 _delay_ms(50);  break;
            case '1': PWM1_SetDutyCycle(20); _delay_ms(50);  break;
            case '2': PWM1_SetDutyCycle(40); _delay_ms(50);  break;
            case '3': PWM1_SetDutyCycle(60); _delay_ms(50);  break;
            case '4': PWM1_SetDutyCycle(80); _delay_ms(50);  break;
            case '5': PWM1_SetDutyCycle(100);_delay_ms(50);  break;
            default: break;
        }
    }
	PWM1_SetDutyCycle(50);
}

void Car_Mode_OA(void) {
	uint16_t distance = 0;
    while (CAR_MODE_OA == modeCommand) {
        distance = Ultrasonic_Calculate_Distance(&ultrasonic_sensor);

        if (distance > 25) {
            CAR_Move_Forward();
        } 
        else if (distance <= 25 && distance > 0) {
            CAR_Move_Backward();
            _delay_ms(200);

            CAR_Move_Right();
            _delay_ms(400);
            CAR_Stop();
            _delay_ms(100);

            uint16_t newDist = Ultrasonic_Calculate_Distance(&ultrasonic_sensor);

            if (newDist <= 20 && newDist > 0) {
                CAR_Move_Left();
                _delay_ms(600);
                CAR_Stop();
                _delay_ms(100);

                newDist = Ultrasonic_Calculate_Distance(&ultrasonic_sensor);

                if (newDist <= 20 && newDist > 0) {
                    CAR_Move_Backward();
                    _delay_ms(300);
                    CAR_Stop();
                }
            }
        } 
        else {
            CAR_Stop();
        }

        _delay_ms(50);
    }

    CAR_Stop();
}

void Car_Mode_LF(){
	PWM1_Init(&motorPWM);
	PWM1_SetDutyCycle(50);
	uint8 leftState, rightState;

	while (CAR_MODE_LF == modeCommand) {
        leftState  = IR_ReadValue(&irLeft);
        rightState = IR_ReadValue(&irRight);

        if (leftState == DIO_LOW && rightState == DIO_LOW) {
            CAR_Move_Forward();
        }
        else if (leftState == DIO_LOW && rightState == DIO_HIGH) {
            CAR_Move_Left();
        }
        else if (leftState == DIO_HIGH && rightState == DIO_LOW) {
            CAR_Move_Right();
        }
        else {
            CAR_Stop();
        }

#ifdef DEBUG_MESSAGES_ENABLED
		UART_SendString("LF Sensors: ");
		char debug[10];
        UART_SendString("LF: L=");
		sprintf(debug, "%u", leftState);
		UART_SendString(debug);
        UART_SendString(" R=");
		sprintf(debug, "%u", rightState);
		UART_SendString(debug);
        UART_SendString("\n");
#endif

        _delay_ms(50);
    }

	CAR_Stop();
}

void Car_Mode_Maze(){
	while (CAR_MODE_Maze == modeCommand) {
		
	}
	CAR_Stop();
}

static void CAR_Move_Forward(){
	DC_Motor_Move_CW(&motorLeft);
	DC_Motor_Move_CW(&motorRight);
}

static void CAR_Move_Backward(){
	DC_Motor_Move_CCW(&motorLeft);
	DC_Motor_Move_CCW(&motorRight);
}

static void CAR_Move_Right(){
	DC_Motor_Move_CW(&motorLeft);
	DC_Motor_Move_CCW(&motorRight);
}

static void CAR_Move_Left(){
	DC_Motor_Move_CCW(&motorLeft);
	DC_Motor_Move_CW(&motorRight);
}

static void CAR_Stop(){
	DC_Motor_Stop(&motorLeft);
	DC_Motor_Stop(&motorRight);
}