/*
 * delay.c
 *
 *  Created on: 2020��11��22��
 *      Author: www14
 */
#include "ti/devices/msp432p4xx/inc/msp.h"
#include <stdint.h>

static uint8_t fac_us = 0; //us��ʱ������
static uint16_t fac_ms = 0; //ms��ʱ������

//��ʼ���ӳٺ���,���������ϵͳʱ��MCLK����λMHz
void delay_init(uint8_t SYSCLK)
{
    fac_us = SYSCLK; //��λλMHz,����ֱ�Ӹ�ֵ��us
    fac_ms = (uint16_t) fac_us * 1000; //ms=us*1000
}

//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:2^24/MCLK=2^24/48000000=349525us=349.525ms
void delay_ms(uint16_t ms)
{
    uint32_t temp;
    SysTick->LOAD = (uint32_t) ms * fac_ms;   //ʱ�����(SysTick->LOADΪ24bit)
    SysTick->VAL = 0x00;           //��ռ�����
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;           //ʹ��Systick���Ҵ�ʱ��Դ
    do
    {
        temp = SysTick->CTRL;           //������32λ�Ĵ���SysTick control and status register (STK_CTRL)��ֵ��temp
    }
    while (temp & 0x01 && !(temp & (1 << 16)));          //�ȴ�ʱ�䵽��
    SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;       //�رռ�����
    SysTick->VAL = 0X00;       //��ռ�����
}

//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:2^24/MCLK=2^24/48000000=349525us=349.525ms
void delay_us(uint32_t us)
{
    uint32_t temp;
    SysTick->LOAD = us * fac_us; //ʱ�����
    SysTick->VAL = 0x00;        //��ռ�����
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk; //ʹ��Systick���Ҵ�ʱ��Դ
    do
    {
        temp = SysTick->CTRL; //������32λ�Ĵ���SysTick control and status register (STK_CTRL)��ֵ��temp
    }
    while (temp & 0x01 && !(temp & (1 << 16)));      //�ȴ�ʱ�䵽��
    SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;       //�رռ�����
    SysTick->VAL = 0X00;       //��ռ�����
}
