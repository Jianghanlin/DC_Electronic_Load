#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>
#include "dac8571.h"
#include "delay.h"
//#include <src/user/display_value.h>

uint32_t i, n;
uint8_t ack = 0;

void IIC_START(void)
{
    SCL_H;                   //SCL
    delay_us(200);
    SDA_H;
    delay_us(200);
    SDA_L;                    //SCL
    delay_us(200);
}

void IIC_OVER(void)
{
    SCL_L;
    SDA_H;
    delay_us(400);
}

void IIC_STOP(void)
{
    SCL_L;
    SDA_L;
    delay_us(400);
    SCL_H;
    delay_us(100);
    SDA_H;
    delay_us(400);
}

uint8_t IIC_TR(uint16_t dat)
{
    uint8_t ack = 0;
    SDA_DIROUT;
    for (i = 0; i < 8; i++)
    {
        n = 7 - i;
        SCL_L;
        delay_us(200);
        if (((dat & (1 << n)) >> n))
        {
            SDA_H;
        }
        else
            SDA_L;
        delay_us(200);
        SCL_H;
        delay_us(200);
    }
    SCL_L;
    SDA_DIRIN;
    delay_us(200);
    ack = SDA_IN;
    delay_us(200);
    SCL_H;
    delay_us(200);
    return ack;
}

uint8_t DAC_Init(void)
{
    uint8_t ack = 0;
    IIC_START();   //IIC
    ack = IIC_TR(0x98);
    if (ack != 0)
    {
        return ack;
    }
    IIC_OVER();
    IIC_TR(0x10);   //Write temporary register and load DAC with data
    if (ack != 0)
    {
        return ack;
    }
    IIC_OVER();
    return 0;
}

void DAC8571_OUT(float num)
{
    uint8_t ack = 0, error = 0;
    uint32_t dat = 0x98;
    uint32_t dat0, dat1;
    if ((num - VREF) > 0.0)
    {
        error = 1;
    }
    DAC_Init();
    dat = (uint32_t) ((num / VREF) * 65535);
    dat1 = ((dat & 0xff00) >> 8);
    ack = IIC_TR(dat1);//先发送高位
    if (ack != 0)
    {
        error = 1;
    }
    IIC_OVER();
    dat0 = (dat & 0x00ff);//再发送低位
    ack = IIC_TR(dat0);
    if (ack != 0)
    {
        error = 1;
    }
    IIC_STOP();
    /*
     while (error == 1)
     ;*/
}

void  (void)
{
    P3DIR |= BIT6 + BIT7; //P3.6--> SDA
                          //P3.7--> SCL
    DAC8571_OUT(0); //DA默认输出0
}
