/*
 * relay.c
 *
 *  Created on: 2021��3��12��
 *      Author: jianghanlin
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
void relay_init()
{
    P9DIR |= BIT0;
    P9OUT &= ~BIT0;
}

