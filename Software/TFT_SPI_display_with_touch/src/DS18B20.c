#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include "delay.h"
#include "ST7796S.h"
#include "DS18B20.h"
unsigned short mos_temp = 0;
/****************************************************************************
 * ��    �ƣ�unsigned char DS18B20_Init(void)
 * ��    �ܣ���DS18B20���г�ʼ��
 * ��ڲ�����
 * ���ڲ�����
 * ˵    ��:
 ****************************************************************************/
unsigned char DS18B20_Init(void)
{
    mos_temp = 0;
    unsigned char result;
    DQ_OUT;
    DQ_L;
    delay_us(500);   //��������480us~960us�����������͸�λ����
    DQ_IN;           //������Ϊ����״̬���ȴ�18b20Ӧ��
    delay_us(60);    //DS18B20����60us~240us��ʾӦ��
    result = DQ_DATE;  //��ȡ18b20Ӧ���ź�
    delay_us(500);   //�ȴ�480us���ϣ���֤�����ͷ�
    return (result);  //����0���ʼ���ɹ�
}
/****************************************************************************
 * ��    �ƣ�unsigned char DS18B20_ReadBit(void)
 * ��    �ܣ���DS18B20�������϶�1Bit��
 * ��ڲ�����
 * ���ڲ�����
 * ˵    ��:
 ****************************************************************************/
unsigned char DS18B20_ReadBit(void)
{
    unsigned char result;
    DQ_OUT;     		//��������Ϊ���״̬
    DQ_L;       		//�������ͣ���������ʼ�ź�
    delay_us(2);		//��֤�͵�ƽ��1us����
    DQ_IN;              //15us�ڶ�ȡ����������
    delay_us(5);        //��ȡ����֮ǰ��Ҫ�ȴ������ͷţ��ǳ���Ҫ��
    result = DQ_DATE;     //��������
    delay_us(60);       //��ʱ40~45us����֤�����ͷ�
    return (result);     //��������
}
/****************************************************************************
 * ��    �ƣ�void DS18B20_WriteBit(unsigned charData)
 * ��    �ܣ���DS18B20��������д1Bit��
 * ��ڲ�����
 * ���ڲ�����
 * ˵    ��:
 ****************************************************************************/
void DS18B20_WriteBit(unsigned char Data)
{
    DQ_OUT;       		//��������Ϊ���
    DQ_L;        		//����д��ʼ�ź�
    delay_us(15);       //10~15us��д������
    if (Data)
        DQ_H;
    else
        DQ_L;
    delay_us(45);       //��������20~45us
    DQ_IN;              //����״̬���߱�������״̬
    delay_us(60);       //��ʱ60us~120us����֤�����ͷ�
}
/****************************************************************************
 * ��    �ƣ�unsigned char DS18B20_ReadByte(void)
 * ��    �ܣ���DS18B20�������϶�1Byte��
 * ��ڲ�����
 * ���ڲ�����
 * ˵    ��:
 ****************************************************************************/
unsigned char DS18B20_ReadByte(void)
{
    unsigned char i, result = 0;
    for (i = 0; i < 8; i++)
    {
        result >>= 1;
        if (DS18B20_ReadBit())
            result |= 0x80;
        else
            result &= 0x7f;
    }
    return (result);
}/****************************************************************************
 * ��    �ƣ�void DS18B20_WriteByte(unsigned charData)
 * ��    �ܣ���DS18B20��������д1Byte��
 * ��ڲ�����
 * ���ڲ�����
 * ˵    ��:
 ****************************************************************************/
void DS18B20_WriteByte(unsigned char Data)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        DS18B20_WriteBit(Data & 0x01);
        Data >>= 1;
    }
}
/****************************************************************************
 * ��    �ƣ�void DS18B20_ReadTemp(void)
 * ��    �ܣ���DS18B20�϶�ȡ�¶�ֵ
 * ��ڲ�����
 * ���ڲ�����
 * ˵    ��:
 ****************************************************************************/
short DS18B20_ReadTemp(void)
{
    unsigned char tempH, tempL, temp;
    short Temperature = 0;
    DS18B20_Init();
    DS18B20_WriteByte(SkipRom);
    DS18B20_WriteByte(ConvertTemperature);
    delay_ms(5);              //��ʱ750~900ms����

    DS18B20_Init();
    DS18B20_WriteByte(SkipRom);
    DS18B20_WriteByte(ReadScratchpad);
    tempL = DS18B20_ReadByte();   //���¶ȵ��ֽ�
    tempH = DS18B20_ReadByte();   //���¶ȸ��ֽ�

    if (tempH > 7)
    {
        tempH = ~tempH;
        tempL = ~tempL;
        temp = 0;   //�¶�Ϊ��
    }
    else
        temp = 1;   //�¶�Ϊ��

    Temperature = tempH; //��ø߰�λ
    Temperature <<= 8;
    Temperature += tempL; //��õͰ�λ

    Temperature = Temperature * 6.25; //ת��Ϊ4λ��������

    if (temp)
        return Temperature; //�����¶�ֵ
    else
        return -Temperature;
}

void display_temperature()
{
    char temp[5] = { };
    mos_temp = DS18B20_ReadTemp();
    sprintf(temp, "%.2f", mos_temp * 0.01); //ת��Ϊ4λ�������ݣ�ʵ�ʻ��ó�0.01����
    Show_Str(350, 20, GREEN, BLACK, (uint8_t*) temp, 24, 0, 1);    //��ʾDS18B20���¶�ֵ
}

