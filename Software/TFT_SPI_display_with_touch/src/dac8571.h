/*
 * dac8571.h
 *
 *  Created on: 2018-05-17 20:43
 *      Author: Jack Chen <redchenjs@live.com>
 */

/*#ifndef INC_DRIVER_DAC8571_H_
 #define INC_DRIVER_DAC8571_H_

 #include <stdint.h>

 extern void dac8571_set_output(uint16_t value);
 extern void dac8571_init(void);

 #endif  INC_DRIVER_DAC8571_H_ */

#ifndef DAC8571_H_
#define DAC8571_H_

#define VREF 3.295//实际的基准电压

#define SCL_H P3OUT |= BIT7 //IIC
#define SDA_H P3OUT |=BIT6   //IIC
#define SCL_L P3OUT &= ~BIT7  //IIC
#define SDA_L P3OUT &= ~BIT6   //IIC
#define SDA_DIRIN  P3DIR &= ~BIT6
#define SDA_DIROUT P3DIR |= BIT6
#define SDA_IN  P3IN&=BIT6

extern void DAC8571_Init(void);
extern void DAC8571_OUT(float num);

#endif /* DAC8571_H_ */
