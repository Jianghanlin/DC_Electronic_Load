/*
 * MAX4662.c
 *
 *  Created on: 2021��3��12��
 *      Author: jianghanlin
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
void MAX4662_init()
{
    P8DIR |= BIT6 + BIT5;
    P8OUT &= ~(BIT6 + BIT5 );
}

