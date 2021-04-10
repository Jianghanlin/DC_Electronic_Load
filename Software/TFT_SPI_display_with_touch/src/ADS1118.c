//////////////////////////////////////////////////////
//AIN����˿ڣ���-����                              //
//  0:AIN0-AIN1 1:AIN0-AIN3 2:AIN1-AIN3 3:AIN2-AIN3 //
//  4:AIN0-GND  5:AIN1-GND  6:AIN2-GND  7:AIN3-GND  //
//����                                                //
//  0:��6.144V 1:��4.096V 2:��2.048V 3:��1.024V     //
//  4:��0.512V 5:��0.256V 6:��0.256V 7:��0.256V     //
//////////////////////////////////////////////////////
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include <stdio.h>
#include "ADS1118.h"
#include "ST7796S.h"
void ADS1118_Init(void)
{
    P5DIR |= BIT0 + BIT1 + BIT2;          //�������Ƭ��д����
    P3DIR &= ~ BIT5;          //���룬��Ƭ��������
}

//****************************************************************
//* �������ƣ�WriteSPI
//* ������������ʼSPIд����
//* ��ڲ�����config
//* ���ز�����void
//****************************************************************
void WriteSPI(uint16_t config)
{
    uint16_t i = 0;
    CS_L;
    SCLK_L;
    //delay_us(200);
    for (i = 0; i < 16; i++)
    {
        SCLK_H;
        //delay_us(200);
        if (config & 0x8000)
        {
            DataIN_H;
        }
        else
        {
            DataIN_L;
        }
        config <<= 1;
        SCLK_L;
        //delay_us(200);
    }
    CS_H;
}

//****************************************************************
//* �������ƣ�ADS_ReadSPI��
//* ������������ʼSPI������
//* ��ڲ�����void
//* ���ز�����unsigned int
//****************************************************************
uint16_t ADS_Read()
{
    uint16_t i = 0;
    uint16_t adc;
    CS_L;
    adc = 0x0000;

    while (ADS1118_OUT)
        ;          //����һ��ת����ʼ�ж�
    DataIN_H;
    SCLK_L;
    for (i = 0; i < 16; i++)          //��ȡ���ݣ�����λ��ȡ����16λ����λ��ʼ
    {
        adc = adc << 1;
        SCLK_H;
        //delay_us(200);
        if (ADS1118_OUT)
        {
            adc |= 0x0001;
        }
        else
        {
            adc &= ~0x0001;
        }
        SCLK_L;

        //delay_us(200);
    }
    CS_H;
    return adc;
}

//****************************************************************
//* �������ƣ�ADS1118_Config
//* �������������üĴ���
//* ��ڲ�����add---ADS1118�ļĴ�������
//* ���ز�����void
//****************************************************************
void ADS1118_Config(uint8_t port, uint8_t scale)
{
    WriteSPI(0x81e3 + port * 4096 + scale * 512);    //C1E3  1100 0001 1110 0011
}
//****************************************************************
//* �������ƣ�ADS1118
//* ��������������һ��ADת��
//* ��ڲ�����port---AIN����˿�(0~7)  scale---������(0~7)
//* ���ز�����void
//****************************************************************
float ADS1118(uint8_t port, uint8_t scale)
{
    float value;
    ADS1118_Config(port, scale);
    value = ADS_Read();
    if (value > 0x7FFF)    //����Ǹ���ѹ
    {
        value -= 0x10000;
        return 0;    //Ĭ�ϲ���������ѹ������ֵ=0
    }
    else    //���������ѹ
    {
        switch (scale)
        {
        case 0:
            value *= 6.144;
            break;
        case 1:
            value *= 4.096;
            break;
        case 2:
            value *= 2.048;
            break;
        case 3:
            value *= 1.024;
            break;
        case 4:
            value *= 0.512;
            break;
        case 5:
            value *= 0.256;
            break;
        case 6:
            value *= 0.256;
            break;
        case 7:
            value *= 0.256;
            break;
        default:
            break;
        }
        value /= 32768.0;
        return value;
    }
}

float average_voltage_caculate(unsigned char channel, unsigned char times) //�������Ϊͨ���źͲ�������
{
    char i = 0;
    float sum = 0, AD = 0, max = 0, min = 10;
    for (i = times; i > 0; i--)
    {
        AD = ADS1118(channel, 1);
        if (max < AD)
        {
            max = AD;
        }
        if (min > AD)
        {
            min = AD;
        }
        sum = sum + AD;
    }
    sum = (sum - max - min) / (times - 2); //��2����Ϊmax��min
    return sum;
}

