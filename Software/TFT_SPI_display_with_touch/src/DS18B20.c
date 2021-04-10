#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include "delay.h"
#include "ST7796S.h"
#include "DS18B20.h"
unsigned short mos_temp = 0;
/****************************************************************************
 * 名    称：unsigned char DS18B20_Init(void)
 * 功    能：对DS18B20进行初始化
 * 入口参数：
 * 出口参数：
 * 说    明:
 ****************************************************************************/
unsigned char DS18B20_Init(void)
{
    mos_temp = 0;
    unsigned char result;
    DQ_OUT;
    DQ_L;
    delay_us(500);   //总线拉低480us~960us，即主机发送复位脉冲
    DQ_IN;           //总线设为输入状态，等待18b20应答
    delay_us(60);    //DS18B20拉低60us~240us表示应答
    result = DQ_DATE;  //读取18b20应答信号
    delay_us(500);   //等待480us以上，保证总线释放
    return (result);  //返回0则初始化成功
}
/****************************************************************************
 * 名    称：unsigned char DS18B20_ReadBit(void)
 * 功    能：从DS18B20单总线上读1Bit数
 * 入口参数：
 * 出口参数：
 * 说    明:
 ****************************************************************************/
unsigned char DS18B20_ReadBit(void)
{
    unsigned char result;
    DQ_OUT;     		//设置总线为输出状态
    DQ_L;       		//总线拉低，产生读起始信号
    delay_us(2);		//保证低电平在1us以上
    DQ_IN;              //15us内读取总线上数据
    delay_us(5);        //读取数据之前先要等待总线释放（非常重要）
    result = DQ_DATE;     //接收数据
    delay_us(60);       //延时40~45us，保证总线释放
    return (result);     //返回数据
}
/****************************************************************************
 * 名    称：void DS18B20_WriteBit(unsigned charData)
 * 功    能：给DS18B20单总线上写1Bit数
 * 入口参数：
 * 出口参数：
 * 说    明:
 ****************************************************************************/
void DS18B20_WriteBit(unsigned char Data)
{
    DQ_OUT;       		//设置总线为输出
    DQ_L;        		//产生写起始信号
    delay_us(15);       //10~15us后写入数据
    if (Data)
        DQ_H;
    else
        DQ_L;
    delay_us(45);       //持续拉低20~45us
    DQ_IN;              //空闲状态总线保持输入状态
    delay_us(60);       //延时60us~120us，保证总线释放
}
/****************************************************************************
 * 名    称：unsigned char DS18B20_ReadByte(void)
 * 功    能：从DS18B20单总线上读1Byte数
 * 入口参数：
 * 出口参数：
 * 说    明:
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
 * 名    称：void DS18B20_WriteByte(unsigned charData)
 * 功    能：给DS18B20单总线上写1Byte数
 * 入口参数：
 * 出口参数：
 * 说    明:
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
 * 名    称：void DS18B20_ReadTemp(void)
 * 功    能：从DS18B20上读取温度值
 * 入口参数：
 * 出口参数：
 * 说    明:
 ****************************************************************************/
short DS18B20_ReadTemp(void)
{
    unsigned char tempH, tempL, temp;
    short Temperature = 0;
    DS18B20_Init();
    DS18B20_WriteByte(SkipRom);
    DS18B20_WriteByte(ConvertTemperature);
    delay_ms(5);              //延时750~900ms左右

    DS18B20_Init();
    DS18B20_WriteByte(SkipRom);
    DS18B20_WriteByte(ReadScratchpad);
    tempL = DS18B20_ReadByte();   //读温度低字节
    tempH = DS18B20_ReadByte();   //读温度高字节

    if (tempH > 7)
    {
        tempH = ~tempH;
        tempL = ~tempL;
        temp = 0;   //温度为负
    }
    else
        temp = 1;   //温度为正

    Temperature = tempH; //获得高八位
    Temperature <<= 8;
    Temperature += tempL; //获得低八位

    Temperature = Temperature * 6.25; //转换为4位整型数据

    if (temp)
        return Temperature; //返回温度值
    else
        return -Temperature;
}

void display_temperature()
{
    char temp[5] = { };
    mos_temp = DS18B20_ReadTemp();
    sprintf(temp, "%.2f", mos_temp * 0.01); //转换为4位整型数据，实际还得乘0.01才行
    Show_Str(350, 20, GREEN, BLACK, (uint8_t*) temp, 24, 0, 1);    //显示DS18B20的温度值
}

