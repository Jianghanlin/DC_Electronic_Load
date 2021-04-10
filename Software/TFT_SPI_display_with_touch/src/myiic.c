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
#include "myiic.h"
#include "delay.h"

/*****************************************************************************
 * @name       :void IIC_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialize IIC
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void IIC_Init(void) //Ƭ��AT24C02��ʼ������
{
    P6DIR |= BIT6 + BIT7; //P6.6��SCL��P6.7��SDA

    IIC_SCL_H;
    IIC_SDA_H;
}

/*****************************************************************************
 * @name       :void IIC_Start(void)
 * @date       :2018-08-09 
 * @function   :Generating IIC starting signal
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void IIC_Start(void)
{
    SDA_OUT();     //sda�����
    IIC_SDA_H;
    IIC_SCL_H;
    delay_us(4);
    IIC_SDA_L;     //START:when CLK is high,DATA change form high to low
    delay_us(4);
    IIC_SCL_L;     //ǯסI2C���ߣ�׼�����ͻ��������
}

/*****************************************************************************
 * @name       :void IIC_Stop(void)
 * @date       :2018-08-09 
 * @function   :Generating IIC stop signal
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void IIC_Stop(void)
{
    SDA_OUT();     //sda�����
    IIC_SCL_L;
    IIC_SDA_L;     //STOP:when CLK is high DATA change form low to high
    delay_us(4);
    IIC_SCL_H;
    IIC_SDA_H;     //����I2C���߽����ź�
    delay_us(4);
}

/*****************************************************************************
 * @name       :uint8_t IIC_Wait_Ack(void)
 * @date       :2018-08-09 
 * @function   :Wait for the response signal
 * @parameters :None
 * @retvalue   :0-receive response signal successfully
 1-receive response signal unsuccessfully
 ******************************************************************************/
uint8_t IIC_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    SDA_IN();      //SDA����Ϊ����
    IIC_SDA_H;
    delay_us(1);
    IIC_SCL_H;
    delay_us(1);
    while (READ_SDA)
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL_L;      //ʱ�����0
    return 0;
}

/*****************************************************************************
 * @name       :void IIC_Ack(void)
 * @date       :2018-08-09 
 * @function   :Generate ACK response signal
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void IIC_Ack(void)
{
    IIC_SCL_L;
    SDA_OUT();
    IIC_SDA_L;
    delay_us(2);
    IIC_SCL_H;
    delay_us(2);
    IIC_SCL_L;
}

/*****************************************************************************
 * @name       :void IIC_NAck(void)
 * @date       :2018-08-09 
 * @function   :Don't generate ACK response signal
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void IIC_NAck(void)
{
    IIC_SCL_L;
    SDA_OUT();
    IIC_SDA_H;
    delay_us(2);
    IIC_SCL_H;
    delay_us(2);
    IIC_SCL_L;
}

/*****************************************************************************
 * @name       :void IIC_Send_Byte(uint8_t txd)
 * @date       :2018-08-09 
 * @function   :send a byte data by IIC bus
 * @parameters :txd:Data to be sent
 * @retvalue   :None
 ******************************************************************************/
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    IIC_SCL_L;      //����ʱ�ӿ�ʼ���ݴ���
    for (t = 0; t < 8; t++)
    {
        if ((txd << t) & 0x80) //�����λ��ʼд
        {
            IIC_SDA_H;
        }
        else
        {
            IIC_SDA_L;
        }
        delay_us(2);   //��TEA5767��������ʱ���Ǳ����
        IIC_SCL_H;
        delay_us(2);
        IIC_SCL_L;
        delay_us(2);
    }
}

/*****************************************************************************
 * @name       :uint8_t IIC_Read_Byte(unsigned char ack)
 * @date       :2018-08-09 
 * @function   :read a byte data by IIC bus
 * @parameters :ack:0-send nACK
 1-send ACK
 * @retvalue   :Data to be read
 ******************************************************************************/
uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i, receive = 0;
    SDA_IN();   //SDA����Ϊ����
    for (i = 0; i < 8; i++)
    {
        IIC_SCL_L;
        delay_us(2);
        IIC_SCL_H;
        receive <<= 1;
        if (READ_SDA)
            receive++;
        delay_us(1);
    }
    if (!ack)
        IIC_NAck();   //����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}

