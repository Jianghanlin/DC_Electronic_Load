/*
 * DS18B20.h
 *
 *  Created on: 2015年11月21日
 *      Author: Administrator
 */

#ifndef DS18B20_H_
#define DS18B20_H_
//DS18B20控制引脚定义
#define  DQ_OUT     P8DIR|=BIT7
#define  DQ_IN      P8DIR&=~BIT7
#define  DQ_H       P8OUT|=BIT7
#define  DQ_L       P8OUT&=~BIT7
#define  DQ_DATE    (P8IN&BIT7)
//DS18B20 ROM命令宏定义
#define ReadRom                     0x33
#define MatchRom                    0x55
#define SearchRom                   0xf0
#define AlertSearch                 0xec
#define CopyScratchpad              0x48
#define SkipRom                     0xcc
#define ReadPower                   0xb4
//DS18B20功能命令宏定义
#define ConvertTemperature          0x44
#define ReadScratchpad              0xbe
#define WriteScratchpad             0x4e
#define RecallE                     0xb8

short DS18B20_ReadTemp(void);
void DS18B20_WriteByte(unsigned char Data);
extern unsigned char DS18B20_Init(void);
extern void display_temperature();
extern unsigned short mos_temp;

#endif /* DS18B20_H_ */
