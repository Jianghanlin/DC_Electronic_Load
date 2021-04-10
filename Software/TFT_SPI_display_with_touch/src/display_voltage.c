/*
 * display_voltage.c
 *
 *  Created on: 2021年1月19日
 *      Author: www14
 */
#include <stdio.h>
#include <stdint.h>
#include "ST7796S.h"
#include "ADS1118.h"
#include "dac8571.h"
volatile float dac8571_out = 0; //用户设定值输出,用来保存显示屏上的用户值
volatile float ADC1_feedback = 0; //ADC1的电压采样值
volatile float ADC2_feedback = 0; //ADC2的电压采样值
volatile float ADC3_feedback = 0; //ADC3的电压采样值
volatile float CC_value = 0; //恒流模式设定值，单位A
volatile float CC_value_fact = 0; //恒流模式设定值，单位A
volatile float CV_value = 0; //恒压模式设定值，单位V
volatile float CV_value_fact = 0; //恒压模式设定值，单位V
volatile float CR_value = 0; //恒阻模式设定值，单位R
volatile float CP_value = 0; //恒功率模式设定值，单位W

void monitor_voltage_CC()    //电压监控函数，传入参数（x,y,端口,量程）
{
    char test[10] = { };

    sprintf(test, "%.3f", dac8571_out);
    //   printf("DAC8571_userset=%s  ", test);    //监控程序里DAC8571的用户设定值

    sprintf(test, "%.4f", average_voltage_caculate(4, 5));
    LCD_ShowString(140, 210, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控ADS118:通道A0,实际上是监控DAC8571的实际输出值,显示在TFT上

    ADC1_feedback = average_voltage_caculate(5, 5);
    ADC1_feedback = 0.0331 * ADC1_feedback * ADC1_feedback + 6.6995 * ADC1_feedback + 0.054; //负载电压关于ADC1的特性曲线

    /*****************************************************************************************/
    /*仅供调试时使用*/
    //   sprintf(test, "%.4f", ADC1_feedback);
    //   printf("ADC1=%s  \n\r", test); //ADC1的输出值，输出至串口助手
    /*****************************************************************************************/
    sprintf(test, "%.4f", ADC1_feedback);
    LCD_ShowString(350, 250, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控ADS118:通道A1,实际上是监控ADC1的输出值,显示在TFT上,监控负载电压

    ADC2_feedback = average_voltage_caculate(6, 5);
    CC_value_fact = -0.0071 * ADC2_feedback * ADC2_feedback + 0.9383 * ADC2_feedback - 0.0245; //实际电流值关于ADC2的特性曲线
    sprintf(test, "%.4f", CC_value_fact);
    LCD_ShowString(350, 219, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控实际电流值
}

void monitor_voltage_CV()    //电压监控函数，传入参数（x,y,端口,量程）
{
    char test[10] = { };

    /*
     sprintf(test, "%.3f", dac8571_out);
     printf("DAC8571_userset=%s  ", test);    //监控程序里DAC8571的用户设定值
     */

    sprintf(test, "%.4f", average_voltage_caculate(4, 5));
    LCD_ShowString(140, 210, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控ADS118:通道A0,实际上是监控DAC8571的实际输出值,显示在TFT上
    //printf("DAC8571_fact=%s  ", test);    //DAC8571的实际输出值，输出至串口助手

    ADC3_feedback = average_voltage_caculate(7, 5);
    ADC3_feedback = 0.9091 * ADC3_feedback * ADC3_feedback + 2.5199 * ADC3_feedback + 0.2203;    //实际恒压值关于ADC3的特性曲线
    sprintf(test, "%.4f", ADC3_feedback);
    LCD_ShowString(350, 250, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控恒压电压值
    /*****************************************************************************************/
    /*仅供调试时使用*/
    // printf("ADC3=%s  \n\r", test); //ADC3的输出值，输出至串口助手
    //LCD_ShowString(116, 241, WHITE, BLACK, 16, (uint8_t*) test, 0, 0);
    /*****************************************************************************************/

}

void monitor_voltage_CR()    //电压监控函数，传入参数（x,y,端口,量程）
{
    char test[10] = { };

    /*
     sprintf(test, "%.3f", dac8571_out);
     printf("DAC8571_userset=%s  ", test);    //监控程序里DAC8571的用户设定值
     */

    sprintf(test, "%.4f", average_voltage_caculate(4, 5));
    LCD_ShowString(140, 210, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控ADS118:通道A0,实际上是监控DAC8571的实际输出值,显示在TFT上

    ADC1_feedback = average_voltage_caculate(5, 5);
    ADC1_feedback = 0.0331 * ADC1_feedback * ADC1_feedback + 6.6995 * ADC1_feedback + 0.054; //负载电压关于ADC1的特性曲线
    sprintf(test, "%.4f", ADC1_feedback);

    /*****************************************************************************************/
    /*仅供调试时使用*/
    printf("----------------------\n"); //ADC1的输出值，输出至串口助手
    printf("ADC1=%s  ", test); //ADC1的输出值，输出至串口助手
    /*****************************************************************************************/

    LCD_ShowString(350, 250, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控负载电压

    ADC2_feedback = average_voltage_caculate(6, 5);
    ADC2_feedback = -0.0071 * ADC2_feedback * ADC2_feedback + 0.9383 * ADC2_feedback - 0.0245;    //实际电流值关于ADC2的特性曲线
    sprintf(test, "%.4f", ADC2_feedback);

    /*****************************************************************************************/
    /*仅供调试时使用*/
    //printf("I=%s  \n\r", test); //ADC1的输出值，输出至串口助手
    /*****************************************************************************************/

    LCD_ShowString(350, 219, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控实际电流值
}

void monitor_voltage_Developer()    //电压监控函数，传入参数（x,y,端口,量程）
{
    char test[10] = { };

    sprintf(test, "%.3f", dac8571_out);
    printf("DAC8571_userset=%s  ", test);    //监控程序里DAC8571的用户设定值

    sprintf(test, "%.4f", average_voltage_caculate(4, 5));
    LCD_ShowString(140, 210, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控ADS118:通道A0,实际上是监控DAC8571的实际输出值,显示在TFT上
    printf("DAC8571_fact=%s  ", test);    //DAC8571的实际输出值，输出至串口助手

    ADC1_feedback = average_voltage_caculate(5, 5);
    sprintf(test, "%.4f", ADC1_feedback);
    LCD_ShowString(116, 241, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控ADS118:通道A1,实际上是监控ADC1的输出值,显示在TFT上
    printf("ADC1=%s  ", test); //ADC1的输出值，输出至串口助手

    ADC1_feedback = -0.0007 * ADC1_feedback * ADC1_feedback + 6.7863 * ADC1_feedback - 0.0142; //负载电压关于ADC1的特性曲线6.6V~14.74V

    sprintf(test, "%.4f", ADC1_feedback);
    LCD_ShowString(350, 250, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控负载电压

    ADC2_feedback = average_voltage_caculate(6, 5);
    sprintf(test, "%.4f", ADC2_feedback);
    LCD_ShowString(116, 272, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控ADS118:通道A2,实际上是监控ADC2的输出值,显示在TFT上
    printf("ADC2=%s  \n\r", test); //ADC2的输出值，输出至串口助手
    //ADC2_feedback = -0.0073 * ADC2_feedback * ADC2_feedback + 0.9247 * ADC2_feedback - 0.0015;    //实际电流值关于ADC2的特性曲线
    //sprintf(test, "%.4f", ADC2_feedback);
    //LCD_ShowString(350, 219, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控实际电流值
}

void monitor_voltage_CP()    //电压监控函数，传入参数（x,y,端口,量程）
{
    char test[10] = { };

    sprintf(test, "%.4f", average_voltage_caculate(4, 5));
    LCD_ShowString(140, 210, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控ADS118:通道A0,实际上是监控DAC8571的实际输出值,显示在TFT上

    ADC1_feedback = average_voltage_caculate(5, 5);
    ADC1_feedback = 0.0331 * ADC1_feedback * ADC1_feedback + 6.6995 * ADC1_feedback + 0.054; //负载电压关于ADC1的特性曲线
    sprintf(test, "%.4f", ADC1_feedback);
    LCD_ShowString(350, 250, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控负载电压

    ADC2_feedback = average_voltage_caculate(6, 5);
    ADC2_feedback = -0.0071 * ADC2_feedback * ADC2_feedback + 0.9383 * ADC2_feedback - 0.0245;    //实际电流值关于ADC2的特性曲线
    sprintf(test, "%.4f", ADC2_feedback);
    LCD_ShowString(350, 219, WHITE, BLACK, 16, (uint8_t*) test, 0, 0); //监控实际电流值
}
