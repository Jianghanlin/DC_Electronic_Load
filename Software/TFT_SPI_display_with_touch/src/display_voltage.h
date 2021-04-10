/*
 * display_voltage.h
 *
 *  Created on: 2021年1月19日
 *      Author: www14
 */

#ifndef SRC_DISPLAY_VOLTAGE_H_
#define SRC_DISPLAY_VOLTAGE_H_

extern void monitor_voltage_CC();   //电压监控函数，传入参数（x,y,端口,量程）
extern void monitor_voltage_CV();   //电压监控函数，传入参数（x,y,端口,量程）
extern void monitor_voltage_CR();   //电压监控函数，传入参数（x,y,端口,量程）
extern void monitor_voltage_Developer();
extern void monitor_voltage_CP();
extern volatile float dac8571_out; //用户设定值输出,用来保存显示屏上的用户值
extern volatile float ADC1_feedback; //ADC1的电压采样值
extern volatile float ADC2_feedback; //ADC2的电压采样值
extern volatile float ADC3_feedback; //ADC3的电压采样值
extern volatile float CC_value; //恒流模式设定值，单位A
extern volatile float CC_value_fact; //恒流模式实际值，单位A
extern volatile float CV_value; //恒压模式设定值，单位V
extern volatile float CV_value_fact; //恒流模式实际值，单位V
extern volatile float CR_value; //恒阻模式设定值，单位R
extern volatile float CP_value; //恒功率模式设定值，单位W
#endif /* SRC_DISPLAY_VOLTAGE_H_ */
