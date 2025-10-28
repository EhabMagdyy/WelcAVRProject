/*
 * timer.h
 *
 * Created: 10/21/2025 12:00:00 PM
 *  Author: Ehab
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../../Lib/STD_Types.h"

typedef enum {
    TIMER0_NORMAL = 0,
    TIMER0_PWM_PHASE_CORRECT = 1,
    TIMER0_CTC = 2,
    TIMER0_FAST_PWM = 3
} TIMER0_Mode_t;

typedef enum {
    TIMER0_NO_CLOCK = 0,
    TIMER0_PRESCALER_1 = 1,
    TIMER0_PRESCALER_8 = 2,
    TIMER0_PRESCALER_64 = 3,
    TIMER0_PRESCALER_256 = 4,
    TIMER0_PRESCALER_1024 = 5
} TIMER0_Prescaler_t;

typedef enum {
    TIMER0_OC_DISCONNECTED = 0,
    TIMER0_OC_TOGGLE = 1,
    TIMER0_OC_CLEAR = 2,
    TIMER0_OC_SET = 3
} TIMER0_OC_Mode_t;

typedef struct {
    TIMER0_Mode_t mode;
    TIMER0_Prescaler_t prescaler;
    TIMER0_OC_Mode_t oc_mode;
    uint8 initial_value;
    uint8 compare_value;
    uint8 enable_overflow_interrupt : 1;
    uint8 enable_compare_interrupt : 1;
} TIMER0_Config_t;

void TIMER0_Init(TIMER0_Config_t config);
void TIMER0_Delay_10us(void);
void TIMER0_WriteValue(uint8 value);
uint8 TIMER0_ReadValue(void);

#endif /* TIMER_H_ */