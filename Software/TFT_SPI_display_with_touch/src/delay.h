/*
 * @Author: mikey.zhaopeng 
 * @Date: 2021-01-02 16:13:18 
 * @Last Modified by: mikey.zhaopeng
 * @Last Modified time: 2021-01-02 16:13:40
 */
/*
 * delay.h
 *
 *  Created on: 2020Äê11ÔÂ22ÈÕ
 *      Author: www14
 */

#ifndef SRC_DELAY_H_
#define SRC_DELAY_H_
#include <stdint.h>
extern void delay_init(uint8_t SYSCLK);
extern void delay_ms(uint16_t nms);
extern void delay_us(uint32_t nus);

#endif /* SRC_DELAY_H_ */
