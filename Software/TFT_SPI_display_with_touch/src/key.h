/*
 * key.h
 *
 *  Created on: 2020年11月23日
 *      Author: www14
 */

#ifndef SRC_KEY_H_
#define SRC_KEY_H_
#include <stdint.h>

#define KEY0_PRES   1       //KEY0

extern void key_init(void); //IO初始化
extern void key_test(void); //按键测试
extern uint8_t key_scan(void);      //按键扫描函数

#endif /* SRC_KEY_H_ */
