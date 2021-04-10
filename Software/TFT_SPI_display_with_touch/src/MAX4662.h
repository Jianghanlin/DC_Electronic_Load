/*
 * MAX4662.h
 *
 *  Created on: 2021Äê3ÔÂ12ÈÕ
 *      Author: jianghanlin
 */

#ifndef SRC_MAX4662_H_
#define SRC_MAX4662_H_

#define DA_IN_off P8OUT &= ~(BIT6 + BIT5 )
#define CV_Mode_DA_IN_on P8OUT |=BIT6
#define CC_Mode_DA_IN_on P8OUT |=BIT5
extern void MAX4662_init();

#endif /* SRC_MAX4662_H_ */
