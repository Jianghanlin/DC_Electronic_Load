/*
 * bee.c
 *
 *  Created on: 2021年3月5日
 *      Author: jianghanlin
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void alarm_init()
{
    P2DIR |= BIT0;
    P2OUT &= ~BIT0; //led报警


    P5DIR |= BIT7;
    P5OUT |= BIT7; //蜂鸣器报警
}

