/*
 * USCI_A0_UART.c
 *
 *  Created on: 2021年1月19日
 *      Author: www14
 */
#include "stdio.h"
#include "string.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
/*******************************************************************************/
void usci_a0_uart_init(void) //UART_A0初始化函数
{
    P1SEL0 |= BIT2 | BIT3; //   将P1.2,P1.3复用为 UART_A0的引脚
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31); // 使能eUSCIA0中断

    UCA0CTLW0 |= UCSWRST; //软件复位使能位 **只有当UCSWRST=1才允许对UCA0CTLW0部分位进行操作
    UCA0CTLW0 |= UCSSEL__SMCLK;             //UART_A0时钟源选择为SMCLK，之前已经初始化为MCLK=SMCLK=48MHz

    /* 波特率计算方法
     *时钟频率 / (16 * 波特率) = xxxx
     */
    UCA0BR0 = 156;             // 48000000/16*19200=156
    UCA0BR1 = 0x00;
    UCA0MCTLW = 0x1000 | UCOS16 | 0x0020;                           //调制控制字寄存器,——_——咱也不懂，也不敢问
    UCA0CTLW0 &= ~UCSWRST;                  // 初始化完成后锁死
    UCA0IE |= UCRXIE;                  //启用UART_A0分中断
}

/*******************************************************************************/
/* Standard Includes */
//用于printf函数串口打印，可便于调试程序
/*******************************************************************************/
//一个字符
int fputc(int _c, register FILE *_fp)
{
    while (!(UCA0IFG & UCTXIFG))
        //UCTXIFG在UCA0TXBUF空时=1

        ;
    UCA0TXBUF = (unsigned char) _c;
    return 0;
}
//一个字符串
int fputs(const char *_ptr, register FILE *_fp)
{
    if ((*_ptr) != '\0')                  //如果字符串没有发送完
    {
        while (!(UCA0IFG & UCTXIFG))
            //如果一个字符没有发送完
            ;
        UCA0TXBUF = (unsigned char) *_ptr;
        _ptr++;
    }
    return 0;
}

