/*
 * rcsr04.c
 *
 * Created: 10/26/2025
 * Author: Ehab
 */

#include "../../Lib/SystemConfig.h"
#include "../../Lib/STD_Types.h"
#include "../../MCAL/DIO/dio.h"
#include <avr/io.h>
#include <util/delay.h>
#include "rcsr04.h"

// Timer0 prescaler = 8 → tick = 0.5 µs @ 16 MHz
#define ULTRASONIC_TIMEOUT_OVERFLOWS 250  // safety limit (~65ms)
#define SPEED_OF_SOUND_CM_PER_US 0.0343f

#define ULTRASONIC_TRIG_PIN PB1
#define ULTRASONIC_ECHO_PIN PB2

void Ultrasonic_Init(ultrasonic_t *obj)
{
	DIO_Init(obj->trigger);
	DIO_Init(obj->echo);
}

uint16 Ultrasonic_Calculate_Distance(ultrasonic_t *obj)
{
    uint16_t overflow_count = 0;
    uint8_t timer_end;

	obj->trigger.logic = DIO_HIGH;
	DIO_SetPinValue(obj->trigger);
	_delay_us(10);
	obj->trigger.logic = DIO_LOW;
	DIO_SetPinValue(obj->trigger);

    // --- Wait for ECHO rising edge ---
    uint32_t timeout = 40000;
    while (!(PINB & (1 << ULTRASONIC_ECHO_PIN))) {
        if (--timeout == 0) return 0;
    }

     // --- Setup Timer0 ---
    TCCR0A = 0;
    TCCR0B = (1 << CS01) | (1 << CS00);   // prescaler 64 → 4 µs per tick @16MHz
    TCNT0 = 0;
    overflow_count = 0;

    // --- Measure HIGH pulse ---
    while (PINB & (1 << ULTRASONIC_ECHO_PIN)) {
        if (TIFR0 & (1 << TOV0)) { // overflow flag set
            TIFR0 |= (1 << TOV0);  // clear it
            overflow_count++;
            if (overflow_count > 250) { // safety limit
                TCCR0B = 0;
                return 0;
            }
        }
    }

    // --- Stop timer and capture count ---
    timer_end = TCNT0;
    TCCR0B = 0;

    // --- Compute total ticks (including overflows) ---
    uint32_t total_ticks = ((uint32_t)overflow_count * 256UL) + timer_end;

    // --- Convert to distance ---
    // tick = 4 µs → time = total_ticks * 4
    // distance (cm) = time * 0.0343 / 2
    float distance = (total_ticks * 4.0f * 0.0343f) / 2.0f;
    return (uint16_t)distance;
}