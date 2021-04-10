//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103RCT6,����ԭ��MiniSTM32������,��Ƶ72MHZ������12MHZ
//QDtech-TFTҺ������ for STM32 IOģ��
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com 
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/08/09
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
 //=========================================��Դ����================================================//
 //     LCDģ��                STM32��Ƭ��
 //      VCC          ��        DC5V/3.3V      //��Դ
 //      GND          ��          GND          //��Դ��
 //=======================================Һ���������߽���==========================================//
 //��ģ��Ĭ��������������ΪSPI����
 //     LCDģ��                STM32��Ƭ��
 //    SDI(MOSI)      ��          PB15         //Һ����SPI��������д�ź�
 //    SDO(MISO)      ��          PB14         //Һ����SPI�������ݶ��źţ��������Ҫ�������Բ�����
 //=======================================Һ���������߽���==========================================//
 //     LCDģ�� 					      STM32��Ƭ��
 //       LED         ��          PB9          //Һ������������źţ��������Ҫ���ƣ���5V��3.3V
 //       SCK         ��          PB13         //Һ����SPI����ʱ���ź�
 //      DC/RS        ��          PB10         //Һ��������/��������ź�
 //       RST         ��          PB12         //Һ������λ�����ź�
 //       CS          ��          PB11         //Һ����Ƭѡ�����ź�
 //=========================================������������=========================================//
 //���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
 //	   LCDģ��                STM32��Ƭ��
 //      T_IRQ        ��          PC10         //�����������ж��ź�
 //      T_DO         ��          PC2          //������SPI���߶��ź�
 //      T_DIN        ��          PC3          //������SPI����д�ź�
 //      T_CS         ��          PC13         //������Ƭѡ�����ź�
 //      T_CLK        ��          PC0          //������SPI����ʱ���ź�
 **************************************************************************************************/
/* @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 **************************************************************************************************/
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <touch.h>
#include "ST7796S.h"
#include "delay.h"
#include "math.h"
#include "24cxx.h"
#include "string.h"

