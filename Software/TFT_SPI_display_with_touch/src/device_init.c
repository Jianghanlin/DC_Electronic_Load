/*
 * device.c
 *
 *  Created on: 2020��11��23��
 *      Author: www14
 */

#include "ST7796S.h"
#include "ADS1118.h"
#include "USCI_B0_SPI.h"
#include "USCI_A0_UART.h"
#include "key.h"
#include "DAC8571.h"
#include "touch.h"
#include "DS18B20.h"
#include "alarm.h"
#include "MAX4662.h"
#include "relay.h"
#include "fan.h"
void device_init()
{
    usci_b0_spi_init(); //Ӳ��SPI��ʼ������������д����ǰ�棬��Ϊ֮��ĺ�����Ҫ�õ�SPI���ŵĹ���
    LCD_Init();
    TP_Init(); //ʹ��֮ǰ��У׼

    DS18B20_Init(); //DS18B20��ʼ��

    usci_a0_uart_init(); //���������ʼ��

    DAC8571_Init(); //Ƭ��16λDA��ʼ��

    ADS1118_Init(); //Ƭ��16λAD��ʼ��

    // key_init(); //������ʼ��

    alarm_init(); //����װ�ó�ʼ��

    MAX4662_init(); //����ģ�⿪��MAX4662��IO���ų�ʼ��

    relay_init(); //�̵�����ʼ��

    fan_init(); //ɢ�ȷ��ȳ�ʼ��
    MAP_Interrupt_setPriority(INT_EUSCIB0, 0x20); //�˴�ʹ��NVICǶ���ж��������Ĭ�ϰ����������SPI��ʱ�򣬽�USCI_B0��ʱ�����õñ�WDT��
    // MAP_Interrupt_setPriority(INT_WDT_A, 0x40);
    MAP_Interrupt_setPriority(INT_TA0_0, 0x30);
}

