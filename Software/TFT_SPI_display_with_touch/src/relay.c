/*
 * relay.c
 *
 *  Created on: 2021Äê3ÔÂ12ÈÕ
 *      Author: jianghanlin
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
void relay_init()
{
    P9DIR |= BIT0;
    P9OUT &= ~BIT0;
}

