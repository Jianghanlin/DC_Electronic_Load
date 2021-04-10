/*
 * device.c
 *
 *  Created on: 2020年11月23日
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
    usci_b0_spi_init(); //硬件SPI初始化函数，必须写在最前面，因为之后的函数需要用到SPI引脚的功能
    LCD_Init();
    TP_Init(); //使用之前先校准

    DS18B20_Init(); //DS18B20初始化

    usci_a0_uart_init(); //串口输出初始化

    DAC8571_Init(); //片外16位DA初始化

    ADS1118_Init(); //片外16位AD初始化

    // key_init(); //按键初始化

    alarm_init(); //报警装置初始化

    MAX4662_init(); //控制模拟开关MAX4662的IO引脚初始化

    relay_init(); //继电器初始化

    fan_init(); //散热风扇初始化
    MAP_Interrupt_setPriority(INT_EUSCIB0, 0x20); //此处使用NVIC嵌套中段向量解决默认按键检测会打乱SPI的时序，将USCI_B0的时序设置得比WDT高
    // MAP_Interrupt_setPriority(INT_WDT_A, 0x40);
    MAP_Interrupt_setPriority(INT_TA0_0, 0x30);
}

