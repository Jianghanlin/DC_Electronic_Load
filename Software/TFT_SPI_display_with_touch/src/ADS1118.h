/*
 * ads1118.h
 *
 *  Created on: 2018-05-17 11:23
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_DRIVER_ADS1118_H_
#define INC_DRIVER_ADS1118_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#define uint  unsigned int
#define uchar unsigned char
#define SCLK_H P5OUT |= BIT1
#define SCLK_L P5OUT &= ~BIT1
#define CS_H   P5OUT |= BIT0
#define CS_L   P5OUT &= ~BIT0
#define DataIN_H  P5OUT |= BIT2
#define DataIN_L  P5OUT &= ~BIT2
#define ADS1118_OUT  P3IN&BIT5

extern void ADS1118_Init();
extern float average_voltage_caculate(unsigned char channel, unsigned char times); //传入参数为通道号和采样次数
#endif /* INC_DRIVER_ADS1118_H_ */
