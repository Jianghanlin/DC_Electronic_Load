/*
 * relay.h
 *
 *  Created on: 2021Äê3ÔÂ12ÈÕ
 *      Author: jianghanlin
 */

#ifndef SRC_RELAY_H_
#define SRC_RELAY_H_
#define switch_load_voltage_to_CC P9OUT &= ~BIT0
#define switch_load_voltage_to_CV P9OUT |=BIT0
extern void relay_init();

#endif /* SRC_RELAY_H_ */
