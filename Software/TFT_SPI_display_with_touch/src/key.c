/*
 * key.c
 *
 *  Created on: 2020年11月23日
 *      Author: www14
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include "delay.h"
#include "key.h"
#include "DAC8571.h"
void key_init(void)
{
    P1DIR &= ~BIT1;
    P1REN |= BIT1;
    P1OUT |= BIT1;

    P2DIR &= ~(BIT4 + BIT6 + BIT7 );
    P2REN |= BIT4 + BIT6 + BIT7;
    P2OUT |= BIT4 + BIT6 + BIT7;

    P5DIR &= ~BIT6;
    P5REN |= BIT6;
    P5OUT |= BIT6;

    P1DIR |= BIT0;
    P1OUT &= ~ BIT0;

    P2DIR |= BIT0 + BIT1 + BIT2;
    P2OUT &= ~(BIT0 + BIT1 + BIT2 );
}

/*****************************************************************************
 * @name       :u8 KEY_Scan(void)
 * @date       :2018-08-09
 * @function   :Key processing,Response priority:KEY0>KEY1>WK_UP!!
 * @parameters :None
 * @retvalue   :0-No buttons were pressed.
 1-The KEY0 button is pressed
 2-The KEY1 button is pressed
 3-The WK_UP button is pressed
 ******************************************************************************/
uint8_t key_scan(void)
{
    if ((P1IN & BIT1 ) == 0)
    {
        delay_ms(10); //去抖动
        if ((P1IN & BIT1 ) == 0)
            return KEY0_PRES;
        else
            ;
    }

    return 0; // 无按键按下
}

void key_test() //检测事件确实发生了
{
    static unsigned char now = 0; //position用来保存选择指针的位置,jiemian用来保存跳转的界面级数,confirm用来记录KEY3的按键次数,hold用来检测是否启用长按函数
    unsigned char past = 0, key = 0; //key来区别那个按键按下,i用来记录长按的时间
    past = now;
    if ((P2IN & BIT7 ) == 0)
    {
        key = 1;
        now = 0;
    }
    else if ((P2IN & BIT6 ) == 0)
    {
        key = 2;
        now = 0;
    }
    else if ((P2IN & BIT4 ) == 0)
    {
        key = 3;
        now = 0;
    }
    else if ((P5IN & BIT6 ) == 0)
    {
        key = 4;
        now = 0;
    }
    else
        now = 1;
    if ((past == 1) && (now == 0))
    {
        switch (key)
        {
        case 1:
            P1OUT ^= BIT0;
            //voltage += 0.01;
            break;
        case 2:
            P2OUT ^= BIT0;
            break;
        case 3:
            P2OUT ^= BIT1;
            break;
        case 4:
            P2OUT ^= BIT2;
            break;
        }
        // DAC8571_OUT(voltage);
    }
    else
        ;
}
