/*
 * bee.c
 *
 *  Created on: 2021��3��5��
 *      Author: jianghanlin
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void alarm_init()
{
    P2DIR |= BIT0;
    P2OUT &= ~BIT0; //led����


    P5DIR |= BIT7;
    P5OUT |= BIT7; //����������
}

