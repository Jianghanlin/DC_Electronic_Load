/*
 * key.h
 *
 *  Created on: 2020��11��23��
 *      Author: www14
 */

#ifndef SRC_KEY_H_
#define SRC_KEY_H_
#include <stdint.h>

#define KEY0_PRES   1       //KEY0

extern void key_init(void); //IO��ʼ��
extern void key_test(void); //��������
extern uint8_t key_scan(void);      //����ɨ�躯��

#endif /* SRC_KEY_H_ */
