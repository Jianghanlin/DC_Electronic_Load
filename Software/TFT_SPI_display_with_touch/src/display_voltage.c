/*
 * display_voltage.c
 *
 *  Created on: 2021��1��19��
 *      Author: www14
 */
#include <stdio.h>
#include <stdint.h>
#include "ST7796S.h"
#include "ADS1118.h"
#include "dac8571.h"
volatile float dac8571_out = 0; //�û��趨ֵ���,����������ʾ���ϵ��û�ֵ
volatile float ADC1_feedback = 0; //ADC1�ĵ�ѹ����ֵ
volatile float ADC2_feedback = 0; //ADC2�ĵ�ѹ����ֵ
volatile float ADC3_feedback = 0; //ADC3�ĵ�ѹ����ֵ
volatile float CC_value = 0; //����ģʽ�趨ֵ����λA
volatile float CC_value_fact = 0; //����ģʽ�趨ֵ����λA
volatile float CV_value = 0; //��ѹģʽ�趨ֵ����λV
volatile float CV_value_fact = 0; //��ѹģʽ�趨ֵ����λV
volatile float CR_value = 0; //����ģʽ�趨ֵ����λR
volatile float CP_value = 0; //�㹦��ģʽ�趨ֵ����λW

void monitor_voltage_CC()    //��ѹ��غ��������������x,y,�˿�,���̣�
{
    char test[10] = { };

    sprintf(test, "%.3f", dac8571_out);
    //   printf("DAC8571_userset=%s  ", test);    //��س�����DAC8571���û��趨ֵ

    sprintf(test, "%.4f", average_voltage_caculate(4, 5));
    LCD_ShowString(140, 210, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ADS118:ͨ��A0,ʵ�����Ǽ��DAC8571��ʵ�����ֵ,��ʾ��TFT��

    ADC1_feedback = average_voltage_caculate(5, 5);
    ADC1_feedback = 0.0331 * ADC1_feedback * ADC1_feedback + 6.6995 * ADC1_feedback + 0.054; //���ص�ѹ����ADC1����������

    /*****************************************************************************************/
    /*��������ʱʹ��*/
    //   sprintf(test, "%.4f", ADC1_feedback);
    //   printf("ADC1=%s  \n\r", test); //ADC1�����ֵ���������������
    /*****************************************************************************************/
    sprintf(test, "%.4f", ADC1_feedback);
    LCD_ShowString(350, 250, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ADS118:ͨ��A1,ʵ�����Ǽ��ADC1�����ֵ,��ʾ��TFT��,��ظ��ص�ѹ

    ADC2_feedback = average_voltage_caculate(6, 5);
    CC_value_fact = -0.0071 * ADC2_feedback * ADC2_feedback + 0.9383 * ADC2_feedback - 0.0245; //ʵ�ʵ���ֵ����ADC2����������
    sprintf(test, "%.4f", CC_value_fact);
    LCD_ShowString(350, 219, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ʵ�ʵ���ֵ
}

void monitor_voltage_CV()    //��ѹ��غ��������������x,y,�˿�,���̣�
{
    char test[10] = { };

    /*
     sprintf(test, "%.3f", dac8571_out);
     printf("DAC8571_userset=%s  ", test);    //��س�����DAC8571���û��趨ֵ
     */

    sprintf(test, "%.4f", average_voltage_caculate(4, 5));
    LCD_ShowString(140, 210, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ADS118:ͨ��A0,ʵ�����Ǽ��DAC8571��ʵ�����ֵ,��ʾ��TFT��
    //printf("DAC8571_fact=%s  ", test);    //DAC8571��ʵ�����ֵ���������������

    ADC3_feedback = average_voltage_caculate(7, 5);
    ADC3_feedback = 0.9091 * ADC3_feedback * ADC3_feedback + 2.5199 * ADC3_feedback + 0.2203;    //ʵ�ʺ�ѹֵ����ADC3����������
    sprintf(test, "%.4f", ADC3_feedback);
    LCD_ShowString(350, 250, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //��غ�ѹ��ѹֵ
    /*****************************************************************************************/
    /*��������ʱʹ��*/
    // printf("ADC3=%s  \n\r", test); //ADC3�����ֵ���������������
    //LCD_ShowString(116, 241, WHITE, BLACK, 16, (uint8_t*) test, 0, 0);
    /*****************************************************************************************/

}

void monitor_voltage_CR()    //��ѹ��غ��������������x,y,�˿�,���̣�
{
    char test[10] = { };

    /*
     sprintf(test, "%.3f", dac8571_out);
     printf("DAC8571_userset=%s  ", test);    //��س�����DAC8571���û��趨ֵ
     */

    sprintf(test, "%.4f", average_voltage_caculate(4, 5));
    LCD_ShowString(140, 210, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ADS118:ͨ��A0,ʵ�����Ǽ��DAC8571��ʵ�����ֵ,��ʾ��TFT��

    ADC1_feedback = average_voltage_caculate(5, 5);
    ADC1_feedback = 0.0331 * ADC1_feedback * ADC1_feedback + 6.6995 * ADC1_feedback + 0.054; //���ص�ѹ����ADC1����������
    sprintf(test, "%.4f", ADC1_feedback);

    /*****************************************************************************************/
    /*��������ʱʹ��*/
    printf("----------------------\n"); //ADC1�����ֵ���������������
    printf("ADC1=%s  ", test); //ADC1�����ֵ���������������
    /*****************************************************************************************/

    LCD_ShowString(350, 250, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //��ظ��ص�ѹ

    ADC2_feedback = average_voltage_caculate(6, 5);
    ADC2_feedback = -0.0071 * ADC2_feedback * ADC2_feedback + 0.9383 * ADC2_feedback - 0.0245;    //ʵ�ʵ���ֵ����ADC2����������
    sprintf(test, "%.4f", ADC2_feedback);

    /*****************************************************************************************/
    /*��������ʱʹ��*/
    //printf("I=%s  \n\r", test); //ADC1�����ֵ���������������
    /*****************************************************************************************/

    LCD_ShowString(350, 219, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ʵ�ʵ���ֵ
}

void monitor_voltage_Developer()    //��ѹ��غ��������������x,y,�˿�,���̣�
{
    char test[10] = { };

    sprintf(test, "%.3f", dac8571_out);
    printf("DAC8571_userset=%s  ", test);    //��س�����DAC8571���û��趨ֵ

    sprintf(test, "%.4f", average_voltage_caculate(4, 5));
    LCD_ShowString(140, 210, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ADS118:ͨ��A0,ʵ�����Ǽ��DAC8571��ʵ�����ֵ,��ʾ��TFT��
    printf("DAC8571_fact=%s  ", test);    //DAC8571��ʵ�����ֵ���������������

    ADC1_feedback = average_voltage_caculate(5, 5);
    sprintf(test, "%.4f", ADC1_feedback);
    LCD_ShowString(116, 241, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ADS118:ͨ��A1,ʵ�����Ǽ��ADC1�����ֵ,��ʾ��TFT��
    printf("ADC1=%s  ", test); //ADC1�����ֵ���������������

    ADC1_feedback = -0.0007 * ADC1_feedback * ADC1_feedback + 6.7863 * ADC1_feedback - 0.0142; //���ص�ѹ����ADC1����������6.6V~14.74V

    sprintf(test, "%.4f", ADC1_feedback);
    LCD_ShowString(350, 250, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //��ظ��ص�ѹ

    ADC2_feedback = average_voltage_caculate(6, 5);
    sprintf(test, "%.4f", ADC2_feedback);
    LCD_ShowString(116, 272, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ADS118:ͨ��A2,ʵ�����Ǽ��ADC2�����ֵ,��ʾ��TFT��
    printf("ADC2=%s  \n\r", test); //ADC2�����ֵ���������������
    //ADC2_feedback = -0.0073 * ADC2_feedback * ADC2_feedback + 0.9247 * ADC2_feedback - 0.0015;    //ʵ�ʵ���ֵ����ADC2����������
    //sprintf(test, "%.4f", ADC2_feedback);
    //LCD_ShowString(350, 219, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ʵ�ʵ���ֵ
}

void monitor_voltage_CP()    //��ѹ��غ��������������x,y,�˿�,���̣�
{
    char test[10] = { };

    sprintf(test, "%.4f", average_voltage_caculate(4, 5));
    LCD_ShowString(140, 210, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ADS118:ͨ��A0,ʵ�����Ǽ��DAC8571��ʵ�����ֵ,��ʾ��TFT��

    ADC1_feedback = average_voltage_caculate(5, 5);
    ADC1_feedback = 0.0331 * ADC1_feedback * ADC1_feedback + 6.6995 * ADC1_feedback + 0.054; //���ص�ѹ����ADC1����������
    sprintf(test, "%.4f", ADC1_feedback);
    LCD_ShowString(350, 250, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //��ظ��ص�ѹ

    ADC2_feedback = average_voltage_caculate(6, 5);
    ADC2_feedback = -0.0071 * ADC2_feedback * ADC2_feedback + 0.9383 * ADC2_feedback - 0.0245;    //ʵ�ʵ���ֵ����ADC2����������
    sprintf(test, "%.4f", ADC2_feedback);
    LCD_ShowString(350, 219, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //���ʵ�ʵ���ֵ
}