_m_tp_dev tp_dev = { TP_Init, TP_Scan, TP_Adjust, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
//Ĭ��Ϊtouchtype=0������.
uint8_t CMD_RDX = 0XD0;
uint8_t CMD_RDY = 0X90;

/*****************************************************************************
 * @name       :void TP_Write_Byte(uint8_t num)
 * @date       :2018-08-09 
 * @function   :Write a byte data to the touch screen IC with SPI bus
 * @parameters :num:Data to be written
 * @retvalue   :None
 ******************************************************************************/
void TP_Write_Byte(uint8_t num)
{
    uint8_t count = 0;
    for (count = 0; count < 8; count++)
    {
        if (num & 0x80)
            TDIN_H;
        else
            TDIN_L;
        num <<= 1;
        TCLK_L;
        TCLK_H;		//��������Ч
    }
}

/*****************************************************************************
 * @name       :uint16_t TP_Read_AD(uint8_t CMD)
 * @date       :2018-08-09 
 * @function   :Reading adc values from touch screen IC with SPI bus
 * @parameters :CMD:Read command,0xD0 for x,0x90 for y
 * @retvalue   :Read data
 ******************************************************************************/
//ʹ��SPI���ߴӴ�����IC��ȡadcֵ
uint16_t TP_Read_AD(uint8_t CMD)
{
    uint8_t count = 0;
    uint16_t Num = 0;
    TCLK_L;		//������ʱ��
    TDIN_L; 	//����������
    TCS_L; 		//ѡ�д�����IC
    TP_Write_Byte(CMD); 		//����������
    delay_us(10); 		//ADS7846��ת��ʱ���Ϊ6us
    TCLK_L;
    delay_us(1);
    TCLK_H;		//��1��ʱ�ӣ����BUSY
    TCLK_L;
    for (count = 0; count < 16; count++)		//����16λ����,ֻ�и�12λ��Ч
    {
        Num <<= 1;
        TCLK_L;	//�½�����Ч
        TCLK_H;
        if (DOUT)
            Num++;
    }
    Num >>= 4;   	//ֻ�и�12λ��Ч.
    TCS_H;		//�ͷ�Ƭѡ
    return (Num);
//#endif
}

#define READ_TIMES 5 	//��ȡ����
#define LOST_VAL 1	  	//����ֵ
/*****************************************************************************
 * @name       :uint16_t TP_Read_XOY(uint8_t xy)
 * @date       :2018-08-09 
 * @function   :Read the touch screen coordinates (x or y),
 Read the READ_TIMES secondary data in succession and sort the data in ascending order,
 Then remove the lowest and highest number of LOST_VAL
 and take the average
 * @parameters :xy:Read command(CMD_RDX/CMD_RDY)
 * @retvalue   :Read data
 ******************************************************************************/
//��ȡ���������꣬������ȡREAD_TIMES�β�����������ݽ�������Ĭ�϶�ȡ5�Σ�Ȼ��ɾ��min��max��LOST_VAL����ȡƽ��ֵ
uint16_t TP_Read_XOY(uint8_t xy)
{
    uint16_t i, j;
    uint16_t buf[READ_TIMES];		//����
    uint16_t sum = 0;
    uint16_t temp;

    for (i = 0; i < READ_TIMES; i++)
        buf[i] = TP_Read_AD(xy);
    for (i = 0; i < READ_TIMES - 1; i++)		//����
    {
        for (j = i + 1; j < READ_TIMES; j++)
        {
            if (buf[i] > buf[j])		//��������
            {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }
    sum = 0;
    for (i = LOST_VAL; i < READ_TIMES - LOST_VAL; i++)		//ȥ�����ֵ����Сֵȡƽ��
        sum += buf[i];
    temp = sum / (READ_TIMES - 2 * LOST_VAL);
    return temp;		//����ֵ��ȡ��ƽ�������޳������Сֵ֮���ֵ
}

/*****************************************************************************
 * @name       :uint8_t TP_Read_XY(uint16_t *x,uint16_t *y)
 * @date       :2018-08-09 
 * @function   :Read touch screen x and y coordinates,
 The minimum value can not be less than 100
 * @parameters :x:Read x coordinate of the touch screen
 y:Read y coordinate of the touch screen
 * @retvalue   :0-fail,1-success
 ******************************************************************************/
//��ȡ��������x��y����,x,y����Сֵ����С��100
uint8_t TP_Read_XY(uint16_t *x, uint16_t *y)		//ָ�������Ϊ�����������Զ��庯��ִ����󽫲��ᱻ�ͷţ������ڼ���ȫ�ֱ��������ã������
{
    uint16_t xtemp, ytemp;		//x,y����ʱֵ
    xtemp = TP_Read_XOY(CMD_RDX);		//��ȡ��ǰ������x����
    ytemp = TP_Read_XOY(CMD_RDY);		//��ȡ��ǰ������y����
    //if(xtemp<100||ytemp<100)return 0;//����ʧ��
    *x = xtemp;
    *y = ytemp;
    return 1;		//�����ɹ�
}

#define ERR_RANGE 50 //��Χ 
/*****************************************************************************
 * @name       :uint8_t TP_Read_XY2(uint16_t *x,uint16_t *y)
 * @date       :2018-08-09 
 * @function   :Read the touch screen coordinates twice in a row, 
 and the deviation of these two times can not exceed ERR_RANGE,
 satisfy the condition, then think the reading is correct,
 otherwise the reading is wrong.
 This function can greatly improve the accuracy.
 * @parameters :x:Read x coordinate of the touch screen
 y:Read y coordinate of the touch screen
 * @retvalue   :0-fail,1-success
 ******************************************************************************/
uint8_t TP_Read_XY2(uint16_t *x, uint16_t *y)
{
    uint16_t x1, y1;
    uint16_t x2, y2;
    uint8_t flag;
    flag = TP_Read_XY(&x1, &y1);
    if (flag == 0)
        return (0);
    flag = TP_Read_XY(&x2, &y2);
    if (flag == 0)
        return (0);
    if (((x2 <= x1 && x1 < x2 + ERR_RANGE) || (x1 <= x2 && x2 < x1 + ERR_RANGE))		//ǰ�����β�����+-50��
    && ((y2 <= y1 && y1 < y2 + ERR_RANGE) || (y1 <= y2 && y2 < y1 + ERR_RANGE)))
    {
        *x = (x1 + x2) / 2;
        *y = (y1 + y2) / 2;
        return 1;
    }
    else
        return 0;
}

/*****************************************************************************
 * @name       :void TP_Drow_Touch_Point(uint16_t x,uint16_t y,uint16_t color)
 * @date       :2018-08-09 
 * @function   :Draw a touch point,Used to calibrate							
 * @parameters :x:Read x coordinate of the touch screen
 y:Read y coordinate of the touch screen
 color:the color value of the touch point
 * @retvalue   :None
 ******************************************************************************/
void TP_Drow_Touch_Point(uint16_t x, uint16_t y, uint16_t color)
{
    POINT_COLOR = color;
    LCD_DrawLine(x - 12, y, x + 13, y);		//����
    LCD_DrawLine(x, y - 12, x, y + 13);		//����
    LCD_DrawPoint(x + 1, y + 1);
    LCD_DrawPoint(x - 1, y + 1);
    LCD_DrawPoint(x + 1, y - 1);
    LCD_DrawPoint(x - 1, y - 1);
    gui_circle(x, y, POINT_COLOR, 6, 0);		//������Ȧ
}

/*****************************************************************************
 * @name       :void TP_Draw_Big_Point(uint16_t x,uint16_t y,uint16_t color)
 * @date       :2018-08-09 
 * @function   :Draw a big point(2*2)					
 * @parameters :x:Read x coordinate of the point
 y:Read y coordinate of the point
 color:the color value of the point
 * @retvalue   :None
 ******************************************************************************/
void TP_Draw_Big_Point(uint16_t x, uint16_t y, uint16_t color)
{
    POINT_COLOR = color;
    LCD_DrawPoint(x, y);		//���ĵ�
    LCD_DrawPoint(x + 1, y);
    LCD_DrawPoint(x, y + 1);
    LCD_DrawPoint(x + 1, y + 1);
}

/*****************************************************************************
 * @name       :uint8_t TP_Scan(uint8_t tp)
 * @date       :2018-08-09 
 * @function   :Scanning touch event				
 * @parameters :tp:0-screen coordinate 
 1-Physical coordinates(For special occasions such as calibration)
 * @retvalue   :Current touch screen status,
 0-no touch
 1-touch
 ******************************************************************************/
uint8_t TP_Scan(uint8_t tp)
{
    if (PEN == 0)		//�а�������
    {
        if (tp)
            TP_Read_XY2(&tp_dev.x, &tp_dev.y);		//��ȡ��������
        else if (TP_Read_XY2(&tp_dev.x, &tp_dev.y))		//��ȡ��Ļ����
        {
            tp_dev.x = tp_dev.xfac * tp_dev.x + tp_dev.xoff;		//�����ת��Ϊ��Ļ����
            tp_dev.y = tp_dev.yfac * tp_dev.y + tp_dev.yoff;
        }
        if ((tp_dev.sta & TP_PRES_DOWN) == 0)		//֮ǰû�б�����
        {
            tp_dev.sta = TP_PRES_DOWN | TP_CATH_PRES;		//��������
            tp_dev.x0 = tp_dev.x;		//��¼��һ�ΰ���ʱ������
            tp_dev.y0 = tp_dev.y;
        }
    }
    else
    {
        if (tp_dev.sta & TP_PRES_DOWN)		//֮ǰ�Ǳ����µ�
        {
            tp_dev.sta &= ~(1 << 7);		//��ǰ����ɿ�
        }
        else		//֮ǰ��û�б�����
        {
            tp_dev.x0 = 0;
            tp_dev.y0 = 0;
            tp_dev.x = 0xffff;
            tp_dev.y = 0xffff;
        }
    }
    return tp_dev.sta & TP_PRES_DOWN;		//���ص�ǰ�Ĵ���״̬
}

//////////////////////////////////////////////////////////////////////////	 
//������EEPROM����ĵ�ַ�����ַ,ռ��13���ֽ�(RANGE:SAVE_ADDR_BASE~SAVE_ADDR_BASE+12)
#define SAVE_ADDR_BASE 40
/*****************************************************************************
 * @name       :void TP_Save_Adjdata(void)
 * @date       :2018-08-09 
 * @function   :Save calibration parameters		
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void TP_Save_Adjdata(void)
{
    int32_t temp;
    //����У�����!
    temp = tp_dev.xfac * 100000000;		//����xУ������
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE, temp, 4);
    temp = tp_dev.yfac * 100000000;		//����yУ������
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE + 4, temp, 4);
    //����xƫ����
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE + 8, tp_dev.xoff, 2);
    //����yƫ����
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE + 10, tp_dev.yoff, 2);
    //���津������
    AT24CXX_WriteOneByte(SAVE_ADDR_BASE + 12, tp_dev.touchtype);
    temp = 0X0A;		//���У׼����
    AT24CXX_WriteOneByte(SAVE_ADDR_BASE + 13, temp);
}

/*****************************************************************************
 * @name       :uint8_t TP_Get_Adjdata(void)
 * @date       :2018-08-09 
 * @function   :Gets the calibration values stored in the EEPROM		
 * @parameters :None
 * @retvalue   :
 * 1-get the calibration values successfully//�ɹ���ȡУ׼ֵ
 * 0-get the calibration values unsuccessfully and Need to recalibrate//�޷����У׼ֵ����Ҫ����У׼
 ******************************************************************************/
//��ȡ�洢��EEPROM�е�У׼ֵ
uint8_t TP_Get_Adjdata(void)
{
    int32_t tempfac;		//��ʱʵ��ֵ
    tempfac = AT24CXX_ReadOneByte(SAVE_ADDR_BASE + 13);		//��ȡ�����,���Ƿ�У׼����
    if (tempfac == 0X0A)		//�������Ѿ�У׼����
    {
        P1OUT |= BIT0;		//������ӵĺ������ҵİ��ϵ�AT24C02�Ƿ���������

        tempfac = AT24CXX_ReadLenByte(SAVE_ADDR_BASE, 4);
        tp_dev.xfac = (float) tempfac / 100000000;		//�õ�xУ׼����

        tempfac = AT24CXX_ReadLenByte(SAVE_ADDR_BASE + 4, 4);
        tp_dev.yfac = (float) tempfac / 100000000;		//�õ�yУ׼����

        //�õ�xƫ����
        tp_dev.xoff = AT24CXX_ReadLenByte(SAVE_ADDR_BASE + 8, 2);

        //�õ�yƫ����
        tp_dev.yoff = AT24CXX_ReadLenByte(SAVE_ADDR_BASE + 10, 2);

        //��ȡ�������ͱ��
        tp_dev.touchtype = AT24CXX_ReadOneByte(SAVE_ADDR_BASE + 12);
        if (tp_dev.touchtype)	    //X,Y��������Ļ�෴
        {
            CMD_RDX = 0X90;
            CMD_RDY = 0XD0;
        }
        else				   //X,Y��������Ļ��ͬ
        {
            CMD_RDX = 0XD0;
            CMD_RDY = 0X90;
        }
        return 1;
    }
    return 0;
}

//��ʾ�ַ���
const uint8_t *TP_REMIND_MSG_TBL = "Please use the stylus click the cross on the screen.The cross will always move until the screen adjustment is completed.";

/*****************************************************************************
 * @name       :void TP_Adj_Info_Show(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t fac)
 * @date       :2018-08-09 
 * @function   :Display calibration results	
 * @parameters :x0:the x coordinates of first calibration point
 y0:the y coordinates of first calibration point
 x1:the x coordinates of second calibration point
 y1:the y coordinates of second calibration point
 x2:the x coordinates of third calibration point
 y2:the y coordinates of third calibration point
 x3:the x coordinates of fourth calibration point
 y3:the y coordinates of fourth calibration point
 fac:calibration factor
 * @retvalue   :None
 ******************************************************************************/
void TP_Adj_Info_Show(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t fac, uint8_t bold)
{
    POINT_COLOR = RED;
    LCD_ShowString(40, 160, BLACK, WHITE, 16, "x1:", 1, bold);
    LCD_ShowString(40 + 80, 160, BLACK, WHITE, 16, "y1:", 1, bold);
    LCD_ShowString(40, 180, BLACK, WHITE, 16, "x2:", 1, bold);
    LCD_ShowString(40 + 80, 180, BLACK, WHITE, 16, "y2:", 1, bold);
    LCD_ShowString(40, 200, BLACK, WHITE, 16, "x3:", 1, bold);
    LCD_ShowString(40 + 80, 200, BLACK, WHITE, 16, "y3:", 1, bold);
    LCD_ShowString(40, 220, BLACK, WHITE, 16, "x4:", 1, bold);
    LCD_ShowString(40 + 80, 220, BLACK, WHITE, 16, "y4:", 1, bold);
    LCD_ShowString(40, 240, BLACK, WHITE, 16, "fac is:", 1, bold);
    LCD_ShowNum(40 + 24, 160, BLACK, WHITE, x0, 4, 16, 1, bold);		//��ʾ��ֵ
    LCD_ShowNum(40 + 24 + 80, 160, BLACK, WHITE, y0, 4, 16, 1, bold);	//��ʾ��ֵ
    LCD_ShowNum(40 + 24, 180, BLACK, WHITE, x1, 4, 16, 1, bold);		//��ʾ��ֵ
    LCD_ShowNum(40 + 24 + 80, 180, BLACK, WHITE, y1, 4, 16, 1, bold);	//��ʾ��ֵ
    LCD_ShowNum(40 + 24, 200, BLACK, WHITE, x2, 4, 16, 1, bold);		//��ʾ��ֵ
    LCD_ShowNum(40 + 24 + 80, 200, BLACK, WHITE, y2, 4, 16, 1, bold);	//��ʾ��ֵ
    LCD_ShowNum(40 + 24, 220, BLACK, WHITE, x3, 4, 16, 1, bold);		//��ʾ��ֵ
    LCD_ShowNum(40 + 24 + 80, 220, BLACK, WHITE, y3, 4, 16, 1, bold);	//��ʾ��ֵ
    LCD_ShowNum(40 + 56, lcddev.width, BLACK, WHITE, fac, 3, 16, 1, bold); 	//��ʾ��ֵ,����ֵ������95~105��Χ֮��.
}

/*****************************************************************************
 * @name       :uint8_t TP_Get_Adjdata(void)
 * @date       :2018-08-09 
 * @function   :Calibration touch screen and Get 4 calibration parameters
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void TP_Adjust(void)
{
    uint16_t pos_temp[4][2]; 	//���껺��ֵ
    uint8_t cnt = 0;
    uint16_t d1, d2;
    uint32_t tem1, tem2;
    float fac;
    uint16_t outtime = 0;
    cnt = 0;
    POINT_COLOR = BLUE;
    BACK_COLOR = WHITE;
    LCD_Clear(WHITE); 	//����
    POINT_COLOR = RED; 	//��ɫ
    LCD_Clear(WHITE); 	//����
    POINT_COLOR = BLACK;
    LCD_ShowString(10, 40, BLACK, WHITE, 16, "Please use the stylus click the", 1, 0); 	//��ʾ��ʾ��Ϣ
    LCD_ShowString(10, 56, BLACK, WHITE, 16, "cross on the screen.The cross will", 1, 0); 	//��ʾ��ʾ��Ϣ
    LCD_ShowString(10, 72, BLACK, WHITE, 16, "always move until the screen ", 1, 0); 	//��ʾ��ʾ��Ϣ
    LCD_ShowString(10, 88, BLACK, WHITE, 16, "adjustment is completed.", 1, 0); 	//��ʾ��ʾ��Ϣ

    TP_Drow_Touch_Point(20, 20, RED); 	//����1
    tp_dev.sta = 0; 	//���������ź�
    tp_dev.xfac = 0; 	//xfac��������Ƿ�У׼��,����У׼֮ǰ�������!�������
    while (1) 	//�������10����û�а���,���Զ��˳�
    {
        tp_dev.scan(1); 	//ɨ����������
        if ((tp_dev.sta & 0xc0) == TP_CATH_PRES) 	//����������һ��(��ʱ�����ɿ���.)
        {
            outtime = 0;
            tp_dev.sta &= ~(1 << 6); 	//1����6λ����λ��ʾ�а��������ˣ���ǰ����Ѿ����������.
            pos_temp[cnt][0] = tp_dev.x;
            pos_temp[cnt][1] = tp_dev.y;
            cnt++;
            switch (cnt)
            {
            case 1:
                TP_Drow_Touch_Point(20, 20, WHITE);				//�����1
                TP_Drow_Touch_Point(lcddev.width - 20, 20, RED);	//����2
                break;
            case 2:
                TP_Drow_Touch_Point(lcddev.width - 20, 20, WHITE);	//�����2
                TP_Drow_Touch_Point(20, lcddev.height - 20, RED);	//����3
                break;
            case 3:
                TP_Drow_Touch_Point(20, lcddev.height - 20, WHITE);			//�����3
                TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, RED);	//����4
                break;
            case 4:	 //ȫ���ĸ����Ѿ��õ�
                //�Ա����
                tem1 = abs(pos_temp[0][0] - pos_temp[1][0]);	    		    //x1-x2
                tem2 = abs(pos_temp[0][1] - pos_temp[1][1]);	    		    //y1-y2
                tem1 *= tem1;
                tem2 *= tem2;
                d1 = sqrt(tem1 + tem2);	    		    //�õ�1,2�ľ���

                tem1 = abs(pos_temp[2][0] - pos_temp[3][0]);	    		    //x3-x4
                tem2 = abs(pos_temp[2][1] - pos_temp[3][1]);	    		    //y3-y4
                tem1 *= tem1;
                tem2 *= tem2;
                d2 = sqrt(tem1 + tem2);	    		    //�õ�3,4�ľ���
                fac = (float) d1 / d2;
                if (fac < 0.95 || fac > 1.05 || d1 == 0 || d2 == 0)	    		    //���ϸ�
                {
                    cnt = 0;
                    TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE);	//�����4
                    TP_Drow_Touch_Point(20, 20, RED);								//����1
                    TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100, 0);								//��ʾ����
                    continue;
                }
                tem1 = abs(pos_temp[0][0] - pos_temp[2][0]);								//x1-x3
                tem2 = abs(pos_temp[0][1] - pos_temp[2][1]);								//y1-y3
                tem1 *= tem1;
                tem2 *= tem2;
                d1 = sqrt(tem1 + tem2);								//�õ�1,3�ľ���

                tem1 = abs(pos_temp[1][0] - pos_temp[3][0]);								//x2-x4
                tem2 = abs(pos_temp[1][1] - pos_temp[3][1]);								//y2-y4
                tem1 *= tem1;
                tem2 *= tem2;
                d2 = sqrt(tem1 + tem2);								//�õ�2,4�ľ���
                fac = (float) d1 / d2;
                if (fac < 0.95 || fac > 1.05)								//���ϸ�
                {
                    cnt = 0;
                    TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE);	//�����4
                    TP_Drow_Touch_Point(20, 20, RED);								//����1
                    TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100, 0);								//��ʾ����
                    continue;
                }								//��ȷ��

                //�Խ������
                tem1 = abs(pos_temp[1][0] - pos_temp[2][0]);								//x1-x3
                tem2 = abs(pos_temp[1][1] - pos_temp[2][1]);								//y1-y3
                tem1 *= tem1;
                tem2 *= tem2;
                d1 = sqrt(tem1 + tem2);								//�õ�1,4�ľ���

                tem1 = abs(pos_temp[0][0] - pos_temp[3][0]);								//x2-x4
                tem2 = abs(pos_temp[0][1] - pos_temp[3][1]);								//y2-y4
                tem1 *= tem1;
                tem2 *= tem2;
                d2 = sqrt(tem1 + tem2);								//�õ�2,3�ľ���
                fac = (float) d1 / d2;
                if (fac < 0.95 || fac > 1.05)								//���ϸ�
                {
                    cnt = 0;
                    TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE);	//�����4
                    TP_Drow_Touch_Point(20, 20, RED);								//����1
                    TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100, 0);								//��ʾ����
                    continue;
                }								//��ȷ��
                                                //������
                tp_dev.xfac = (float) (lcddev.width - 40) / (pos_temp[1][0] - pos_temp[0][0]);					//�õ�xfac
                tp_dev.xoff = (lcddev.width - tp_dev.xfac * (pos_temp[1][0] + pos_temp[0][0])) / 2;					//�õ�xoff

                tp_dev.yfac = (float) (lcddev.height - 40) / (pos_temp[2][1] - pos_temp[0][1]);					//�õ�yfac
                tp_dev.yoff = (lcddev.height - tp_dev.yfac * (pos_temp[2][1] + pos_temp[0][1])) / 2;					//�õ�yoff
                if (abs(tp_dev.xfac) > 2 || abs(tp_dev.yfac) > 2)					//������Ԥ����෴��.
                {
                    cnt = 0;
                    TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE);	//�����4
                    TP_Drow_Touch_Point(20, 20, RED);								//����1
                    LCD_ShowString(40, 26, BLACK, WHITE, 16, "TP Need readjust!", 1, 0);
                    tp_dev.touchtype = !tp_dev.touchtype;								//�޸Ĵ�������.
                    if (tp_dev.touchtype)								//X,Y��������Ļ�෴
                    {
                        CMD_RDX = 0X90;
                        CMD_RDY = 0XD0;
                    }
                    else				   //X,Y��������Ļ��ͬ
                    {
                        CMD_RDX = 0XD0;
                        CMD_RDY = 0X90;
                    }
                    continue;
                }
                POINT_COLOR = BLUE;
                LCD_Clear(WHITE);				   //����
                LCD_ShowString(35, 110, BLACK, WHITE, 16, "Touch Screen Adjust OK!", 1, 0);				   //У�����
                delay_ms(1000);
                TP_Save_Adjdata();
                LCD_Clear(WHITE);				   //����
                return;				   //У�����
            }
        }
        delay_ms(10);
        outtime++;
        if (outtime > 1000)
        {
            TP_Get_Adjdata();
            break;
        }
    }
}

/*****************************************************************************
 * @name       :uint8_t TP_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization touch screen
 * @parameters :None
 * @retvalue   :0-no calibration
 1-Has been calibrated
 ******************************************************************************/
uint8_t TP_Init(void)
{
    TP_Read_XY(&tp_dev.x, &tp_dev.y);  //��һ�ζ�ȡ��ʼ��
    AT24CXX_Init();  //��ʼ��24CXX
    if (TP_Get_Adjdata())
        return 0;  //�Ѿ�У׼
    else			   //δУ׼?
    {
        LCD_Clear(WHITE);			   //����
        TP_Adjust();  //��ĻУ׼
        TP_Save_Adjdata();
    }
    TP_Get_Adjdata();
    return 1;
}

