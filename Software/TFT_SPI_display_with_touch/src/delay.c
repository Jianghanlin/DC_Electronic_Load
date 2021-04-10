/*
 * delay.c
 *
 *  Created on: 2020年11月22日
 *      Author: www14
 */
#include "ti/devices/msp432p4xx/inc/msp.h"
#include <stdint.h>

static uint8_t fac_us = 0; //us延时倍乘数
static uint16_t fac_ms = 0; //ms延时倍乘数

//初始化延迟函数,传入参数是系统时钟MCLK，单位MHz
void delay_init(uint8_t SYSCLK)
{
    fac_us = SYSCLK; //单位位MHz,所以直接赋值是us
    fac_ms = (uint16_t) fac_us * 1000; //ms=us*1000
}

//SysTick->LOAD为24位寄存器,所以,最大延时为:2^24/MCLK=2^24/48000000=349525us=349.525ms
void delay_ms(uint16_t ms)
{
    uint32_t temp;
    SysTick->LOAD = (uint32_t) ms * fac_ms;   //时间加载(SysTick->LOAD为24bit)
    SysTick->VAL = 0x00;           //清空计数器
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;           //使能Systick并且打开时钟源
    do
    {
        temp = SysTick->CTRL;           //将整个32位寄存器SysTick control and status register (STK_CTRL)赋值给temp
    }
    while (temp & 0x01 && !(temp & (1 << 16)));          //等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;       //关闭计数器
    SysTick->VAL = 0X00;       //清空计数器
}

//SysTick->LOAD为24位寄存器,所以,最大延时为:2^24/MCLK=2^24/48000000=349525us=349.525ms
void delay_us(uint32_t us)
{
    uint32_t temp;
    SysTick->LOAD = us * fac_us; //时间加载
    SysTick->VAL = 0x00;        //清空计数器
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk; //使能Systick并且打开时钟源
    do
    {
        temp = SysTick->CTRL; //将整个32位寄存器SysTick control and status register (STK_CTRL)赋值给temp
    }
    while (temp & 0x01 && !(temp & (1 << 16)));      //等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;       //关闭计数器
    SysTick->VAL = 0X00;       //清空计数器
}
