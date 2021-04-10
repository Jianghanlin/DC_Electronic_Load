/*
 * GUI.c
 *
 *  Created on: 2021��1��4��
 *      Author: www14
 */
#include <stdio.h>
#include "ST7796S.h"
#include "delay.h"
#include "device_init.h"
#include "key.h"
#include "touch.h"
#include "picture.h"
#include "dac8571.h"
#include "ADS1118.h"
#include "display_voltage.h"
#include "DS18B20.h"
#include "pid.h"
#include "MAX4662.h"
#include "relay.h"
#include "math.h"
void draw_mode()
{
    LCD_Fill(0, 5, 470, 320, BLACK); //��ʾ֮ǰ��������Ļ

    Gui_StrCenter(0, 10, WHITE, BLUE, "ģʽѡ��", 32, 1, 1); //������ʾģʽѡ��

    LCD_Fill(44, 54, 276, 119, BLUE1);
    Show_Str(64, 71, WHITE, BLACK, "CC Mode", 24, 1, 1); //CC_Mode

    LCD_Fill(299, 54, 450, 119, BLUE1);
    Show_Str(338, 71, WHITE, BLACK, "CR Mode", 24, 1, 1); //CR_Mode

    LCD_Fill(44, 135, 276, 200, BLUE1);
    Show_Str(64, 152, WHITE, BLACK, "CV Mode", 24, 1, 1); //CV_Mode

    LCD_Fill(299, 135, 450, 200, BLUE1);
    Show_Str(338, 152, WHITE, BLACK, "CP Mode", 24, 1, 1); //CP_Mode

    LCD_Fill(44, 214, 276, 281, BLUE1);
    Show_Str(64, 233, WHITE, BLACK, "Developer Mode", 24, 1, 1); //Developer_Mode

    LCD_Fill(299, 214, 450, 281, BRED);
    Show_Str(338, 233, WHITE, BLACK, "More...", 24, 1, 1); //More...
}

void draw_return_buttom()
{

    gui_circle(447, 33, RED, 23, 1); //���о���������424��10��470��56
    LCD_DrawboldLine(434, 20, 460, 46, 2); //������
    LCD_DrawboldLine(434, 46, 460, 20, 2);
}

void clear_interface()
{
    LCD_Fill(173, 4, 309, 48, BLACK);
    LCD_Fill(44, 54, 276, 119, BLACK);
    LCD_Fill(299, 54, 450, 119, BLACK);
    LCD_Fill(44, 135, 276, 200, BLACK);
    LCD_Fill(299, 135, 450, 200, BLACK);
    LCD_Fill(44, 214, 276, 281, BLACK);
    LCD_Fill(299, 214, 450, 281, BLACK);
}

