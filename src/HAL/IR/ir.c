
#include "../../MCAL/DIO/dio.h"
#include "../../Lib/BIT_Math.h"
#include "ir.h"

void IR_Init(pin_config_t* irObj){
    DIO_Init(irObj);
}

uint8 IR_ReadValue(pin_config_t* irOb){
    return DIO_GetPinLogic(PINC, irOb->pin);
}