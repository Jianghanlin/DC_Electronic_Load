/*
 * fan.h
 *
 *  Created on: 2021Äê3ÔÂ12ÈÕ
 *      Author: jianghanlin
 */

#ifndef SRC_FAN_H_
#define SRC_FAN_H_
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#define fan_run P9OUT |=BIT1
#define fan_stop P9OUT &= ~BIT1
extern void fan_init();

#endif /* SRC_FAN_H_ */
