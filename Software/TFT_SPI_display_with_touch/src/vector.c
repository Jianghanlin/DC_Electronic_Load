/*
 * vector.c
 *
 *  Created on: 2020年11月23日
 *      Author: www14
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "USCI_B0_SPI.h"
#include "USCI_A0_UART.h"
#include "key.h"
#include "DS18B20.h"
#include "alarm.h"
#include "fan.h"
#include  "delay.h"
void EUSCIA0_IRQHandler(void) //UART_A0的中断服务函数
{
    if (UCA0IFG & UCTXIFG) //如果此时发送完成，发送下一个字符
    {
        // UCA0IFG &= ~ UCTXIFG; //复位发送完成标志
    }
}

void TA0_0_IRQHandler(void)
{
    static char i = 0;
    // Clear the compare interrupt flag
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    if (mos_temp > 2500) //超出阈值报警
    {
        fan_run;
        red_led_on; //LED报警
        bee_on; //蜂鸣器报警
        delay_ms(50);
        bee_off;
        delay_ms(50);
        bee_on; //蜂鸣器报警
        delay_ms(50);
        bee_off;
    }
    else
    {
        i++;
        if (i == 254)
        {
            red_led_off;
            bee_off;
            fan_stop;
            i = 0;
        }
    }
}

void EUSCIB0_IRQHandler(void)
{
    if (UCB0IFG & UCRXIFG)
    {
        usci_b0_spi_rx_isr_handle();
    }
    if (UCB0IFG & UCTXIFG)
    {
        usci_b0_spi_tx_isr_handle();
    }
}

void WDT_A_IRQHandler(void)
{
    key_test();
}

