/*
 * display_voltage.h
 *
 *  Created on: 2021��1��19��
 *      Author: www14
 */

#ifndef SRC_DISPLAY_VOLTAGE_H_
#define SRC_DISPLAY_VOLTAGE_H_

extern void monitor_voltage_CC();   //��ѹ��غ��������������x,y,�˿�,���̣�
extern void monitor_voltage_CV();   //��ѹ��غ��������������x,y,�˿�,���̣�
extern void monitor_voltage_CR();   //��ѹ��غ��������������x,y,�˿�,���̣�
extern void monitor_voltage_Developer();
extern void monitor_voltage_CP();
extern volatile float dac8571_out; //�û��趨ֵ���,����������ʾ���ϵ��û�ֵ
extern volatile float ADC1_feedback; //ADC1�ĵ�ѹ����ֵ
extern volatile float ADC2_feedback; //ADC2�ĵ�ѹ����ֵ
extern volatile float ADC3_feedback; //ADC3�ĵ�ѹ����ֵ
extern volatile float CC_value; //����ģʽ�趨ֵ����λA
extern volatile float CC_value_fact; //����ģʽʵ��ֵ����λA
extern volatile float CV_value; //��ѹģʽ�趨ֵ����λV
extern volatile float CV_value_fact; //����ģʽʵ��ֵ����λV
extern volatile float CR_value; //����ģʽ�趨ֵ����λR
extern volatile float CP_value; //�㹦��ģʽ�趨ֵ����λW
#endif /* SRC_DISPLAY_VOLTAGE_H_ */
