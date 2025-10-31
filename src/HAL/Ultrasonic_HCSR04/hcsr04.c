/*
 * rcsr04.c
 *
 * Created: 10/26/2025
 * Author: Ehab
 */

#include "../../Lib/SystemConfig.h"
#include "../../Lib/STD_Types.h"
#include "../../Lib/BIT_Math.h"
#include "../../MCAL/Timer0/timer0.h"
#include "hcsr04.h"

#define ULTRASONIC_TIMEOUT		 252
#define SPEED_OF_SOUND_CM_PER_US 0.0686f

void Ultrasonic_Init(ultrasonic_t *obj)
{
	DIO_Init(&(obj->trigger));
	DIO_Init(&(obj->echo));
}

uint16 Ultrasonic_Calculate_Distance(ultrasonic_t *obj)
{
    uint16_t distance = 0, ovfCount = 0;
    uint8_t echoRecTime = 0;

	obj->trigger.logic = DIO_HIGH;
	DIO_SetPinValue(&(obj->trigger));
	_delay_us(10);
	obj->trigger.logic = DIO_LOW;
	DIO_SetPinValue(&(obj->trigger));

    uint32_t timeout = 40000;
    while (DIO_LOW == DIO_GetPinLogic(&obj->echo)) {
        if (--timeout == 0) return 0;
    }

	Timer0_Init();
    ovfCount = 0;

    while (DIO_HIGH == DIO_GetPinLogic(&obj->echo)) {
        if (Timer0_CheckOverFlow()) {
            Timer0_ClearOverFlowFlag();  // clear the flag "by writing 1 in it"
            ovfCount++;
            if (ovfCount > ULTRASONIC_TIMEOUT) {  // bad reading
                Timer0_WriteValue(0);
                return 0;
            }
        }
    }

    // capture timer value
    echoRecTime = Timer0_ReadValue();
    Timer0_WriteValue(0);

    uint32_t total_ticks = ((uint32_t)ovfCount * 256UL) + echoRecTime;

    distance = (total_ticks * SPEED_OF_SOUND_CM_PER_US);
    return distance;
}