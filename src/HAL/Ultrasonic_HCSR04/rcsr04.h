/*
 * rcsr04.h
 *
 * Created: 10/26/2025 1:12:09 PM
 *  Author: Ehab
 */ 


#ifndef RCSR04_H_
#define RCSR04_H_

#include "../../MCAL/DIO/dio.h"

typedef struct {
	pin_config_t trigger;
	pin_config_t echo;
} ultrasonic_t;

void Ultrasonic_Init(ultrasonic_t obj);
uint16 Ultrasonic_Calculate_Distance(ultrasonic_t obj);

#endif /* RCSR04_H_ */