void draw_interface1(void)
{
    TIMER_A0->CCTL[0] &= ~ TIMER_A_CCTLN_CCIE;
    clear_interface(); //��ʾ֮ǰ��������Ļ,��������������ǵøĻ���
    //�����˳���ť�;���ģʽ��ʾ����
    LCD_Fill(10, 10, 133, 56, BLUE1); //����ģʽ��ʾ����
    Show_Str(20, 20, WHITE, WHITE, "CC Mode", 32, 1, 0);    //��ʾCC Mode
    draw_return_buttom(); //�����˳���ť
    LCD_DrawboldLine(10, 71, 470, 71, 4);    //���Ʒָ���
    Show_Str(10, 81, BLACK, WHITE, "Current Adjusting Area", 24, 0, 1);    //��ʾCurrent adjusting area
    Show_Str(21, 115, WHITE, BLACK, "Set Current", 16, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(55, 130, WHITE, BLACK, "Value:", 16, 1, 1);    //��ʾVoltage adjusting area

    gui_circle(155, 144, WHITE, 2, 1); //���о���������424��10��470��56
    LCD_Fill(124, 120, 146, 143, WHITE);
    LCD_Fill(164, 120, 186, 143, WHITE);
    LCD_Fill(199, 120, 221, 143, WHITE);
    LCD_Fill(234, 120, 256, 143, WHITE);    //�����м����

    LCD_ShowNum(128, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(168, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(203, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(238, 120, BLACK, WHITE, 0, 1, 24, 1, 1);    //���Ƴ�ʼ����

    LCD_ShowChar_2412(270, 120, WHITE, BLACK, 'A', 32, 1, 1);    //���Ƶ�λ

    LCD_Fill(345, 116, 403, 145, 0x397b); //ȷ������ʾ����
    Show_Str(350, 120, WHITE, BLACK, "Confirm", 24, 1, 1);    //��ʾȷ����ť����

    LCD_DrawboldLine(10, 158, 470, 158, 4);    //���Ʒָ���
    Show_Str(10, 168, BLACK, WHITE, "Monitoring area", 24, 0, 1);    //��ʾVoltage adjusting area
    Show_Str(21, 210, WHITE, BLACK, "DAC8571 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    // Show_Str(21, 241, WHITE, BLACK, "ADC1 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    //Show_Str(21, 272, WHITE, BLACK, "ADC2 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(240, 210, WHITE, BLACK, "I Value:       A", 24, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(240, 241, WHITE, BLACK, "V Value:       V", 24, 1, 1);    //��ʾVoltage adjusting area
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled

}

void draw_interface2(void)
{
    clear_interface(); //��ʾ֮ǰ��������Ļ,��������������ǵøĻ���
    //�����˳���ť�;���ģʽ��ʾ����
    LCD_Fill(10, 10, 133, 56, BLUE1); //����ģʽ��ʾ����
    Show_Str(20, 20, WHITE, WHITE, "CV Mode", 32, 1, 0);    //��ʾCC Mode
    //�����˳���ť�;���ģʽ��ʾ����
    draw_return_buttom(); //�����˳���ť
    LCD_DrawboldLine(10, 71, 470, 71, 4);    //���Ʒָ���
    Show_Str(10, 81, BLACK, WHITE, "Voltage Adjusting Area", 24, 0, 1);    //��ʾVoltage Adjusting Area
    Show_Str(21, 115, WHITE, BLACK, "Set Voltage", 16, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(55, 130, WHITE, BLACK, "Value:", 16, 1, 1);    //��ʾVoltage adjusting area

    gui_circle(155, 144, WHITE, 2, 1); //���о���������424��10��470��56
    LCD_Fill(124, 120, 146, 143, WHITE);
    LCD_Fill(164, 120, 186, 143, WHITE);
    LCD_Fill(199, 120, 221, 143, WHITE);
    LCD_Fill(234, 120, 256, 143, WHITE);    //�����м����

    /*
     LCD_Fill(124, 78, 146, 108, WHITE);    //��2��4�пɵ�
     LCD_Fill(164, 78, 186, 108, WHITE);
     LCD_Fill(199, 78, 221, 108, WHITE);
     LCD_Fill(234, 78, 256, 108, WHITE);
     LCD_Fill(124, 155, 146, 185, WHITE);
     LCD_Fill(164, 155, 186, 185, WHITE);
     LCD_Fill(199, 155, 221, 185, WHITE);
     LCD_Fill(234, 155, 256, 185, WHITE);    //����������ť���򣬿��ӻ�����������Ҫ���ԣ�ȡ��ע�ͼ���
     */

    LCD_ShowNum(128, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(168, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(203, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(238, 120, BLACK, WHITE, 0, 1, 24, 1, 1);    //���Ƴ�ʼ����

    LCD_ShowChar_2412(270, 120, WHITE, BLACK, 'V', 32, 1, 1);    //���Ƶ�λ

    LCD_Fill(345, 116, 403, 145, 0x397b); //ȷ������ʾ����
    Show_Str(350, 120, WHITE, BLACK, "Confirm", 24, 1, 1);    //��ʾȷ����ť����

    LCD_DrawboldLine(10, 158, 470, 158, 4);    //���Ʒָ���
    Show_Str(10, 168, BLACK, WHITE, "Monitoring area", 24, 0, 1);    //��ʾVoltage adjusting area
    Show_Str(21, 210, WHITE, BLACK, "DAC8571 Value:         V", 16, 1, 1);
    // Show_Str(21, 241, WHITE, BLACK, "ADC3 Value:         V", 16, 1, 1);
    Show_Str(240, 241, WHITE, BLACK, "V Value:       V", 24, 1, 1);
}

void draw_interface3(void)
{
    TIMER_A0->CCTL[0] &= ~ TIMER_A_CCTLN_CCIE; // TACCR0 interrupt disabled

    clear_interface(); //��ʾ֮ǰ��������Ļ,��������������ǵøĻ���

    //�����˳���ť�;���ģʽ��ʾ����
    LCD_Fill(10, 10, 200, 56, BLUE1); //����ģʽ��ʾ����
    Show_Str(20, 20, WHITE, WHITE, "Developer Mode", 24, 1, 1);    //��ʾDeveloper Mode
    draw_return_buttom(); //�����˳���ť
    LCD_DrawboldLine(10, 71, 470, 71, 4);    //���Ʒָ���
    Show_Str(10, 81, BLACK, WHITE, "Voltage adjusting area", 24, 0, 1);    //��ʾVoltage adjusting area
    Show_Str(21, 115, WHITE, BLACK, "Set DAC8571", 16, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(55, 130, WHITE, BLACK, "Output:", 16, 1, 1);    //��ʾVoltage adjusting area

    gui_circle(155, 144, WHITE, 2, 1); //���о���������424��10��470��56
    LCD_Fill(124, 120, 146, 143, WHITE);
    LCD_Fill(164, 120, 186, 143, WHITE);
    LCD_Fill(199, 120, 221, 143, WHITE);
    LCD_Fill(234, 120, 256, 143, WHITE);    //�����м����

    /*
     LCD_Fill(124, 78, 146, 108, WHITE);    //��2��4�пɵ�
     LCD_Fill(164, 78, 186, 108, WHITE);
     LCD_Fill(199, 78, 221, 108, WHITE);
     LCD_Fill(234, 78, 256, 108, WHITE);
     LCD_Fill(124, 155, 146, 185, WHITE);
     LCD_Fill(164, 155, 186, 185, WHITE);
     LCD_Fill(199, 155, 221, 185, WHITE);
     LCD_Fill(234, 155, 256, 185, WHITE);    //����������ť���򣬿��ӻ�����������Ҫ���ԣ�ȡ��ע�ͼ���
     */

    LCD_ShowNum(128, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(168, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(203, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(238, 120, BLACK, WHITE, 0, 1, 24, 1, 1);    //���Ƴ�ʼ����

    LCD_ShowChar_2412(270, 120, WHITE, BLACK, 'V', 32, 1, 1);    //���Ƶ�λ

    LCD_Fill(345, 116, 403, 145, 0x397b); //ȷ������ʾ����
    Show_Str(350, 120, WHITE, BLACK, "Confirm", 24, 1, 1);    //��ʾȷ����ť����

    LCD_DrawboldLine(10, 158, 470, 158, 4);    //���Ʒָ���
    Show_Str(10, 168, BLACK, WHITE, "Monitoring area", 24, 0, 1);    //��ʾVoltage adjusting area
    Show_Str(21, 210, WHITE, BLACK, "DAC8571 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(21, 241, WHITE, BLACK, "ADC1 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(21, 272, WHITE, BLACK, "ADC2 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(240, 210, WHITE, BLACK, "I Value:       A", 24, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(240, 241, WHITE, BLACK, "V Value:       V", 24, 1, 1);    //��ʾVoltage adjusting area

    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
}

void draw_interface4(void)
{
    TIMER_A0->CCTL[0] &= ~ TIMER_A_CCTLN_CCIE;
    clear_interface(); //��ʾ֮ǰ��������Ļ,��������������ǵøĻ���
    //�����˳���ť�;���ģʽ��ʾ����
    LCD_Fill(10, 10, 133, 56, BLUE1); //����ģʽ��ʾ����
    Show_Str(20, 20, WHITE, WHITE, "CR Mode", 32, 1, 0);    //��ʾCC Mode
    draw_return_buttom(); //�����˳���ť
    LCD_DrawboldLine(10, 71, 470, 71, 4);    //���Ʒָ���
    Show_Str(10, 81, BLACK, WHITE, "Resistance Adjusting Area", 24, 0, 1);    //��ʾCurrent adjusting area
    Show_Str(10, 115, WHITE, BLACK, "Set Resistance", 16, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(60, 130, WHITE, BLACK, "Value:", 16, 1, 1);    //��ʾVoltage adjusting area

    gui_circle(228, 144, WHITE, 2, 1); //����С����
    LCD_Fill(124, 120, 146, 143, WHITE);
    LCD_Fill(164, 120, 186, 143, WHITE);
    LCD_Fill(199, 120, 221, 143, WHITE);
    LCD_Fill(234, 120, 256, 143, WHITE);    //�����м����

    LCD_ShowNum(128, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(168, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(203, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(238, 120, BLACK, WHITE, 0, 1, 24, 1, 1);    //���Ƴ�ʼ����

    Show_Str(270, 120, WHITE, BLACK, "Ohm", 32, 1, 1);    ////���Ƶ�λ

    LCD_Fill(345, 116, 403, 145, 0x397b); //ȷ������ʾ����
    Show_Str(350, 120, WHITE, BLACK, "Confirm", 24, 1, 1);    //��ʾȷ����ť����

    LCD_DrawboldLine(10, 158, 470, 158, 4);    //���Ʒָ���
    Show_Str(10, 168, BLACK, WHITE, "Monitoring area", 24, 0, 1);    //��ʾVoltage adjusting area
    Show_Str(21, 210, WHITE, BLACK, "DAC8571 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    // Show_Str(21, 241, WHITE, BLACK, "ADC1 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    //Show_Str(21, 272, WHITE, BLACK, "ADC2 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(240, 210, WHITE, BLACK, "I Value:       A", 24, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(240, 241, WHITE, BLACK, "V Value:       V", 24, 1, 1);    //��ʾVoltage adjusting area
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled

}

void draw_interface5(void)
{
    TIMER_A0->CCTL[0] &= ~ TIMER_A_CCTLN_CCIE;
    clear_interface(); //��ʾ֮ǰ��������Ļ,��������������ǵøĻ���
    //�����˳���ť�;���ģʽ��ʾ����
    LCD_Fill(10, 10, 133, 56, BLUE1); //����ģʽ��ʾ����
    Show_Str(20, 20, WHITE, WHITE, "CP Mode", 32, 1, 0);    //��ʾCC Mode
    draw_return_buttom(); //�����˳���ť
    LCD_DrawboldLine(10, 71, 470, 71, 4);    //���Ʒָ���
    Show_Str(10, 81, BLACK, WHITE, "Power Adjusting Area", 24, 0, 1);    //��ʾCurrent adjusting area
    Show_Str(21, 115, WHITE, BLACK, "Set Power", 16, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(55, 130, WHITE, BLACK, "Value:", 16, 1, 1);    //��ʾVoltage adjusting area

    gui_circle(155, 144, WHITE, 2, 1); //���о���������424��10��470��56
    LCD_Fill(124, 120, 146, 143, WHITE);
    LCD_Fill(164, 120, 186, 143, WHITE);
    LCD_Fill(199, 120, 221, 143, WHITE);
    LCD_Fill(234, 120, 256, 143, WHITE);    //�����м����

    LCD_ShowNum(128, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(168, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(203, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(238, 120, BLACK, WHITE, 0, 1, 24, 1, 1);    //���Ƴ�ʼ����

    LCD_ShowChar_2412(270, 120, WHITE, BLACK, 'W', 32, 1, 1);    //���Ƶ�λ

    LCD_Fill(345, 116, 403, 145, 0x397b); //ȷ������ʾ����
    Show_Str(350, 120, WHITE, BLACK, "Confirm", 24, 1, 1);    //��ʾȷ����ť����

    LCD_DrawboldLine(10, 158, 470, 158, 4);    //���Ʒָ���
    Show_Str(10, 168, BLACK, WHITE, "Monitoring area", 24, 0, 1);    //��ʾVoltage adjusting area
    Show_Str(21, 210, WHITE, BLACK, "DAC8571 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    // Show_Str(21, 241, WHITE, BLACK, "ADC1 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    // Show_Str(21, 272, WHITE, BLACK, "ADC2 Value:         V", 16, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(240, 210, WHITE, BLACK, "I Value:       A", 24, 1, 1);    //��ʾVoltage adjusting area
    Show_Str(240, 241, WHITE, BLACK, "V Value:       V", 24, 1, 1);    //��ʾVoltage adjusting area
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled

}

void more(void)
{
    uint8_t flag = 0;
    clear_interface(); //��ʾ֮ǰ��������Ļ
    //�����˳���ť�;���ģʽ��ʾ����
    LCD_Fill(10, 10, 200, 56, BLUE1); //����ģʽ��ʾ����
    Show_Str(20, 20, WHITE, WHITE, "More Settings", 24, 1, 1);    //��ʾMore Settings
    draw_return_buttom(); //�����˳���ť
    Show_Str(20, 80, WHITE, WHITE, "��Һ�,���ǽ����,Ŀǰ��ʾ���������̼���Rev1.0,�����д�", 16, 1, 1);    //��ʾMore Settings
    while (flag == 0)
    {
        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //������������
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56)) //�˳������о���������424��10��470��56     //CC_Mode������
            {
                flag = 1;
                draw_mode(); //ģʽѡ��ͼ�λ���
            }
        }
    }
}

void draw_personal_information()
{
    Gui_StrCenter(0, 5, WHITE, BLUE, "ֱ�����Ӹ���", 32, 1, 1); //������ʾ��������
    Gui_Drawbmp_JHL(20, 67, gImage_jianghanlin); //��ʾ����ֵĸ���һ�����Լ�������Ϣ
    Show_Str(111, 80, BLUE, YELLOW, "������", 24, 0, 0);
    Show_Str(111, 107, WHITE, WHITE, "����:�����", 16, 1, 0);
    Show_Str(111, 124, WHITE, WHITE, "ѧ��:Xb17610107", 16, 1, 0);
    Show_Str(111, 141, WHITE, WHITE, "�༶:17������Ϣ����1", 16, 1, 0);
    Gui_Drawbmp_LL(15, 205, gImage_liulu); //��ʾ����ֵĸ���һ�����Լ�������Ϣ
    Show_Str(111, 214, BLUE, YELLOW, "Ӳ�����", 24, 0, 0);
    Show_Str(111, 241, WHITE, WHITE, "����:��¶", 16, 1, 0);
    Show_Str(111, 258, WHITE, WHITE, "ѧ��:Xb17610124", 16, 1, 0);
    Show_Str(111, 275, WHITE, WHITE, "�༶:17������Ϣ����1", 16, 1, 0);
    LCD_Fill(294, 97, 450, 224, GREEN); //��ʼʹ�þ��ΰ�ť����
}

//���������ָ�����͵ģ���Ϊ�����һ������ͣ�ִ�����Ӻ������ֵ�ᱻ�ͷţ��Ӹ�������˵��û�иı�ԭ��λ�õ�ֵ������ָ���͵ı�������Ӹ����ϸı�ԭ��λ�õ�ֵ
//�ڶ�������������趨ֵ
void draw_focus(uint8_t *pos, volatile float *setvalue, uint8_t mode, uint8_t clear)
{
    float trans = 0; //ֻ������Ϊ�м���������һЩ���ӵ�����
    static uint8_t gewei = 0, xiaoshu1 = 0, xiaoshu2 = 0, xiaoshu3 = 0;
    if (clear == 1) //�󼸴ξ�������Ҫ��ո�λ��ֵ��������ʾֵ��ʵ��ֵ��ȫ����Ӧ
    {
        gewei = xiaoshu1 = xiaoshu2 = xiaoshu3 = 0;
    }
    if ((tp_dev.x > 124) && (tp_dev.y > 120) && (tp_dev.x < 146) && (tp_dev.y < 143)) //ѡ����gewei
    {
        if (*pos != 0) //���Ƶ�ǰλ������ͷ��ͬʱ�������λ��������ͷ
        {
            switch (*pos)
            {
            case 2:
                Fill_Triangel(175, 113 - 3, 163, 119 - 3, 187, 119 - 3, BLACK);
                LCD_ShowNum(164 + 4, 120, BLACK, WHITE, xiaoshu1, 1, 24, 0, 1);
                Fill_Triangel(163, 148 - 1, 187, 148 - 1, 175, 154 - 1, BLACK);
                break;
            case 3:
                Fill_Triangel(210, 113 - 3, 198, 119 - 3, 222, 119 - 3, BLACK);
                LCD_ShowNum(199 + 4, 120, BLACK, WHITE, xiaoshu2, 1, 24, 0, 1);
                Fill_Triangel(198, 148 - 1, 222, 148 - 1, 210, 154 - 1, BLACK);
                break;
            case 4:
                Fill_Triangel(245, 113 - 3, 233, 119 - 3, 257, 119 - 3, BLACK);
                LCD_ShowNum(234 + 4, 120, BLACK, WHITE, xiaoshu3, 1, 24, 0, 1);
                Fill_Triangel(233, 148 - 1, 257, 148 - 1, 245, 154 - 1, BLACK);
                break;
            default:
                break;
            }
        }
        *pos = 1; //��ǰѡ��gewei
        Fill_Triangel(135, 113 - 3, 123, 119 - 3, 147, 119 - 3, RED);
        LCD_ShowNum(124 + 4, 120, BLACK, YELLOW, gewei, 1, 24, 0, 1);
        Fill_Triangel(123, 148 - 1, 147, 148 - 1, 135, 154 - 1, RED);
    }
    else if ((tp_dev.x > 164) && (tp_dev.y > 120) && (tp_dev.x < 186) && (tp_dev.y < 143)) //ѡ����xiaoshu1
    {
        if (*pos != 0)
        {
            switch (*pos)
            {
            case 1:
                Fill_Triangel(135, 113 - 3, 123, 119 - 3, 147, 119 - 3, BLACK);
                LCD_ShowNum(124 + 4, 120, BLACK, WHITE, gewei, 1, 24, 0, 1);
                Fill_Triangel(123, 148 - 1, 147, 148 - 1, 135, 154 - 1, BLACK);
                break;
            case 3:
                Fill_Triangel(210, 113 - 3, 198, 119 - 3, 222, 119 - 3, BLACK);
                LCD_ShowNum(199 + 4, 120, BLACK, WHITE, xiaoshu2, 1, 24, 0, 1);
                Fill_Triangel(198, 148 - 1, 222, 148 - 1, 210, 154 - 1, BLACK);
                break;
            case 4:
                Fill_Triangel(245, 113 - 3, 233, 119 - 3, 257, 119 - 3, BLACK);
                LCD_ShowNum(234 + 4, 120, BLACK, WHITE, xiaoshu3, 1, 24, 0, 1);    //�����м����
                Fill_Triangel(233, 148 - 1, 257, 148 - 1, 245, 154 - 1, BLACK);
                break;
            default:
                break;
            }
        }
        *pos = 2;
        Fill_Triangel(175, 113 - 3, 163, 119 - 3, 187, 119 - 3, RED);
        LCD_ShowNum(164 + 4, 120, BLACK, YELLOW, xiaoshu1, 1, 24, 0, 1);
        Fill_Triangel(163, 148 - 1, 187, 148 - 1, 175, 154 - 1, RED);
    }
    else if ((tp_dev.x > 199) && (tp_dev.y > 120) && (tp_dev.x < 221) && (tp_dev.y < 143)) //ѡ����xiaoshu2
    {
        switch (*pos)
        {
        case 1:
            Fill_Triangel(135, 113 - 3, 123, 119 - 3, 147, 119 - 3, BLACK);
            LCD_ShowNum(124 + 4, 120, BLACK, WHITE, gewei, 1, 24, 0, 1);
            Fill_Triangel(123, 148 - 1, 147, 148 - 1, 135, 154 - 1, BLACK);
            break;
        case 2:
            Fill_Triangel(175, 113 - 3, 163, 119 - 3, 187, 119 - 3, BLACK);
            LCD_ShowNum(164 + 4, 120, BLACK, WHITE, xiaoshu1, 1, 24, 0, 1);
            Fill_Triangel(163, 148 - 1, 187, 148 - 1, 175, 154 - 1, BLACK);
            break;
        case 4:
            Fill_Triangel(245, 113 - 3, 233, 119 - 3, 257, 119 - 3, BLACK);
            LCD_ShowNum(234 + 4, 120, BLACK, WHITE, xiaoshu3, 1, 24, 0, 1);    //�����м����
            Fill_Triangel(233, 148 - 1, 257, 148 - 1, 245, 154 - 1, BLACK);
            break;
        default:
            break;
        }
        *pos = 3;
        Fill_Triangel(210, 113 - 3, 198, 119 - 3, 222, 119 - 3, RED);
        LCD_ShowNum(199 + 4, 120, BLACK, YELLOW, xiaoshu2, 1, 24, 0, 1);
        Fill_Triangel(198, 148 - 1, 222, 148 - 1, 210, 154 - 1, RED);
    }
    else if ((tp_dev.x > 234) && (tp_dev.y > 120) && (tp_dev.x < 256) && (tp_dev.y < 143)) //ѡ����xiaoshu3
    {
        switch (*pos)
        {
        case 1:
            Fill_Triangel(135, 113 - 3, 123, 119 - 3, 147, 119 - 3, BLACK);
            LCD_ShowNum(124 + 4, 120, BLACK, WHITE, gewei, 1, 24, 0, 1);
            Fill_Triangel(123, 148 - 1, 147, 148 - 1, 135, 154 - 1, BLACK);
            break;
        case 2:
            Fill_Triangel(175, 113 - 3, 163, 119 - 3, 187, 119 - 3, BLACK);
            LCD_ShowNum(164 + 4, 120, BLACK, WHITE, xiaoshu1, 1, 24, 0, 1);
            Fill_Triangel(163, 148 - 1, 187, 148 - 1, 175, 154 - 1, BLACK);
            break;
        case 3:
            Fill_Triangel(210, 113 - 3, 198, 119 - 3, 222, 119 - 3, BLACK);
            LCD_ShowNum(199 + 4, 120, BLACK, WHITE, xiaoshu2, 1, 24, 0, 1);
            Fill_Triangel(198, 148 - 1, 222, 148 - 1, 210, 154 - 1, BLACK);
            break;
        default:
            break;
        }
        *pos = 4;
        Fill_Triangel(245, 113 - 3, 233, 119 - 3, 257, 119 - 3, RED);    //��������������
        LCD_ShowNum(234 + 4, 120, BLACK, YELLOW, xiaoshu3, 1, 24, 0, 1);    //�����м����
        Fill_Triangel(233, 148 - 1, 257, 148 - 1, 245, 154 - 1, RED);    //��������������
    }    //��ѹλѡ���������
    //��ѹλ��������鿪ʼ
    else if ((tp_dev.x > 124) && (tp_dev.x < 146) && (*pos == 1))    //��λ��������
    {
        if ((tp_dev.y > 78) && (tp_dev.y < 108))
        {
            if (gewei < 9)    //ÿλ��߲��ܳ���9,�˴�ԭ��Ӧ����(xiaoshu1 >= 0) && (xiaoshu1 < 9)�������޷���Ĭ��>=0,����ǰ��������壬ʡ��
            {
                gewei++;
            }
            LCD_ShowNum(124 + 4, 120, BLACK, YELLOW, gewei, 1, 24, 0, 1);
        }
        else if ((tp_dev.y > 155) && (tp_dev.y < 185))
        {
            if (gewei > 0)    //ÿλ��Ͳ���С��0
            {
                gewei--;
            }
            LCD_ShowNum(124 + 4, 120, BLACK, YELLOW, gewei, 1, 24, 0, 1);
        }
        else
            ;
    }
    else if ((tp_dev.x > 164) && (tp_dev.x < 186) && (*pos == 2))    //xiaoshu1��������
    {
        if ((tp_dev.y > 78) && (tp_dev.y < 108))
        {
            if (xiaoshu1 < 9)
            {
                xiaoshu1++;
            }
            LCD_ShowNum(164 + 4, 120, BLACK, YELLOW, xiaoshu1, 1, 24, 0, 1);
        }

        else if ((tp_dev.y > 155) && (tp_dev.y < 185))
        {
            if (xiaoshu1 > 0)
            {
                xiaoshu1--;
            }
            LCD_ShowNum(164 + 4, 120, BLACK, YELLOW, xiaoshu1, 1, 24, 0, 1);
        }
        else
            ;
    }
    else if ((tp_dev.x > 199) && (tp_dev.x < 221) && (*pos == 3))    //xiaoshu2��������
    {
        if ((tp_dev.y > 78) && (tp_dev.y < 108))
        {
            if (xiaoshu2 < 9)
            {
                xiaoshu2++;
            }
            LCD_ShowNum(199 + 4, 120, BLACK, YELLOW, xiaoshu2, 1, 24, 0, 1);
        }
        else if ((tp_dev.y > 155) && (tp_dev.y < 185))
        {
            if (xiaoshu2 > 0)
            {
                xiaoshu2--;
            }
            LCD_ShowNum(199 + 4, 120, BLACK, YELLOW, xiaoshu2, 1, 24, 0, 1);
        }
        else
            ;
    }
    else if ((tp_dev.x > 234) && (tp_dev.x < 256) && (*pos == 4))    //xiaoshu3��������
    {
        if ((tp_dev.y > 78) && (tp_dev.y < 108))
        {
            if (xiaoshu3 < 9)
            {
                xiaoshu3++;
            }
            LCD_ShowNum(234 + 4, 120, BLACK, YELLOW, xiaoshu3, 1, 24, 0, 1);
        }
        else if ((tp_dev.y > 155) && (tp_dev.y < 185))
        {
            if (xiaoshu3 > 0)
            {
                xiaoshu3--;
            }
            LCD_ShowNum(234 + 4, 120, BLACK, YELLOW, xiaoshu3, 1, 24, 0, 1);
        }
        else
            ;
    }
    //������������
    else if ((tp_dev.x > 345) && (tp_dev.y > 116) && (tp_dev.x < 403) && (tp_dev.y < 145))    //ȷ�ϰ���ִ�к���
    {
        *setvalue = gewei + 0.1 * xiaoshu1 + 0.01 * xiaoshu2 + 0.001 * xiaoshu3;
        switch (mode)
        {
        case 1:
            if (*setvalue > 1.2)    //CCģʽ0.1~1.2A
            {
                Show_Str(300, 81, RED, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //��ʾVoltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //��ʾVoltage adjusting area
            }
            else
            {
                dac8571_out = 0.008 * (*setvalue) * (*setvalue) + 0.9707 * (*setvalue) - 0.0229;  //DAC8571�������ʵ�ʵ�������Ϲ�ʽ
                DAC8571_OUT(dac8571_out);
                Show_Str(300, 81, GREEN, BLACK, "Set Successful!!", 16, 0, 1);    //��ʾVoltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Successful!!", 16, 0, 1);    //��ʾVoltage adjusting area
            }
            break;
        case 2:
            if (*setvalue > 3)    //CVģʽҪ��1~3V
            {
                Show_Str(300, 81, RED, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //��ʾVoltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //��ʾVoltage adjusting area
            }
            else
            {
                dac8571_out = -0.0183 * (*setvalue) * (*setvalue) + 0.5446 * (*setvalue) - 0.088; //DAC8571�������ʵ�ʺ�ѹ����Ϲ�ʽ
                DAC8571_OUT(dac8571_out);
                Show_Str(300, 81, GREEN, BLACK, "Set Successful!!", 16, 0, 1);    //��ʾVoltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Successful!!", 16, 0, 1);    //��ʾVoltage adjusting area
            }
            break;
        case 3:
            *setvalue = (*setvalue) * 100.0;
            if (*setvalue < 20)    //CRģʽҪ��10~100ŷ
            {
                Show_Str(300, 81, RED, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //��ʾVoltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //��ʾVoltage adjusting area
            }
            else
            {
                dac8571_out = ADC1_feedback / (*setvalue);    //�����趨�ĵ���ֵ���������
                dac8571_out = 0.008 * dac8571_out * dac8571_out + 0.9707 * dac8571_out - 0.0229;  //DAC8571�������ʵ�ʵ�������Ϲ�ʽ
                DAC8571_OUT(dac8571_out);
                Show_Str(330, 81, GREEN, BLACK, "Set Successful!!", 16, 0, 1);    //��ʾVoltage adjusting area
                delay_ms(340);
                Show_Str(330, 81, BLACK, BLACK, "Set Successful!!", 16, 0, 1);    //��ʾVoltage adjusting area
            }
            break;
        case 4:
            trans = (*setvalue) / ADC1_feedback;    //I=P/U
            if ((*setvalue > 6) || (trans > 1.2))    //CPģʽ1~6W
            {
                Show_Str(300, 81, RED, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //��ʾVoltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //��ʾVoltage adjusting area
            }
            else
            {
                dac8571_out = 0.008 * trans * trans + 0.9707 * trans - 0.0229;  //DAC8571�������ʵ�ʵ�������Ϲ�ʽ
                DAC8571_OUT(dac8571_out);
                Show_Str(300, 81, GREEN, BLACK, "Set Successful!!", 16, 0, 1);    //��ʾVoltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Successful!!", 16, 0, 1);    //��ʾVoltage adjusting area
            }
            break;
        case 5:
            DAC8571_OUT(*setvalue);
            break;

        default:
            break;
        }
    }
    else
        ;
}

void CC_Mode()
{
    float difference = 0;
    static uint8_t clear_setavlue_flag = 0;
    uint8_t pos = 0, exit_mode_flag = 0;    //pos������¼��ǰ���µ����Ǹ�λ��flag������¼�˳���ť��û�б�����
    draw_interface1();         //���ƹ̶�Ԫ��
    while (exit_mode_flag == 0)
    {
        display_temperature();         //��ʾ����¶�
        monitor_voltage_CC();         //��ʾ��ص�ѹ

        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //������������
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56))    //�˳������о���������424��10��470��56
            {
                DA_IN_off;    //�ر�����DA����ͨ��
                switch_load_voltage_to_CC;    //Ĭ�Ͻ����ص�ѹ�л���CC
                DAC8571_OUT(0);    //һ���˳���ϸ�Ľ��棬DAC8571�������
                dac8571_out = 0;    //������Ļ������漰�Ӽ�DAC8571�Ĳ���ʱ������ۼƣ�����Ҫ����
                CC_value = 0;
                exit_mode_flag = 1;    //��¼�˳���ť��û�б�����
                clear_setavlue_flag = 1;    //���������ʾֵ��־
                draw_mode(); //ģʽѡ��ͼ�λ���
            }
            else
            {
                draw_focus(&pos, &CC_value, 1, clear_setavlue_flag); //���������pos�ĵ�ַ����Ϊָ��������Ը����ϵظı�ԭ��λ�õ�ֵ,�ڶ���������Ҫ����DAC8571�����ֵ
                clear_setavlue_flag = 0;
            }
        }
        if (CC_value > 0)
        {
            difference = CC_value - CC_value_fact;
            if (fabs(difference) > 0.01)
            {
                if (difference > 0)
                {
                    dac8571_out += 0.01; //
                    DAC8571_OUT(dac8571_out);
                }
                else if (difference < 0)
                {
                    dac8571_out -= 0.01; //
                    DAC8571_OUT(dac8571_out);
                }
                delay_ms(5);
            }
            else if (fabs(difference) > 0.005)
            {
                if (difference > 0)
                {
                    dac8571_out += 0.005; //
                    DAC8571_OUT(dac8571_out);
                }
                else if (difference < 0)
                {
                    dac8571_out -= 0.005; //
                    DAC8571_OUT(dac8571_out);
                }
                delay_ms(5);
            }
            else
                ;
        }
    }
}

void CV_Mode()
{
    // float difference = 0;
    static uint8_t clear_setavlue_flag = 0;
    uint8_t pos = 0, exit_mode_flag = 0;    //pos������¼��ǰ���µ����Ǹ�λ��flag������¼�˳���ť��û�б�����
    draw_interface2();         //���ƹ̶�Ԫ��
    while (exit_mode_flag == 0)
    {
        monitor_voltage_CV();         //��ʾ��ص�ѹ
        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //������������
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56))    //�˳������о���������424��10��470��56
            {
                DA_IN_off;    //�ر�����DA����ͨ��
                switch_load_voltage_to_CC;
                DAC8571_OUT(0);    //һ���˳���ϸ�Ľ��棬DAC8571�������
                dac8571_out = 0;    //������Ļ������漰�Ӽ�DAC8571�Ĳ���ʱ������ۼƣ�����Ҫ����
                CV_value = 0;
                exit_mode_flag = 1;    //��¼�˳���ť��û�б�����
                clear_setavlue_flag = 1;    //���������ʾֵ��־

                draw_mode(); //ģʽѡ��ͼ�λ���
            }
            else
            {
                draw_focus(&pos, &CV_value, 2, clear_setavlue_flag); //���������pos�ĵ�ַ����Ϊָ��������Ը����ϵظı�ԭ��λ�õ�ֵ,�ڶ���������Ҫ����DAC8571�����ֵ
                clear_setavlue_flag = 0;
            }
        }
        /*        if (CV_value > 0)
         {
         difference = CV_value - CV_value_fact;
         if (fabs(difference) > 0.1) //>0.1
         {
         if (difference > 0)
         {
         dac8571_out += 0.04; //
         DAC8571_OUT(dac8571_out);
         }
         else if (difference < 0)
         {
         dac8571_out -= 0.04; //
         DAC8571_OUT(dac8571_out);
         }
         delay_ms(5);
         }
         else if (fabs(difference) > 0.03) //0.04~0.1
         {
         if (difference > 0)
         {
         dac8571_out += 0.01; //
         DAC8571_OUT(dac8571_out);
         }
         else if (difference < 0)
         {
         dac8571_out -= 0.01; //
         DAC8571_OUT(dac8571_out);
         }
         delay_ms(5);
         }
         else
         ;
         }*/
    }
}

void CR_Mode()
{
    static uint8_t clear_setavlue_flag = 0;
    uint8_t pos = 0, exit_mode_flag = 0;    //pos������¼��ǰ���µ����Ǹ�λ��flag������¼�˳���ť��û�б�����
    draw_interface4();         //���ƹ̶�Ԫ��
    while (exit_mode_flag == 0)
    {
        display_temperature();         //��ʾ����¶�
        monitor_voltage_CR();         //��ʾ��ص�ѹ

        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //������������
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56))    //�˳������о���������424��10��470��56
            {
                DA_IN_off;    //�ر�����DA����ͨ��
                switch_load_voltage_to_CC;    //Ĭ�Ͻ����ص�ѹ�л���CC
                DAC8571_OUT(0);    //һ���˳���ϸ�Ľ��棬DAC8571�������
                dac8571_out = 0;    //������Ļ������漰�Ӽ�DAC8571�Ĳ���ʱ������ۼƣ�����Ҫ����
                CR_value = 0;
                exit_mode_flag = 1;    //��¼�˳���ť��û�б�����
                clear_setavlue_flag = 1;    //���������ʾֵ��־
                draw_mode(); //ģʽѡ��ͼ�λ���
            }
            else
            {
                draw_focus(&pos, &CR_value, 3, clear_setavlue_flag); //���������pos�ĵ�ַ����Ϊָ��������Ը����ϵظı�ԭ��λ�õ�ֵ,�ڶ���������Ҫ����DAC8571�����ֵ
                clear_setavlue_flag = 0;
            }
        }
        /*        ADC2_feedback = average_voltage_caculate(6, 5);
         CC_value_fact = 0.0192 * ADC2_feedback * ADC2_feedback + 0.9032 * ADC2_feedback + 0.006;
         dac8571_out += Incremental_PI(CC_value_fact, CC_value); //����ʽPID����������ֵ������
         DAC8571_OUT(dac8571_out);*/
    }
}

void CP_Mode()
{
    static uint8_t clear_setavlue_flag = 0;
    uint8_t pos = 0, exit_mode_flag = 0;    //pos������¼��ǰ���µ����Ǹ�λ��flag������¼�˳���ť��û�б�����
    draw_interface5();         //���ƹ̶�Ԫ��
    while (exit_mode_flag == 0)
    {
        display_temperature();         //��ʾ����¶�
        monitor_voltage_CP();         //��ʾ��ص�ѹ

        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //������������
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56))    //�˳������о���������424��10��470��56
            {
                DA_IN_off;    //�ر�����DA����ͨ��
                switch_load_voltage_to_CC;    //Ĭ�Ͻ����ص�ѹ�л���CC
                DAC8571_OUT(0);    //һ���˳���ϸ�Ľ��棬DAC8571�������
                dac8571_out = 0;    //������Ļ������漰�Ӽ�DAC8571�Ĳ���ʱ������ۼƣ�����Ҫ����
                CP_value = 0;
                exit_mode_flag = 1;    //��¼�˳���ť��û�б�����
                clear_setavlue_flag = 1;    //���������ʾֵ��־
                draw_mode(); //ģʽѡ��ͼ�λ���
            }
            else
            {
                draw_focus(&pos, &CP_value, 4, clear_setavlue_flag); //���������pos�ĵ�ַ����Ϊָ��������Ը����ϵظı�ԭ��λ�õ�ֵ,�ڶ���������Ҫ����DAC8571�����ֵ
                clear_setavlue_flag = 0;
            }
        }
    }
}

void Developer_Mode()
{
    static uint8_t clear_setvalue_flag = 0; //�û��趨ֵ�����־λ
    uint8_t pos = 0, exit_mode_flag = 0;    //pos������¼��ǰ���µ����Ǹ�λ��flag������¼�˳���ť��û�б�����

    draw_interface3();         //���ƹ̶�Ԫ��

    switch_load_voltage_to_CC;         //�л����ص�ѹ��CC��·
    DA_IN_off;         //�ر�����DA����ͨ��
    CC_Mode_DA_IN_on;         //����CC��·DA����ͨ��

    while (exit_mode_flag == 0)
    {
        display_temperature();         //��ʾ����¶�
        monitor_voltage_Developer();             //Ĭ�ϼ��4ͨ���ĵ�ѹֵ������Ӧ�û���д���
        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //������������
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56))    //�˳������о���������424��10��470��56
            {
                DAC8571_OUT(0);    //һ���˳���ϸ�Ľ��棬DAC8571�������
                dac8571_out = 0;    //������Ļ������漰�Ӽ�DAC8571�Ĳ���ʱ������ۼƣ�����Ҫ����
                CC_value = 0;
                exit_mode_flag = 1;    //��¼�˳���ť��û�б�����
                clear_setvalue_flag = 1;    //���������ʾֵ��־

                draw_mode(); //ģʽѡ��ͼ�λ���
            }
            else
            {
                /*
                 * ��1�����������pos�ĵ�ַ����Ϊָ��������Ը����ϵظı�ԭ��λ�õ�ֵ,��2��������Ҫ����DAC8571�����ֵ����3�����������ѡ�������ģʽ����4������������趨ֵ�����־λ
                 * ����dac8571_outΪȫ�ֱ�����Ϊ�˽���˳����û��趨ֵ��Ȼ����������clear_setvalue_flag-->�û��趨ֵ�����־λ
                 * �����˳���ť��clear_setvalue_flag=1����һ�ν����Ӧģʽ���û��趨ֵ���ᱻ����
                 * �������˳���ť��clear_setvalue_flag���ظ�=0
                 */

                /*ע��
                 *�û��趨ֵ��dac8571_out��������ͬ�ĸ�� �˴���clear_setvalue_flag�������������dac8571_out�ģ������˳���dac8571_outȷʵ��������
                 *�������������ʾ����λ����ʾֵ�����򽫲�����ֳ�����0~9������Ч��
                 */
                draw_focus(&pos, &CC_value, 5, clear_setvalue_flag);
                clear_setvalue_flag = 0;
            }
        }
    }
}

void draw_interface(void)
{
    draw_mode(); //ģʽѡ��ͼ�λ���
    while (1)
    {
        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //������������
        {
            if ((tp_dev.x > 44) && (tp_dev.y > 54) && (tp_dev.x < 276) && (tp_dev.y < 119))         //CC_Mode������
            {
                switch_load_voltage_to_CC;         //�л����ص�ѹ��CC��·
                DA_IN_off;         //�ر�����DA����ͨ��
                CC_Mode_DA_IN_on;         //����CC��·DA����ͨ��
                CC_Mode();         //CCģʽ
            }
            else if ((tp_dev.x > 44) && (tp_dev.y > 135) && (tp_dev.x < 276) && (tp_dev.y < 200))         //CV_Mode������
            {
                switch_load_voltage_to_CV;         //�л����ص�ѹ��CV��·
                DA_IN_off;         //�ر�����DA����ͨ��
                CV_Mode_DA_IN_on;         //����CV��·DA����ͨ��
                CV_Mode();         //CVģʽ
            }
            else if ((tp_dev.x > 44) && (tp_dev.y > 214) && (tp_dev.x < 276) && (tp_dev.y < 281))    //Developer_Mode������
            {
                Developer_Mode();  //������ģʽ
            }
            else if ((tp_dev.x > 299) && (tp_dev.y > 54) && (tp_dev.x < 450) && (tp_dev.y < 119))    //CR_Mode������
            {
                switch_load_voltage_to_CC;         //�л����ص�ѹ��CC��·
                DA_IN_off;         //�ر�����DA����ͨ��
                CC_Mode_DA_IN_on;         //����CC��·DA����ͨ��
                CR_Mode();  //CRģʽ
            }
            else if ((tp_dev.x > 299) && (tp_dev.y > 135) && (tp_dev.x < 450) && (tp_dev.y < 200))    //CP_Mode������
            {
                switch_load_voltage_to_CC;         //�л����ص�ѹ��CC��·
                DA_IN_off;         //�ر�����DA����ͨ��
                CC_Mode_DA_IN_on;         //����CC��·DA����ͨ��
                CP_Mode();  //CPģʽ
            }
            else if ((tp_dev.x > 299) && (tp_dev.y > 214) && (tp_dev.x < 450) && (tp_dev.y < 281))         //More...������
            {
                more();
            }
            else
                ;
        }
    }
}

void draw_start()
{
    LCD_Clear(BLACK); //��ʾ֮ǰ��������Ļ
    draw_personal_information(); //��ʾ˽����Ϣ
    Show_Str(325, 147, RED, BLACK, "��ʼʹ��", 24, 1, 1); //��ʼʹ��������ɫ
    while (1)
    {
        tp_dev.scan(0); //����ʱ����Ļ״̬��������ṹ����
        if (tp_dev.sta & TP_PRES_DOWN)         //������������
        {
            if ((tp_dev.x > 294) && (tp_dev.y > 97) && (tp_dev.x < 450) && (tp_dev.y < 224))         //��ʼʹ�ñ�����
                draw_interface();         //����ģʽѡ�����
        }
    }
}

