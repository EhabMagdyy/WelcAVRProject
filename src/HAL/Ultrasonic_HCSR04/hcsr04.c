/*
 * hcsr04.c
 *
 * Created: 10/26/2025
 * Author: Ehab
 */

#include "../../Lib/SystemConfig.h"
#include "../../Lib/STD_Types.h"
#include "../../Lib/BIT_Math.h"
#include "../../MCAL/Timer0/timer0.h"
#include "../../MCAL/UART/uart.h"
#include "hcsr04.h"

#define ULTRASONIC_TIMEOUT         40
#define SPEED_OF_SOUND_CM_PER_US   0.0343f
#define TIMER0_TICK_US             4.0f
#define HISTORY_SIZE               3

static uint16 Ultrasonic_Single_Read(ultrasonic_t *obj);

uint16 Ultrasonic_Calculate_Distance(ultrasonic_t *obj)
{
    static uint16 history[HISTORY_SIZE] = {0};
    static uint8 filled = 0;
    static uint8 index = 0;
    static uint16 lastValid = 0;

    uint16 newReading = Ultrasonic_Single_Read(obj);

    if (newReading == 0) {
        if (lastValid != 0)
            return lastValid;
        else
            return 0;     
    }

    if (filled < HISTORY_SIZE) {
        history[filled++] = newReading;
        if (filled < HISTORY_SIZE)
            return 0;
    }

    history[index++] = newReading;
    if (index >= HISTORY_SIZE)
        index = 0;

    uint32 sum = 0;
    for (uint8 i = 0; i < HISTORY_SIZE; i++)
        sum += history[i];

    uint16 avg = (uint16)(sum / HISTORY_SIZE);
    lastValid = avg;

    return avg;
}

static uint16 Ultrasonic_Single_Read(ultrasonic_t *obj)
{
    uint16_t distance = 0, ovfCount = 0;
    uint8_t echoRecTime = 0;

    obj->trigger.logic = DIO_HIGH;
    DIO_SetPinValue(&(obj->trigger));
    _delay_us(10);
    obj->trigger.logic = DIO_LOW;
    DIO_SetPinValue(&(obj->trigger));

    uint32_t timeout = 40000;
    while (DIO_LOW == DIO_GetPinLogic(PINB, PIN2)) {
        if (--timeout == 0)
            return 0;
    }

    Timer0_Init();
    ovfCount = 0;

    while (DIO_HIGH == DIO_GetPinLogic(PINB, PIN2)) {
        if (Timer0_CheckOverFlow()) {
            Timer0_ClearOverFlowFlag();
            ovfCount++;
            if (ovfCount > ULTRASONIC_TIMEOUT) {
                Timer0_WriteValue(0);
                return 0;
            }
        }
    }

    echoRecTime = Timer0_ReadValue();
    Timer0_WriteValue(0);

    uint32_t total_ticks = ((uint32_t)ovfCount * 256UL) + echoRecTime;
    distance = ((float)total_ticks * TIMER0_TICK_US * SPEED_OF_SOUND_CM_PER_US) / 2.0f;

    return distance;
}
