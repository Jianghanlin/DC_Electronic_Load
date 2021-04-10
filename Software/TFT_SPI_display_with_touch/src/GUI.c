/*
 * GUI.c
 *
 *  Created on: 2021年1月4日
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
    LCD_Fill(0, 5, 470, 320, BLACK); //显示之前先清理屏幕

    Gui_StrCenter(0, 10, WHITE, BLUE, "模式选择", 32, 1, 1); //居中显示模式选择

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

    gui_circle(447, 33, RED, 23, 1); //外切矩形坐标是424，10，470，56
    LCD_DrawboldLine(434, 20, 460, 46, 2); //叉叉符号
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
    clear_interface(); //显示之前先清理屏幕,调试完这个界面后记得改回来
    //绘制退出按钮和具体模式显示背景
    LCD_Fill(10, 10, 133, 56, BLUE1); //具体模式显示背景
    Show_Str(20, 20, WHITE, WHITE, "CC Mode", 32, 1, 0);    //显示CC Mode
    draw_return_buttom(); //绘制退出按钮
    LCD_DrawboldLine(10, 71, 470, 71, 4);    //绘制分隔线
    Show_Str(10, 81, BLACK, WHITE, "Current Adjusting Area", 24, 0, 1);    //显示Current adjusting area
    Show_Str(21, 115, WHITE, BLACK, "Set Current", 16, 1, 1);    //显示Voltage adjusting area
    Show_Str(55, 130, WHITE, BLACK, "Value:", 16, 1, 1);    //显示Voltage adjusting area

    gui_circle(155, 144, WHITE, 2, 1); //外切矩形坐标是424，10，470，56
    LCD_Fill(124, 120, 146, 143, WHITE);
    LCD_Fill(164, 120, 186, 143, WHITE);
    LCD_Fill(199, 120, 221, 143, WHITE);
    LCD_Fill(234, 120, 256, 143, WHITE);    //绘制中间矩形

    LCD_ShowNum(128, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(168, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(203, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(238, 120, BLACK, WHITE, 0, 1, 24, 1, 1);    //绘制初始数字

    LCD_ShowChar_2412(270, 120, WHITE, BLACK, 'A', 32, 1, 1);    //绘制单位

    LCD_Fill(345, 116, 403, 145, 0x397b); //确定键显示背景
    Show_Str(350, 120, WHITE, BLACK, "Confirm", 24, 1, 1);    //显示确定按钮文字

    LCD_DrawboldLine(10, 158, 470, 158, 4);    //绘制分隔线
    Show_Str(10, 168, BLACK, WHITE, "Monitoring area", 24, 0, 1);    //显示Voltage adjusting area
    Show_Str(21, 210, WHITE, BLACK, "DAC8571 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    // Show_Str(21, 241, WHITE, BLACK, "ADC1 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    //Show_Str(21, 272, WHITE, BLACK, "ADC2 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    Show_Str(240, 210, WHITE, BLACK, "I Value:       A", 24, 1, 1);    //显示Voltage adjusting area
    Show_Str(240, 241, WHITE, BLACK, "V Value:       V", 24, 1, 1);    //显示Voltage adjusting area
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled

}

void draw_interface2(void)
{
    clear_interface(); //显示之前先清理屏幕,调试完这个界面后记得改回来
    //绘制退出按钮和具体模式显示背景
    LCD_Fill(10, 10, 133, 56, BLUE1); //具体模式显示背景
    Show_Str(20, 20, WHITE, WHITE, "CV Mode", 32, 1, 0);    //显示CC Mode
    //绘制退出按钮和具体模式显示背景
    draw_return_buttom(); //绘制退出按钮
    LCD_DrawboldLine(10, 71, 470, 71, 4);    //绘制分隔线
    Show_Str(10, 81, BLACK, WHITE, "Voltage Adjusting Area", 24, 0, 1);    //显示Voltage Adjusting Area
    Show_Str(21, 115, WHITE, BLACK, "Set Voltage", 16, 1, 1);    //显示Voltage adjusting area
    Show_Str(55, 130, WHITE, BLACK, "Value:", 16, 1, 1);    //显示Voltage adjusting area

    gui_circle(155, 144, WHITE, 2, 1); //外切矩形坐标是424，10，470，56
    LCD_Fill(124, 120, 146, 143, WHITE);
    LCD_Fill(164, 120, 186, 143, WHITE);
    LCD_Fill(199, 120, 221, 143, WHITE);
    LCD_Fill(234, 120, 256, 143, WHITE);    //绘制中间矩形

    /*
     LCD_Fill(124, 78, 146, 108, WHITE);    //第2、4列可调
     LCD_Fill(164, 78, 186, 108, WHITE);
     LCD_Fill(199, 78, 221, 108, WHITE);
     LCD_Fill(234, 78, 256, 108, WHITE);
     LCD_Fill(124, 155, 146, 185, WHITE);
     LCD_Fill(164, 155, 186, 185, WHITE);
     LCD_Fill(199, 155, 221, 185, WHITE);
     LCD_Fill(234, 155, 256, 185, WHITE);    //绘制增减按钮区域，可视化，若后期想要调试，取消注释即可
     */

    LCD_ShowNum(128, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(168, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(203, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(238, 120, BLACK, WHITE, 0, 1, 24, 1, 1);    //绘制初始数字

    LCD_ShowChar_2412(270, 120, WHITE, BLACK, 'V', 32, 1, 1);    //绘制单位

    LCD_Fill(345, 116, 403, 145, 0x397b); //确定键显示背景
    Show_Str(350, 120, WHITE, BLACK, "Confirm", 24, 1, 1);    //显示确定按钮文字

    LCD_DrawboldLine(10, 158, 470, 158, 4);    //绘制分隔线
    Show_Str(10, 168, BLACK, WHITE, "Monitoring area", 24, 0, 1);    //显示Voltage adjusting area
    Show_Str(21, 210, WHITE, BLACK, "DAC8571 Value:         V", 16, 1, 1);
    // Show_Str(21, 241, WHITE, BLACK, "ADC3 Value:         V", 16, 1, 1);
    Show_Str(240, 241, WHITE, BLACK, "V Value:       V", 24, 1, 1);
}

void draw_interface3(void)
{
    TIMER_A0->CCTL[0] &= ~ TIMER_A_CCTLN_CCIE; // TACCR0 interrupt disabled

    clear_interface(); //显示之前先清理屏幕,调试完这个界面后记得改回来

    //绘制退出按钮和具体模式显示背景
    LCD_Fill(10, 10, 200, 56, BLUE1); //具体模式显示背景
    Show_Str(20, 20, WHITE, WHITE, "Developer Mode", 24, 1, 1);    //显示Developer Mode
    draw_return_buttom(); //绘制退出按钮
    LCD_DrawboldLine(10, 71, 470, 71, 4);    //绘制分隔线
    Show_Str(10, 81, BLACK, WHITE, "Voltage adjusting area", 24, 0, 1);    //显示Voltage adjusting area
    Show_Str(21, 115, WHITE, BLACK, "Set DAC8571", 16, 1, 1);    //显示Voltage adjusting area
    Show_Str(55, 130, WHITE, BLACK, "Output:", 16, 1, 1);    //显示Voltage adjusting area

    gui_circle(155, 144, WHITE, 2, 1); //外切矩形坐标是424，10，470，56
    LCD_Fill(124, 120, 146, 143, WHITE);
    LCD_Fill(164, 120, 186, 143, WHITE);
    LCD_Fill(199, 120, 221, 143, WHITE);
    LCD_Fill(234, 120, 256, 143, WHITE);    //绘制中间矩形

    /*
     LCD_Fill(124, 78, 146, 108, WHITE);    //第2、4列可调
     LCD_Fill(164, 78, 186, 108, WHITE);
     LCD_Fill(199, 78, 221, 108, WHITE);
     LCD_Fill(234, 78, 256, 108, WHITE);
     LCD_Fill(124, 155, 146, 185, WHITE);
     LCD_Fill(164, 155, 186, 185, WHITE);
     LCD_Fill(199, 155, 221, 185, WHITE);
     LCD_Fill(234, 155, 256, 185, WHITE);    //绘制增减按钮区域，可视化，若后期想要调试，取消注释即可
     */

    LCD_ShowNum(128, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(168, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(203, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(238, 120, BLACK, WHITE, 0, 1, 24, 1, 1);    //绘制初始数字

    LCD_ShowChar_2412(270, 120, WHITE, BLACK, 'V', 32, 1, 1);    //绘制单位

    LCD_Fill(345, 116, 403, 145, 0x397b); //确定键显示背景
    Show_Str(350, 120, WHITE, BLACK, "Confirm", 24, 1, 1);    //显示确定按钮文字

    LCD_DrawboldLine(10, 158, 470, 158, 4);    //绘制分隔线
    Show_Str(10, 168, BLACK, WHITE, "Monitoring area", 24, 0, 1);    //显示Voltage adjusting area
    Show_Str(21, 210, WHITE, BLACK, "DAC8571 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    Show_Str(21, 241, WHITE, BLACK, "ADC1 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    Show_Str(21, 272, WHITE, BLACK, "ADC2 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    Show_Str(240, 210, WHITE, BLACK, "I Value:       A", 24, 1, 1);    //显示Voltage adjusting area
    Show_Str(240, 241, WHITE, BLACK, "V Value:       V", 24, 1, 1);    //显示Voltage adjusting area

    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
}

void draw_interface4(void)
{
    TIMER_A0->CCTL[0] &= ~ TIMER_A_CCTLN_CCIE;
    clear_interface(); //显示之前先清理屏幕,调试完这个界面后记得改回来
    //绘制退出按钮和具体模式显示背景
    LCD_Fill(10, 10, 133, 56, BLUE1); //具体模式显示背景
    Show_Str(20, 20, WHITE, WHITE, "CR Mode", 32, 1, 0);    //显示CC Mode
    draw_return_buttom(); //绘制退出按钮
    LCD_DrawboldLine(10, 71, 470, 71, 4);    //绘制分隔线
    Show_Str(10, 81, BLACK, WHITE, "Resistance Adjusting Area", 24, 0, 1);    //显示Current adjusting area
    Show_Str(10, 115, WHITE, BLACK, "Set Resistance", 16, 1, 1);    //显示Voltage adjusting area
    Show_Str(60, 130, WHITE, BLACK, "Value:", 16, 1, 1);    //显示Voltage adjusting area

    gui_circle(228, 144, WHITE, 2, 1); //绘制小数点
    LCD_Fill(124, 120, 146, 143, WHITE);
    LCD_Fill(164, 120, 186, 143, WHITE);
    LCD_Fill(199, 120, 221, 143, WHITE);
    LCD_Fill(234, 120, 256, 143, WHITE);    //绘制中间矩形

    LCD_ShowNum(128, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(168, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(203, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(238, 120, BLACK, WHITE, 0, 1, 24, 1, 1);    //绘制初始数字

    Show_Str(270, 120, WHITE, BLACK, "Ohm", 32, 1, 1);    ////绘制单位

    LCD_Fill(345, 116, 403, 145, 0x397b); //确定键显示背景
    Show_Str(350, 120, WHITE, BLACK, "Confirm", 24, 1, 1);    //显示确定按钮文字

    LCD_DrawboldLine(10, 158, 470, 158, 4);    //绘制分隔线
    Show_Str(10, 168, BLACK, WHITE, "Monitoring area", 24, 0, 1);    //显示Voltage adjusting area
    Show_Str(21, 210, WHITE, BLACK, "DAC8571 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    // Show_Str(21, 241, WHITE, BLACK, "ADC1 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    //Show_Str(21, 272, WHITE, BLACK, "ADC2 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    Show_Str(240, 210, WHITE, BLACK, "I Value:       A", 24, 1, 1);    //显示Voltage adjusting area
    Show_Str(240, 241, WHITE, BLACK, "V Value:       V", 24, 1, 1);    //显示Voltage adjusting area
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled

}

void draw_interface5(void)
{
    TIMER_A0->CCTL[0] &= ~ TIMER_A_CCTLN_CCIE;
    clear_interface(); //显示之前先清理屏幕,调试完这个界面后记得改回来
    //绘制退出按钮和具体模式显示背景
    LCD_Fill(10, 10, 133, 56, BLUE1); //具体模式显示背景
    Show_Str(20, 20, WHITE, WHITE, "CP Mode", 32, 1, 0);    //显示CC Mode
    draw_return_buttom(); //绘制退出按钮
    LCD_DrawboldLine(10, 71, 470, 71, 4);    //绘制分隔线
    Show_Str(10, 81, BLACK, WHITE, "Power Adjusting Area", 24, 0, 1);    //显示Current adjusting area
    Show_Str(21, 115, WHITE, BLACK, "Set Power", 16, 1, 1);    //显示Voltage adjusting area
    Show_Str(55, 130, WHITE, BLACK, "Value:", 16, 1, 1);    //显示Voltage adjusting area

    gui_circle(155, 144, WHITE, 2, 1); //外切矩形坐标是424，10，470，56
    LCD_Fill(124, 120, 146, 143, WHITE);
    LCD_Fill(164, 120, 186, 143, WHITE);
    LCD_Fill(199, 120, 221, 143, WHITE);
    LCD_Fill(234, 120, 256, 143, WHITE);    //绘制中间矩形

    LCD_ShowNum(128, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(168, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(203, 120, BLACK, WHITE, 0, 1, 24, 1, 1);
    LCD_ShowNum(238, 120, BLACK, WHITE, 0, 1, 24, 1, 1);    //绘制初始数字

    LCD_ShowChar_2412(270, 120, WHITE, BLACK, 'W', 32, 1, 1);    //绘制单位

    LCD_Fill(345, 116, 403, 145, 0x397b); //确定键显示背景
    Show_Str(350, 120, WHITE, BLACK, "Confirm", 24, 1, 1);    //显示确定按钮文字

    LCD_DrawboldLine(10, 158, 470, 158, 4);    //绘制分隔线
    Show_Str(10, 168, BLACK, WHITE, "Monitoring area", 24, 0, 1);    //显示Voltage adjusting area
    Show_Str(21, 210, WHITE, BLACK, "DAC8571 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    // Show_Str(21, 241, WHITE, BLACK, "ADC1 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    // Show_Str(21, 272, WHITE, BLACK, "ADC2 Value:         V", 16, 1, 1);    //显示Voltage adjusting area
    Show_Str(240, 210, WHITE, BLACK, "I Value:       A", 24, 1, 1);    //显示Voltage adjusting area
    Show_Str(240, 241, WHITE, BLACK, "V Value:       V", 24, 1, 1);    //显示Voltage adjusting area
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled

}

void more(void)
{
    uint8_t flag = 0;
    clear_interface(); //显示之前先清理屏幕
    //绘制退出按钮和具体模式显示背景
    LCD_Fill(10, 10, 200, 56, BLUE1); //具体模式显示背景
    Show_Str(20, 20, WHITE, WHITE, "More Settings", 24, 1, 1);    //显示More Settings
    draw_return_buttom(); //绘制退出按钮
    Show_Str(20, 80, WHITE, WHITE, "大家好,我是江瀚林,目前显示屏的驱动固件是Rev1.0,后续有待", 16, 1, 1);    //显示More Settings
    while (flag == 0)
    {
        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //触摸屏被按下
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56)) //退出键外切矩形坐标是424，10，470，56     //CC_Mode被按下
            {
                flag = 1;
                draw_mode(); //模式选择图形绘制
            }
        }
    }
}

void draw_personal_information()
{
    Gui_StrCenter(0, 5, WHITE, BLUE, "直流电子负载", 32, 1, 1); //居中显示课题名称
    Gui_Drawbmp_JHL(20, 67, gImage_jianghanlin); //显示江瀚林的个人一寸照以及个人信息
    Show_Str(111, 80, BLUE, YELLOW, "软件设计", 24, 0, 0);
    Show_Str(111, 107, WHITE, WHITE, "姓名:江瀚林", 16, 1, 0);
    Show_Str(111, 124, WHITE, WHITE, "学号:Xb17610107", 16, 1, 0);
    Show_Str(111, 141, WHITE, WHITE, "班级:17电子信息工程1", 16, 1, 0);
    Gui_Drawbmp_LL(15, 205, gImage_liulu); //显示江瀚林的个人一寸照以及个人信息
    Show_Str(111, 214, BLUE, YELLOW, "硬件设计", 24, 0, 0);
    Show_Str(111, 241, WHITE, WHITE, "姓名:刘露", 16, 1, 0);
    Show_Str(111, 258, WHITE, WHITE, "学号:Xb17610124", 16, 1, 0);
    Show_Str(111, 275, WHITE, WHITE, "班级:17电子信息工程1", 16, 1, 0);
    LCD_Fill(294, 97, 450, 224, GREEN); //开始使用矩形按钮窗口
}

//传入参数是指针类型的，因为如果是一般的类型，执行完子函数后的值会被释放，从根本上来说并没有改变原来位置的值，引入指针型的变量将会从根本上改变原来位置的值
//第二个传入参数是设定值
void draw_focus(uint8_t *pos, volatile float *setvalue, uint8_t mode, uint8_t clear)
{
    float trans = 0; //只用来作为中间变量，解决一些复杂的运算
    static uint8_t gewei = 0, xiaoshu1 = 0, xiaoshu2 = 0, xiaoshu3 = 0;
    if (clear == 1) //后几次经进入需要清空各位的值，否则显示值与实际值完全不对应
    {
        gewei = xiaoshu1 = xiaoshu2 = xiaoshu3 = 0;
    }
    if ((tp_dev.x > 124) && (tp_dev.y > 120) && (tp_dev.x < 146) && (tp_dev.y < 143)) //选中了gewei
    {
        if (*pos != 0) //绘制当前位增减箭头，同时清除其他位的增减箭头
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
        *pos = 1; //当前选中gewei
        Fill_Triangel(135, 113 - 3, 123, 119 - 3, 147, 119 - 3, RED);
        LCD_ShowNum(124 + 4, 120, BLACK, YELLOW, gewei, 1, 24, 0, 1);
        Fill_Triangel(123, 148 - 1, 147, 148 - 1, 135, 154 - 1, RED);
    }
    else if ((tp_dev.x > 164) && (tp_dev.y > 120) && (tp_dev.x < 186) && (tp_dev.y < 143)) //选中了xiaoshu1
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
                LCD_ShowNum(234 + 4, 120, BLACK, WHITE, xiaoshu3, 1, 24, 0, 1);    //绘制中间矩形
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
    else if ((tp_dev.x > 199) && (tp_dev.y > 120) && (tp_dev.x < 221) && (tp_dev.y < 143)) //选中了xiaoshu2
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
            LCD_ShowNum(234 + 4, 120, BLACK, WHITE, xiaoshu3, 1, 24, 0, 1);    //绘制中间矩形
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
    else if ((tp_dev.x > 234) && (tp_dev.y > 120) && (tp_dev.x < 256) && (tp_dev.y < 143)) //选中了xiaoshu3
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
        Fill_Triangel(245, 113 - 3, 233, 119 - 3, 257, 119 - 3, RED);    //绘制上排三角形
        LCD_ShowNum(234 + 4, 120, BLACK, YELLOW, xiaoshu3, 1, 24, 0, 1);    //绘制中间矩形
        Fill_Triangel(233, 148 - 1, 257, 148 - 1, 245, 154 - 1, RED);    //绘制下排三角形
    }    //电压位选择代码块结束
    //电压位增减代码块开始
    else if ((tp_dev.x > 124) && (tp_dev.x < 146) && (*pos == 1))    //个位增减代码
    {
        if ((tp_dev.y > 78) && (tp_dev.y < 108))
        {
            if (gewei < 9)    //每位最高不能超过9,此处原本应该是(xiaoshu1 >= 0) && (xiaoshu1 < 9)，但是无符号默认>=0,所以前半句无意义，省略
            {
                gewei++;
            }
            LCD_ShowNum(124 + 4, 120, BLACK, YELLOW, gewei, 1, 24, 0, 1);
        }
        else if ((tp_dev.y > 155) && (tp_dev.y < 185))
        {
            if (gewei > 0)    //每位最低不能小于0
            {
                gewei--;
            }
            LCD_ShowNum(124 + 4, 120, BLACK, YELLOW, gewei, 1, 24, 0, 1);
        }
        else
            ;
    }
    else if ((tp_dev.x > 164) && (tp_dev.x < 186) && (*pos == 2))    //xiaoshu1增减代码
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
    else if ((tp_dev.x > 199) && (tp_dev.x < 221) && (*pos == 3))    //xiaoshu2增减代码
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
    else if ((tp_dev.x > 234) && (tp_dev.x < 256) && (*pos == 4))    //xiaoshu3增减代码
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
    //增减代码块结束
    else if ((tp_dev.x > 345) && (tp_dev.y > 116) && (tp_dev.x < 403) && (tp_dev.y < 145))    //确认按键执行函数
    {
        *setvalue = gewei + 0.1 * xiaoshu1 + 0.01 * xiaoshu2 + 0.001 * xiaoshu3;
        switch (mode)
        {
        case 1:
            if (*setvalue > 1.2)    //CC模式0.1~1.2A
            {
                Show_Str(300, 81, RED, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //显示Voltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //显示Voltage adjusting area
            }
            else
            {
                dac8571_out = 0.008 * (*setvalue) * (*setvalue) + 0.9707 * (*setvalue) - 0.0229;  //DAC8571输出关于实际电流的拟合公式
                DAC8571_OUT(dac8571_out);
                Show_Str(300, 81, GREEN, BLACK, "Set Successful!!", 16, 0, 1);    //显示Voltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Successful!!", 16, 0, 1);    //显示Voltage adjusting area
            }
            break;
        case 2:
            if (*setvalue > 3)    //CV模式要求1~3V
            {
                Show_Str(300, 81, RED, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //显示Voltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //显示Voltage adjusting area
            }
            else
            {
                dac8571_out = -0.0183 * (*setvalue) * (*setvalue) + 0.5446 * (*setvalue) - 0.088; //DAC8571输出关于实际恒压的拟合公式
                DAC8571_OUT(dac8571_out);
                Show_Str(300, 81, GREEN, BLACK, "Set Successful!!", 16, 0, 1);    //显示Voltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Successful!!", 16, 0, 1);    //显示Voltage adjusting area
            }
            break;
        case 3:
            *setvalue = (*setvalue) * 100.0;
            if (*setvalue < 20)    //CR模式要求10~100欧
            {
                Show_Str(300, 81, RED, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //显示Voltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //显示Voltage adjusting area
            }
            else
            {
                dac8571_out = ADC1_feedback / (*setvalue);    //根据设定的电阻值，换算电流
                dac8571_out = 0.008 * dac8571_out * dac8571_out + 0.9707 * dac8571_out - 0.0229;  //DAC8571输出关于实际电流的拟合公式
                DAC8571_OUT(dac8571_out);
                Show_Str(330, 81, GREEN, BLACK, "Set Successful!!", 16, 0, 1);    //显示Voltage adjusting area
                delay_ms(340);
                Show_Str(330, 81, BLACK, BLACK, "Set Successful!!", 16, 0, 1);    //显示Voltage adjusting area
            }
            break;
        case 4:
            trans = (*setvalue) / ADC1_feedback;    //I=P/U
            if ((*setvalue > 6) || (trans > 1.2))    //CP模式1~6W
            {
                Show_Str(300, 81, RED, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //显示Voltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Unsuccessful!!", 16, 0, 1);    //显示Voltage adjusting area
            }
            else
            {
                dac8571_out = 0.008 * trans * trans + 0.9707 * trans - 0.0229;  //DAC8571输出关于实际电流的拟合公式
                DAC8571_OUT(dac8571_out);
                Show_Str(300, 81, GREEN, BLACK, "Set Successful!!", 16, 0, 1);    //显示Voltage adjusting area
                delay_ms(340);
                Show_Str(300, 81, BLACK, BLACK, "Set Successful!!", 16, 0, 1);    //显示Voltage adjusting area
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
    uint8_t pos = 0, exit_mode_flag = 0;    //pos用来记录当前按下的是那个位，flag用来记录退出按钮有没有被按下
    draw_interface1();         //绘制固定元素
    while (exit_mode_flag == 0)
    {
        display_temperature();         //显示监控温度
        monitor_voltage_CC();         //显示监控电压

        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //触摸屏被按下
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56))    //退出键外切矩形坐标是424，10，470，56
            {
                DA_IN_off;    //关闭所有DA输入通道
                switch_load_voltage_to_CC;    //默认将负载电压切换至CC
                DAC8571_OUT(0);    //一旦退出详细的界面，DAC8571输出归零
                dac8571_out = 0;    //不清零的话，在涉及加减DAC8571的操作时会造成累计，所以要归零
                CC_value = 0;
                exit_mode_flag = 1;    //记录退出按钮有没有被按下
                clear_setavlue_flag = 1;    //清除调节显示值标志
                draw_mode(); //模式选择图形绘制
            }
            else
            {
                draw_focus(&pos, &CC_value, 1, clear_setavlue_flag); //传入参数是pos的地址，因为指针参数可以根本上地改变原来位置的值,第二个参数是要调节DAC8571输出的值
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
    uint8_t pos = 0, exit_mode_flag = 0;    //pos用来记录当前按下的是那个位，flag用来记录退出按钮有没有被按下
    draw_interface2();         //绘制固定元素
    while (exit_mode_flag == 0)
    {
        monitor_voltage_CV();         //显示监控电压
        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //触摸屏被按下
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56))    //退出键外切矩形坐标是424，10，470，56
            {
                DA_IN_off;    //关闭所有DA输入通道
                switch_load_voltage_to_CC;
                DAC8571_OUT(0);    //一旦退出详细的界面，DAC8571输出归零
                dac8571_out = 0;    //不清零的话，在涉及加减DAC8571的操作时会造成累计，所以要归零
                CV_value = 0;
                exit_mode_flag = 1;    //记录退出按钮有没有被按下
                clear_setavlue_flag = 1;    //清除调节显示值标志

                draw_mode(); //模式选择图形绘制
            }
            else
            {
                draw_focus(&pos, &CV_value, 2, clear_setavlue_flag); //传入参数是pos的地址，因为指针参数可以根本上地改变原来位置的值,第二个参数是要调节DAC8571输出的值
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
    uint8_t pos = 0, exit_mode_flag = 0;    //pos用来记录当前按下的是那个位，flag用来记录退出按钮有没有被按下
    draw_interface4();         //绘制固定元素
    while (exit_mode_flag == 0)
    {
        display_temperature();         //显示监控温度
        monitor_voltage_CR();         //显示监控电压

        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //触摸屏被按下
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56))    //退出键外切矩形坐标是424，10，470，56
            {
                DA_IN_off;    //关闭所有DA输入通道
                switch_load_voltage_to_CC;    //默认将负载电压切换至CC
                DAC8571_OUT(0);    //一旦退出详细的界面，DAC8571输出归零
                dac8571_out = 0;    //不清零的话，在涉及加减DAC8571的操作时会造成累计，所以要归零
                CR_value = 0;
                exit_mode_flag = 1;    //记录退出按钮有没有被按下
                clear_setavlue_flag = 1;    //清除调节显示值标志
                draw_mode(); //模式选择图形绘制
            }
            else
            {
                draw_focus(&pos, &CR_value, 3, clear_setavlue_flag); //传入参数是pos的地址，因为指针参数可以根本上地改变原来位置的值,第二个参数是要调节DAC8571输出的值
                clear_setavlue_flag = 0;
            }
        }
        /*        ADC2_feedback = average_voltage_caculate(6, 5);
         CC_value_fact = 0.0192 * ADC2_feedback * ADC2_feedback + 0.9032 * ADC2_feedback + 0.006;
         dac8571_out += Incremental_PI(CC_value_fact, CC_value); //增量式PID函数，返回值是增量
         DAC8571_OUT(dac8571_out);*/
    }
}

void CP_Mode()
{
    static uint8_t clear_setavlue_flag = 0;
    uint8_t pos = 0, exit_mode_flag = 0;    //pos用来记录当前按下的是那个位，flag用来记录退出按钮有没有被按下
    draw_interface5();         //绘制固定元素
    while (exit_mode_flag == 0)
    {
        display_temperature();         //显示监控温度
        monitor_voltage_CP();         //显示监控电压

        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //触摸屏被按下
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56))    //退出键外切矩形坐标是424，10，470，56
            {
                DA_IN_off;    //关闭所有DA输入通道
                switch_load_voltage_to_CC;    //默认将负载电压切换至CC
                DAC8571_OUT(0);    //一旦退出详细的界面，DAC8571输出归零
                dac8571_out = 0;    //不清零的话，在涉及加减DAC8571的操作时会造成累计，所以要归零
                CP_value = 0;
                exit_mode_flag = 1;    //记录退出按钮有没有被按下
                clear_setavlue_flag = 1;    //清除调节显示值标志
                draw_mode(); //模式选择图形绘制
            }
            else
            {
                draw_focus(&pos, &CP_value, 4, clear_setavlue_flag); //传入参数是pos的地址，因为指针参数可以根本上地改变原来位置的值,第二个参数是要调节DAC8571输出的值
                clear_setavlue_flag = 0;
            }
        }
    }
}

void Developer_Mode()
{
    static uint8_t clear_setvalue_flag = 0; //用户设定值清除标志位
    uint8_t pos = 0, exit_mode_flag = 0;    //pos用来记录当前按下的是那个位，flag用来记录退出按钮有没有被按下

    draw_interface3();         //绘制固定元素

    switch_load_voltage_to_CC;         //切换负载电压至CC电路
    DA_IN_off;         //关闭所有DA输入通道
    CC_Mode_DA_IN_on;         //开启CC电路DA输入通道

    while (exit_mode_flag == 0)
    {
        display_temperature();         //显示监控温度
        monitor_voltage_Developer();             //默认监控4通道的电压值，后续应该会重写这块
        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //触摸屏被按下
        {
            if ((tp_dev.x > 424) && (tp_dev.y > 10) && (tp_dev.x < 470) && (tp_dev.y < 56))    //退出键外切矩形坐标是424，10，470，56
            {
                DAC8571_OUT(0);    //一旦退出详细的界面，DAC8571输出归零
                dac8571_out = 0;    //不清零的话，在涉及加减DAC8571的操作时会造成累计，所以要归零
                CC_value = 0;
                exit_mode_flag = 1;    //记录退出按钮有没有被按下
                clear_setvalue_flag = 1;    //清除调节显示值标志

                draw_mode(); //模式选择图形绘制
            }
            else
            {
                /*
                 * 第1个传入参数是pos的地址，因为指针参数可以根本上地改变原来位置的值,第2个参数是要调节DAC8571输出的值，第3个传入参数是选择的运行模式，第4个传入参数是设定值清楚标志位
                 * 由于dac8571_out为全局变量，为了解决退出后用户设定值仍然保留，引入clear_setvalue_flag-->用户设定值清除标志位
                 * 按下退出按钮，clear_setvalue_flag=1，下一次进入对应模式，用户设定值将会被清零
                 * 不按下退出按钮，clear_setvalue_flag被重复=0
                 */

                /*注意
                 *用户设定值和dac8571_out是两个不同的概念， 此处的clear_setvalue_flag并不是用来清除dac8571_out的，按下退出后，dac8571_out确实必须清零
                 *而是用来清除显示屏各位的显示值，否则将不会出现长按后0~9递增的效果
                 */
                draw_focus(&pos, &CC_value, 5, clear_setvalue_flag);
                clear_setvalue_flag = 0;
            }
        }
    }
}

void draw_interface(void)
{
    draw_mode(); //模式选择图形绘制
    while (1)
    {
        tp_dev.scan(0);
        if (tp_dev.sta & TP_PRES_DOWN)         //触摸屏被按下
        {
            if ((tp_dev.x > 44) && (tp_dev.y > 54) && (tp_dev.x < 276) && (tp_dev.y < 119))         //CC_Mode被按下
            {
                switch_load_voltage_to_CC;         //切换负载电压至CC电路
                DA_IN_off;         //关闭所有DA输入通道
                CC_Mode_DA_IN_on;         //开启CC电路DA输入通道
                CC_Mode();         //CC模式
            }
            else if ((tp_dev.x > 44) && (tp_dev.y > 135) && (tp_dev.x < 276) && (tp_dev.y < 200))         //CV_Mode被按下
            {
                switch_load_voltage_to_CV;         //切换负载电压至CV电路
                DA_IN_off;         //关闭所有DA输入通道
                CV_Mode_DA_IN_on;         //开启CV电路DA输入通道
                CV_Mode();         //CV模式
            }
            else if ((tp_dev.x > 44) && (tp_dev.y > 214) && (tp_dev.x < 276) && (tp_dev.y < 281))    //Developer_Mode被按下
            {
                Developer_Mode();  //开发者模式
            }
            else if ((tp_dev.x > 299) && (tp_dev.y > 54) && (tp_dev.x < 450) && (tp_dev.y < 119))    //CR_Mode被按下
            {
                switch_load_voltage_to_CC;         //切换负载电压至CC电路
                DA_IN_off;         //关闭所有DA输入通道
                CC_Mode_DA_IN_on;         //开启CC电路DA输入通道
                CR_Mode();  //CR模式
            }
            else if ((tp_dev.x > 299) && (tp_dev.y > 135) && (tp_dev.x < 450) && (tp_dev.y < 200))    //CP_Mode被按下
            {
                switch_load_voltage_to_CC;         //切换负载电压至CC电路
                DA_IN_off;         //关闭所有DA输入通道
                CC_Mode_DA_IN_on;         //开启CC电路DA输入通道
                CP_Mode();  //CP模式
            }
            else if ((tp_dev.x > 299) && (tp_dev.y > 214) && (tp_dev.x < 450) && (tp_dev.y < 281))         //More...被按下
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
    LCD_Clear(BLACK); //显示之前先清理屏幕
    draw_personal_information(); //显示私人信息
    Show_Str(325, 147, RED, BLACK, "开始使用", 24, 1, 1); //开始使用字体颜色
    while (1)
    {
        tp_dev.scan(0); //检测此时的屏幕状态，保存进结构体中
        if (tp_dev.sta & TP_PRES_DOWN)         //触摸屏被按下
        {
            if ((tp_dev.x > 294) && (tp_dev.y > 97) && (tp_dev.x < 450) && (tp_dev.y < 224))         //开始使用被按下
                draw_interface();         //绘制模式选择界面
        }
    }
}

