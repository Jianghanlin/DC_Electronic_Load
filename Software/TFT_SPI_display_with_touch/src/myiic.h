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
#ifndef __MYIIC_H
#define __MYIIC_H
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
//IO��������
#define SDA_IN()  P6DIR &=~BIT7
#define SDA_OUT() P6DIR |=BIT7

//IO��������	 
#define IIC_SCL_H    P6OUT |=BIT6
#define IIC_SCL_L    P6OUT &=~BIT6
#define IIC_SDA_H    P6OUT |=BIT7
#define IIC_SDA_L    P6OUT &=~BIT7
#define READ_SDA   P6IN&BIT7  //����SDA

//IIC���в�������
extern void IIC_Init(void);                //��ʼ��IIC��IO��
extern void IIC_Start(void);				//����IIC��ʼ�ź�
extern void IIC_Stop(void);	  			//����IICֹͣ�ź�
extern void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
extern uint8_t IIC_Read_Byte(unsigned char ack);			//IIC��ȡһ���ֽ�
extern uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
extern void IIC_Ack(void);					//IIC����ACK�ź�
extern void IIC_NAck(void);				//IIC������ACK�ź�
extern void IIC_Write_One_Byte(uint8_t daddr, uint8_t addr, uint8_t data);
extern uint8_t IIC_Read_One_Byte(uint8_t daddr, uint8_t addr);
#endif

