/*
 * fan.c
 *
 *  Created on: 2021Äê3ÔÂ12ÈÕ
 *      Author: jianghanlin
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
void fan_init()
{
    P9DIR |= BIT1;
    P9OUT &= ~BIT1;
}

