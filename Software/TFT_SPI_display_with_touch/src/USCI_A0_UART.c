/*
 * USCI_A0_UART.c
 *
 *  Created on: 2021��1��19��
 *      Author: www14
 */
#include "stdio.h"
#include "string.h"
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
/*******************************************************************************/
void usci_a0_uart_init(void) //UART_A0��ʼ������
{
    P1SEL0 |= BIT2 | BIT3; //   ��P1.2,P1.3����Ϊ UART_A0������
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31); // ʹ��eUSCIA0�ж�

    UCA0CTLW0 |= UCSWRST; //�����λʹ��λ **ֻ�е�UCSWRST=1�������UCA0CTLW0����λ���в���
    UCA0CTLW0 |= UCSSEL__SMCLK;             //UART_A0ʱ��Դѡ��ΪSMCLK��֮ǰ�Ѿ���ʼ��ΪMCLK=SMCLK=48MHz

    /* �����ʼ��㷽��
     *ʱ��Ƶ�� / (16 * ������) = xxxx
     */
    UCA0BR0 = 156;             // 48000000/16*19200=156
    UCA0BR1 = 0x00;
    UCA0MCTLW = 0x1000 | UCOS16 | 0x0020;                           //���ƿ����ּĴ���,����_������Ҳ������Ҳ������
    UCA0CTLW0 &= ~UCSWRST;                  // ��ʼ����ɺ�����
    UCA0IE |= UCRXIE;                  //����UART_A0���ж�
}

/*******************************************************************************/
/* Standard Includes */
//����printf�������ڴ�ӡ���ɱ��ڵ��Գ���
/*******************************************************************************/
//һ���ַ�
int fputc(int _c, register FILE *_fp)
{
    while (!(UCA0IFG & UCTXIFG))
        //UCTXIFG��UCA0TXBUF��ʱ=1

        ;
    UCA0TXBUF = (unsigned char) _c;
    return 0;
}
//һ���ַ���
int fputs(const char *_ptr, register FILE *_fp)
{
    if ((*_ptr) != '\0')                  //����ַ���û�з�����
    {
        while (!(UCA0IFG & UCTXIFG))
            //���һ���ַ�û�з�����
            ;
        UCA0TXBUF = (unsigned char) *_ptr;
        _ptr++;
    }
    return 0;
}

