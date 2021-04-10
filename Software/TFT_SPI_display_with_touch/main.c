/*
 * @Author: jianghanlin 
 * @Date: 2021-03-07 11:12:59 
 * @Last Modified by:   jianghanlin 
 * @Last Modified time: 2021-03-07 11:12:59 
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdio.h>
#include "system_init.h"
#include "device_init.h"
#include "ST7796S.h"
#include "ADS1118.h"
#include "GUI.h"
int main(void)
{
    WDT_A_holdTimer(); //关狗
    system_init();     //MSP432P401R初始化
    device_init();     //外设初始化
    MAP_Interrupt_enableMaster(); //打开总中断
    //CR_Mode();
    draw_start();
    //Developer_Mode();
}

