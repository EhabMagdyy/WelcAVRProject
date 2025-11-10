
#ifndef HCSR04_H_
#define HCSR04_H_

#include "../../MCAL/DIO/dio.h"

typedef struct {
	pin_config_t trigger;
	pin_config_t echo;
} ultrasonic_t;

void Ultrasonic_Init(ultrasonic_t* obj);
uint16 Ultrasonic_Calculate_Distance(ultrasonic_t* obj);

#endif /* HCSR04_H_ */