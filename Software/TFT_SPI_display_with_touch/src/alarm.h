/*
 * bee.h
 *
 *  Created on: 2021Äê3ÔÂ5ÈÕ
 *      Author: jianghanlin
 */

#ifndef SRC_ALARM_H_
#define SRC_ALARM_H_

#define red_led_on P2OUT |=BIT0
#define red_led_off P2OUT &= ~BIT0
#define bee_on P5OUT &= ~ BIT7
#define bee_off P5OUT |= BIT7
extern void alarm_init();
#endif /* SRC_ALARM_H_ */
