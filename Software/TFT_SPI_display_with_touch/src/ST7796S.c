/*
 * Author：江瀚林
 * Date：2020.11.23
 * Class：17电子信息工程1
 * Num：Xb17610107
 */
/****************************************************************************************************
 //=========================================电源接线================================================//
 //     LCD模块                MSP432P401R开发板
 //      VCC          接        DC5V/3.3V      //电源
 //      GND          接          GND          //电源地
 //=======================================液晶屏数据线接线==========================================//
 //本模块默认数据总线类型为SPI总线
 //     LCD模块                  MSP432P401R开发板
 //    SDI(MOSI)      接          P1.6         //液晶屏SPI总线数据写信号
 //    SDO(MISO)      接          无         //液晶屏SPI总线数据读信号，如果不需要读，可以不接线
 //=======================================液晶屏控制线接线==========================================//
 //     LCD模块                MSP432P401R开发板
 //       LED         接          P2.5          //液晶屏背光控制信号，如果不需要控制，接5V或3.3V
 //       SCK         接          P1.5          //液晶屏SPI总线时钟信号
 //      DC/RS        接          P5.4         //液晶屏数据/命令控制信号
 //       RST         接          P5.2         //液晶屏复位控制信号
 //       CS          接          P5.1         //液晶屏片选控制信号
 //=========================================触摸屏触接线=========================================//
 //如果模块不带触摸功能或者带有触摸功能，但是不需要触摸功能，则不需要进行触摸屏接线
 //     LCD模块                MSP432P401R开发板
 //      T_IRQ        接          PC10         //触摸屏触摸中断信号
 //      T_DO         接          PC2          //触摸屏SPI总线读信号
 //      T_DIN        接          PC3          //触摸屏SPI总线写信号
 //      T_CS         接          PC13         //触摸屏片选控制信号
 //      T_CLK        接          PC0          //触摸屏SPI总线时钟信号
 **************************************************************************************************/
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/devices/msp432p4xx/driverlib/eusci.h>
#include "ST7796S.h"
#include "delay.h"
#include "string.h"
#include "font.h"
#include "USCI_B0_SPI.h"

#define SPI_WRITE_BYTE(__DATA)  usci_b0_spi_transmit_frame(&__DATA, 1)

//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

//画笔颜色,背景颜色
uint16_t POINT_COLOR = 0x0000, BACK_COLOR = 0xFFFF;
uint16_t DeviceCode;

/*void LCD_DisplayOn(void)
 {
 P2OUT |= BIT5;
 }
 void LCD_DisplayOff(void)
 {
 P2OUT &= ~ BIT5;
 }*/
/*****************************************************************************
 * @name       :void LCD_WR_REG(uint8_t data)
 * @date       :2018-08-09
 * @function   :Write an 8-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
 ******************************************************************************/
void LCD_WR_REG(uint8_t data)
{
    LCD_CS_CLR;
    LCD_RS_CLR;
    SPI_WRITE_BYTE(data);
    LCD_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA(uint8_t data)
 * @date       :2018-08-09
 * @function   :Write an 8-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
 ******************************************************************************/
void LCD_WR_DATA(uint8_t data)
{
    LCD_CS_CLR;
    LCD_RS_SET;
    SPI_WRITE_BYTE(data);
    LCD_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
 * @date       :2018-08-09
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
 LCD_RegValue:Data to be written
 * @retvalue   :None
 ******************************************************************************/
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
    LCD_WR_REG(LCD_Reg);
    LCD_WR_DATA(LCD_RegValue);
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
    LCD_WR_REG(lcddev.wramcmd);
}

/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(uint16_t Data)
 * @date       :2018-08-09
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
 ******************************************************************************/
void Lcd_WriteData_16Bit(uint16_t data)
{
    uint8_t low = 0;
    uint8_t high = 0;
    LCD_CS_CLR;
    LCD_RS_SET;
    high = data >> 8;
    low = data;
    SPI_WRITE_BYTE(high);
    SPI_WRITE_BYTE(low);
    LCD_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(uint16_t x,uint16_t y)
 * @date       :2018-08-09
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
 y:the y coordinate of the pixel
 * @retvalue   :None
 ******************************************************************************/
void LCD_DrawPoint(uint16_t x, uint16_t y)
{
    LCD_SetCursor(x, y); //设置光标位置
    Lcd_WriteData_16Bit(POINT_COLOR);
}

/*****************************************************************************
 * @name       :void LCD_Clear(uint16_t Color)
 * @date       :2018-08-09
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
 ******************************************************************************/
void LCD_Clear(uint16_t Color)
{
    unsigned int i, m;
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
    LCD_CS_CLR;
    LCD_RS_SET;
    for (i = 0; i < lcddev.height; i++)
    {
        for (m = 0; m < lcddev.width; m++)
        {
            Lcd_WriteData_16Bit(Color);
        }
    }
    LCD_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_GPIOInit(void)
 * @date       :2018-08-09
 * @function   :Initialization LCD screen GPIO
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void LCD_GPIOInit(void)
{
    P4DIR |= BIT0 + BIT1 + BIT3 + BIT4 + BIT6;
    P6DIR |= BIT1;
    P5DIR |= BIT5;
    //触摸引脚初始化

    P3DIR &= ~BIT3;
    P6DIR &= ~BIT0;
}

/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void LCD_RESET(void)
{
    LCD_RST_CLR;
    delay_ms(100);
    LCD_RST_SET;
    delay_ms(50);
}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
 ******************************************************************************/
void LCD_Init(void)
{
    LCD_GPIOInit();   //LCD GPIO初始化
    LCD_ON;
    LCD_RESET(); //LCD 复位
//************* ST7796S初始化**********//
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0xC3);
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0x96);
    LCD_WR_REG(0x36);
    LCD_WR_DATA(0x68);
    LCD_WR_REG(0x3A);
    LCD_WR_DATA(0x05);
    LCD_WR_REG(0xB0);
    LCD_WR_DATA(0x80);
    LCD_WR_REG(0xB6);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x02);
    LCD_WR_REG(0xB5);
    LCD_WR_DATA(0x02);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x04);
    LCD_WR_REG(0xB1);
    LCD_WR_DATA(0x80);
    LCD_WR_DATA(0x10);
    LCD_WR_REG(0xB4);
    LCD_WR_DATA(0x00);
    LCD_WR_REG(0xB7);
    LCD_WR_DATA(0xC6);
    LCD_WR_REG(0xC5);
    LCD_WR_DATA(0x24);
    LCD_WR_REG(0xE4);
    LCD_WR_DATA(0x31);
    LCD_WR_REG(0xE8);
    LCD_WR_DATA(0x40);
    LCD_WR_DATA(0x8A);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x29);
    LCD_WR_DATA(0x19);
    LCD_WR_DATA(0xA5);
    LCD_WR_DATA(0x33);
    LCD_WR_REG(0xC2);
    LCD_WR_REG(0xA7);

    LCD_WR_REG(0xE0);
    LCD_WR_DATA(0xF0);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x13);
    LCD_WR_DATA(0x12);
    LCD_WR_DATA(0x12);
    LCD_WR_DATA(0x2B);
    LCD_WR_DATA(0x3C);
    LCD_WR_DATA(0x44);
    LCD_WR_DATA(0x4B);
    LCD_WR_DATA(0x1B);
    LCD_WR_DATA(0x18);
    LCD_WR_DATA(0x17);
    LCD_WR_DATA(0x1D);
    LCD_WR_DATA(0x21);

    LCD_WR_REG(0XE1);
    LCD_WR_DATA(0xF0);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x13);
    LCD_WR_DATA(0x0C);
    LCD_WR_DATA(0x0D);
    LCD_WR_DATA(0x27);
    LCD_WR_DATA(0x3B);
    LCD_WR_DATA(0x44);
    LCD_WR_DATA(0x4D);
    LCD_WR_DATA(0x0B);
    LCD_WR_DATA(0x17);
    LCD_WR_DATA(0x17);
    LCD_WR_DATA(0x1D);
    LCD_WR_DATA(0x21);

    LCD_WR_REG(0X36);
    LCD_WR_DATA(0xEC);
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0xC3);
    LCD_WR_REG(0xF0);
    LCD_WR_DATA(0x69);
    LCD_WR_REG(0X13);
    LCD_WR_REG(0X11);
    LCD_WR_REG(0X29);

    LCD_direction(USE_HORIZONTAL); //设置LCD显示方向
    LCD_Clear(WHITE); //清全屏白色
}

/*****************************************************************************
 * @name       :void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
 * @date       :2018-08-09
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
 yStar:the bebinning y coordinate of the LCD display window
 xEnd:the endning x coordinate of the LCD display window
 yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
 ******************************************************************************/
void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd)
{
    LCD_WR_REG(lcddev.setxcmd);
    LCD_WR_DATA(xStar >> 8);
    LCD_WR_DATA(0x00FF & xStar);
    LCD_WR_DATA(xEnd >> 8);
    LCD_WR_DATA(0x00FF & xEnd);

    LCD_WR_REG(lcddev.setycmd);
    LCD_WR_DATA(yStar >> 8);
    LCD_WR_DATA(0x00FF & yStar);
    LCD_WR_DATA(yEnd >> 8);
    LCD_WR_DATA(0x00FF & yEnd);

    LCD_WriteRAM_Prepare(); //开始写入GRAM
}

/*****************************************************************************
 * @name       :void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
 * @date       :2018-08-09
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
 Ypos:the  y coordinate of the pixel
 * @retvalue   :None
 ******************************************************************************/
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    LCD_SetWindows(Xpos, Ypos, Xpos, Ypos);
}

/*****************************************************************************
 * @name       :void LCD_direction(uint8_t direction)
 * @date       :2018-08-09
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
 1-90 degree
 2-180 degree
 3-270 degree
 * @retvalue   :None
 ******************************************************************************/
void LCD_direction(uint8_t direction)
{
    lcddev.setxcmd = 0x2A;
    lcddev.setycmd = 0x2B;
    lcddev.wramcmd = 0x2C;
    switch (direction)
    {
    case 0:
        lcddev.width = LCD_W;
        lcddev.height = LCD_H;
        LCD_WriteReg(0x36, (1 << 3) | (1 << 6));
        break;
    case 1:
        lcddev.width = LCD_H;
        lcddev.height = LCD_W;
        LCD_WriteReg(0x36, (1 << 3) | (1 << 5));
        break;
    case 2:
        lcddev.width = LCD_W;
        lcddev.height = LCD_H;
        LCD_WriteReg(0x36, (1 << 3) | (1 << 7));
        break;
    case 3:
        lcddev.width = LCD_H;
        lcddev.height = LCD_W;
        LCD_WriteReg(0x36, (1 << 3) | (1 << 7) | (1 << 6) | (1 << 5));
        break;
    default:
        break;
    }
}

//具体元素绘制函数
/*******************************************************************
 * @name       :void GUI_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
 * @date       :2018-08-09
 * @function   :draw a point in LCD screen
 * @parameters :x:the x coordinate of the point
 y:the y coordinate of the point
 color:the color value of the point
 * @retvalue   :None
 ********************************************************************/
void GUI_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_SetCursor(x, y); //设置光标位置
    Lcd_WriteData_16Bit(color);
}

/*******************************************************************
 * @name       :void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
 * @date       :2018-08-09
 * @function   :fill the specified area
 * @parameters :sx:the bebinning x coordinate of the specified area
 sy:the bebinning y coordinate of the specified area
 ex:the ending x coordinate of the specified area
 ey:the ending y coordinate of the specified area
 color:the filled color value
 * @retvalue   :None
 ********************************************************************/
void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color)
{
    uint16_t i, j;
    uint16_t width = ex - sx + 1;      //得到填充的宽度
    uint16_t height = ey - sy + 1;     //高度
    LCD_SetWindows(sx, sy, ex, ey);     //设置显示窗口
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
            Lcd_WriteData_16Bit(color); //写入数据
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1); //恢复窗口设置为全屏
}

/*******************************************************************
 * @name       :void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
 * @date       :2018-08-09
 * @function   :Draw a line between two points
 * @parameters :x1:the bebinning x coordinate of the line
 y1:the bebinning y coordinate of the line
 x2:the ending x coordinate of the line
 y2:the ending y coordinate of the line
 * @retvalue   :None
 ********************************************************************/
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;

    delta_x = x2 - x1; //计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;
    if (delta_x > 0)
        incx = 1; //设置单步方向
    else if (delta_x == 0)
        incx = 0; //垂直线
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; //水平线
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x; //选取基本增量坐标轴
    else
        distance = delta_y;
    for (t = 0; t <= distance + 1; t++) //画线输出
    {
        LCD_DrawPoint(uRow, uCol); //画点
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

void LCD_DrawboldLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t bold)
{
    POINT_COLOR = WHITE;
    uint8_t i;
    for (i = 0; i < bold; i++)
    {
        LCD_DrawLine(x1, y1 + i, x2, y2 + i);
    }

}

/*****************************************************************************
 * @name       :void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
 * @date       :2018-08-09
 * @function   :Draw a rectangle
 * @parameters :x1:the bebinning x coordinate of the rectangle
 y1:the bebinning y coordinate of the rectangle
 x2:the ending x coordinate of the rectangle
 y2:the ending y coordinate of the rectangle
 * @retvalue   :None
 ******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    LCD_DrawLine(x1, y1, x2, y1);
    LCD_DrawLine(x1, y1, x1, y2);
    LCD_DrawLine(x1, y2, x2, y2);
    LCD_DrawLine(x2, y1, x2, y2);
}

/*****************************************************************************
 * @name       :void LCD_DrawFillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
 * @date       :2018-08-09
 * @function   :Filled a rectangle
 * @parameters :x1:the bebinning x coordinate of the filled rectangle
 y1:the bebinning y coordinate of the filled rectangle
 x2:the ending x coordinate of the filled rectangle
 y2:the ending y coordinate of the filled rectangle
 * @retvalue   :None
 ******************************************************************************/
void LCD_DrawFillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    LCD_Fill(x1, y1, x2, y2, POINT_COLOR);
}

/*****************************************************************************
 * @name       :void _draw_circle_8(int xc, int yc, int x, int y, uint16_t c)
 * @date       :2018-08-09
 * @function   :8 symmetry circle drawing algorithm (internal call)
 * @parameters :xc:the x coordinate of the Circular center
 yc:the y coordinate of the Circular center
 x:the x coordinate relative to the Circular center
 y:the y coordinate relative to the Circular center
 c:the color value of the circle
 * @retvalue   :None
 ******************************************************************************/
void _draw_circle_8(int xc, int yc, int x, int y, uint16_t c)
{
    GUI_DrawPoint(xc + x, yc + y, c);

    GUI_DrawPoint(xc - x, yc + y, c);

    GUI_DrawPoint(xc + x, yc - y, c);

    GUI_DrawPoint(xc - x, yc - y, c);

    GUI_DrawPoint(xc + y, yc + x, c);

    GUI_DrawPoint(xc - y, yc + x, c);

    GUI_DrawPoint(xc + y, yc - x, c);

    GUI_DrawPoint(xc - y, yc - x, c);
}

/*****************************************************************************
 * @name       :void gui_circle(int xc, int yc,uint16_t c,int r, int fill)
 * @date       :2018-08-09
 * @function   :Draw a circle of specified size at a specified location
 * @parameters :xc:the x coordinate of the Circular center
 yc:the y coordinate of the Circular center
 r:Circular radius
 fill:1-filling,0-no filling
 * @retvalue   :None
 ******************************************************************************/
void gui_circle(int xc, int yc, uint16_t c, int r, int fill)
{
    int x = 0, y = r, yi, d;

    d = 3 - 2 * r;

    if (fill)
    {
        // 如果填充（画实心圆）
        while (x <= y)
        {
            for (yi = x; yi <= y; yi++)
                _draw_circle_8(xc, yc, x, yi, c);

            if (d < 0)
            {
                d = d + 4 * x + 6;
            }
            else
            {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
    else
    {
        // 如果不填充（画空心圆）
        while (x <= y)
        {
            _draw_circle_8(xc, yc, x, y, c);
            if (d < 0)
            {
                d = d + 4 * x + 6;
            }
            else
            {
                d = d + 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
}

/*****************************************************************************
 * @name       :void Draw_Triangel(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
 * @date       :2018-08-09
 * @function   :Draw a triangle at a specified position
 * @parameters :x0:the bebinning x coordinate of the triangular edge
 y0:the bebinning y coordinate of the triangular edge
 x1:the vertex x coordinate of the triangular
 y1:the vertex y coordinate of the triangular
 x2:the ending x coordinate of the triangular edge
 y2:the ending y coordinate of the triangular edge
 * @retvalue   :None
 ******************************************************************************/
void Draw_Triangel(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    LCD_DrawLine(x0, y0, x1, y1);
    LCD_DrawLine(x1, y1, x2, y2);
    LCD_DrawLine(x2, y2, x0, y0);
}

static void _swap(uint16_t *a, uint16_t *b)
{
    uint16_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

/*****************************************************************************
 * @name       :void Fill_Triangel(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
 * @date       :2018-08-09
 * @function   :filling a triangle at a specified position
 * @parameters :x0:the bebinning x coordinate of the triangular edge
 y0:the bebinning y coordinate of the triangular edge
 x1:the vertex x coordinate of the triangular
 y1:the vertex y coordinate of the triangular
 x2:the ending x coordinate of the triangular edge
 y2:the ending y coordinate of the triangular edge
 * @retvalue   :None
 ******************************************************************************/
void Fill_Triangel(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t a, b, y, last;
    int dx01, dy01, dx02, dy02, dx12, dy12;
    long sa = 0;
    long sb = 0;
    if (y0 > y1)
    {
        _swap(&y0, &y1);
        _swap(&x0, &x1);
    }
    if (y1 > y2)
    {
        _swap(&y2, &y1);
        _swap(&x2, &x1);
    }
    if (y0 > y1)
    {
        _swap(&y0, &y1);
        _swap(&x0, &x1);
    }
    if (y0 == y2)
    {
        a = b = x0;
        if (x1 < a)
        {
            a = x1;
        }
        else if (x1 > b)
        {
            b = x1;
        }
        if (x2 < a)
        {
            a = x2;
        }
        else if (x2 > b)
        {
            b = x2;
        }
        LCD_Fill(a, y0, b, y0, color);
        return;
    }
    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;

    if (y1 == y2)
    {
        last = y1;
    }
    else
    {
        last = y1 - 1;
    }
    for (y = y0; y <= last; y++)
    {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        if (a > b)
        {
            _swap(&a, &b);
        }
        LCD_Fill(a, y, b, y, color);
    }
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++)
    {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        if (a > b)
        {
            _swap(&a, &b);
        }
        LCD_Fill(a, y, b, y, color);
    }
}

/*****************************************************************************
 * @name       :void LCD_ShowChar(uint16_t x,uint16_t y,uint16_t fc, uint16_t bc, uint8_t num,uint8_t size,uint8_t mode)
 * @date       :2018-08-09
 * @function   :Display a single English character
 * @parameters :x:the bebinning x coordinate of the Character display position
 y:the bebinning y coordinate of the Character display position
 fc:the color value of display character
 bc:the background color of display character
 num:the ascii code of display character(0~94)
 size:the size of display character
 mode:0-no overlying,1-overlying
 * @retvalue   :None
 ******************************************************************************/
void LCD_ShowChar_2412(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode, uint8_t bold)
{
    uint8_t temp;
    uint8_t pos, t;
    uint16_t colortemp = POINT_COLOR;

    num = num - ' '; //得到偏移后的值
    LCD_SetWindows(x, y, x + size / 2 - 1, y + size - 1); //设置单个文字显示窗口
    if (!mode) //非叠加方式
    {
        for (pos = 0; pos < 48; pos++)
        {
            //temp = asc2_2412[num][pos];       //调用2412字体
            if (bold == 0)
            {
                temp = heiti_2412[num][pos];
            }
            else
            {
                temp = heiti_bold_2412[num][pos];
            }

            if ((pos % 2) == 0)
            {
                y = y + 1;
                for (t = 0; t < 8; t++)
                {
                    if (temp & 0x01)
                        Lcd_WriteData_16Bit(fc);
                    else
                        Lcd_WriteData_16Bit(bc);
                    temp >>= 1;
                }
            }
            else
            {
                //temp >>= 4;
                for (t = 0; t < 4; t++)
                {
                    if (temp & 0x01)
                        Lcd_WriteData_16Bit(fc);
                    else
                        Lcd_WriteData_16Bit(bc);
                    temp >>= 1;
                }
            }
        }
    }
    else       //叠加方式
    {
        for (pos = 0; pos < 48; pos++)
        {
            if (bold == 0)
            {
                temp = heiti_2412[num][pos];
            }
            else
            {
                temp = heiti_bold_2412[num][pos];
            }
            if ((pos % 2) == 0)
            {
                y = y + 1;
                for (t = 0; t < 8; t++)
                {
                    POINT_COLOR = fc;
                    if (temp & 0x01)
                        LCD_DrawPoint(x + t, y);       //画一个点
                    temp >>= 1;
                }
            }
            else
            {
                for (t = 0; t < 4; t++)
                {
                    POINT_COLOR = fc;
                    if (temp & 0x01)
                        LCD_DrawPoint(x + t + 8, y);       //画一个点
                    temp >>= 1;
                }
            }
        }
    }
    POINT_COLOR = colortemp;
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);       //恢复窗口为全屏
}

void LCD_ShowChar_3216(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode, uint8_t bold)
{
    uint8_t temp;
    uint8_t pos, t;
    uint16_t colortemp = POINT_COLOR;

    num = num - ' '; //得到偏移后的值
    LCD_SetWindows(x, y, x + size / 2 - 1, y + size - 1); //设置单个文字显示窗口
    if (!mode) //非叠加方式
    {
        for (pos = 0; pos < 64; pos++)
        {
            if (bold == 0)
            {
                temp = heiti_3216[num][pos];
            }
            else
            {
                temp = heiti_bold_3216[num][pos];
            }
            if ((pos % 2) == 0)
            {
                y = y + 1;
                for (t = 0; t < 8; t++)
                {
                    if (temp & 0x01)
                        Lcd_WriteData_16Bit(fc);
                    else
                        Lcd_WriteData_16Bit(bc);
                    temp >>= 1;
                }
            }
            else
            {
                for (t = 0; t < 8; t++)
                {
                    if (temp & 0x01)
                        Lcd_WriteData_16Bit(fc);
                    else
                        Lcd_WriteData_16Bit(bc);
                    temp >>= 1;
                }
            }
        }
    }
    else       //叠加方式
    {
        for (pos = 0; pos < 64; pos++)
        {
            if (bold == 0)
            {
                temp = heiti_3216[num][pos];
            }
            else
            {
                temp = heiti_bold_3216[num][pos];
            }
            if ((pos % 2) == 0)
            {
                y = y + 1;
                for (t = 0; t < 8; t++)
                {
                    POINT_COLOR = fc;
                    if (temp & 0x01)
                        LCD_DrawPoint(x + t, y);       //画一个点
                    temp >>= 1;
                }
            }
            else
            {
                for (t = 0; t < 8; t++)
                {
                    POINT_COLOR = fc;
                    if (temp & 0x01)
                        LCD_DrawPoint(x + t + 8, y);       //画一个点
                    temp >>= 1;
                }
            }
        }
    }
    POINT_COLOR = colortemp;
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);       //恢复窗口为全屏
}

void LCD_ShowChar(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode, uint8_t bold)
{
    uint8_t temp;
    uint8_t pos, t;
    uint16_t colortemp = POINT_COLOR;
    num = num - ' '; //得到偏移后的值
    LCD_SetWindows(x, y, x + size / 2 - 1, y + size - 1); //设置单个文字显示窗口
    if (!mode) //非叠加方式
    {
        for (pos = 0; pos < size; pos++)
        {
            if (size == 12) //1206字体
                temp = songti_1206[num][pos]; //调用1206字体
            else
            {
                if (bold == 0)
                    //1608字体
                    temp = songti_1608[num][pos];       //调用1608字体
                else
                    //1608字体
                    temp = songti_bold_1608[num][pos];       //调用1608字体
            }
            for (t = 0; t < size / 2; t++)
            {
                if (temp & 0x01)
                    Lcd_WriteData_16Bit(fc);
                else
                    Lcd_WriteData_16Bit(bc);
                temp >>= 1;
            }

        }
    }
    else       //叠加方式
    {
        for (pos = 0; pos < size; pos++)
        {
            if (size == 12) //1206字体
                temp = songti_1206[num][pos]; //调用1206字体
            else
            {
                if (bold == 0)
                    //1608字体
                    temp = songti_1608[num][pos];       //调用1608字体
                else
                    //1608字体
                    temp = songti_bold_1608[num][pos];       //调用1608字体
            }
            for (t = 0; t < size / 2; t++)
            {
                POINT_COLOR = fc;
                if (temp & 0x01)
                    LCD_DrawPoint(x + t, y + pos);       //画一个点
                temp >>= 1;
            }
        }
    }
    POINT_COLOR = colortemp;
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);       //恢复窗口为全屏
}

/*****************************************************************************
 * @name       :void LCD_ShowString(uint16_t x,uint16_t y,uint8_t size,uint8_t *p,uint8_t mode)
 * @date       :2018-08-09
 * @function   :Display English string
 * @parameters :x:the bebinning x coordinate of the English string
 y:the bebinning y coordinate of the English string
 p:the start address of the English string
 size:the size of display character
 mode:0-no overlying,1-overlying
 * @retvalue   :None
 ******************************************************************************/
void LCD_ShowString(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t size, uint8_t *p, uint8_t mode, uint8_t bold)
//字符显示函数，传入参数（x,y,前景色,背景色,字号,字符串首地址,显示模式,是否加粗）
{
    while ((*p <= '~') && (*p >= ' '))       //判断是不是非法字符!
    {
        if (x > (lcddev.width - 1) || y > (lcddev.height - 1))
            return;
        LCD_ShowChar(x, y, fc, bc, *p, size, mode, bold);
        x += size / 2;
        p++;
    }
}

//江瀚林独立制作
void show_num_jhl(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t size, uint8_t *p, uint8_t mode, uint8_t bold)
{
    while ((*p <= '~') && (*p >= ' '))       //判断是不是非法字符!
    {
        if (x > (lcddev.width - 1) || y > (lcddev.height - 1))
            return;
        LCD_ShowChar(x, y, fc, bc, *p, size, mode, bold);
        x += size / 2;
        p++;
    }
}

/*****************************************************************************
 * @name       :uint32_t mypow(uint8_t m,uint8_t n)
 * @date       :2018-08-09
 * @function   :get the nth power of m (internal call)
 * @parameters :m:the multiplier
 n:the power
 * @retvalue   :the nth power of m
 ******************************************************************************/
uint32_t mypow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
        result *= m;
    return result;
}

/*****************************************************************************
 * @name       :void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size)
 * @date       :2018-08-09
 * @function   :Display number
 * @parameters :x:the bebinning x coordinate of the number
 y:the bebinning y coordinate of the number
 num:the number(0~4294967295)
 len:the length of the display number
 size:the size of display number
 * @retvalue   :None
 ******************************************************************************/
//整数显示函数0~4294967295，传入参数x,y,数字用一般的写法，长度，有几位写几位，字体的尺寸，字体的粗细
void LCD_ShowNum(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint8_t bold)
{
    uint8_t t, temp;
    uint8_t enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / mypow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                if (size > 16)
                {
                    LCD_ShowChar_2412(x + (size / 2) * t, y, fc, bc, ' ', size, mode, bold);
                }
                else
                    LCD_ShowChar(x + (size / 2) * t, y, fc, bc, ' ', size, mode, bold);
                continue;
            }
            else
                enshow = 1;

        }

        if (size > 16)
        {
            LCD_ShowChar_2412(x + (size / 2) * t, y, fc, bc, temp + '0', size, mode, bold);
        }
        else
        {
            LCD_ShowChar(x + (size / 2) * t, y, fc, bc, temp + '0', size, mode, bold);
        }
    }
}

/*****************************************************************************
 * @name       :void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
 * @date       :2018-08-09
 * @function   :Display a single 16x16 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
 y:the bebinning y coordinate of the Chinese character
 fc:the color value of Chinese character
 bc:the background color of Chinese character
 s:the start address of the Chinese character
 mode:0-no overlying,1-overlying
 * @retvalue   :None
 ******************************************************************************/
void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode)
{
    uint8_t i, j;
    uint16_t k;
    uint16_t HZnum;
    uint16_t x0 = x;
    HZnum = sizeof(tfont16) / sizeof(typFNT_GB16);  //自动统计汉字数目

    for (k = 0; k < HZnum; k++)
    {
        if ((tfont16[k].Index[0] == *(s)) && (tfont16[k].Index[1] == *(s + 1)))
        {
            LCD_SetWindows(x, y, x + 16 - 1, y + 16 - 1);
            for (i = 0; i < 16 * 2; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) //非叠加方式
                    {
                        if (tfont16[k].Msk[i] & (0x80 >> j))
                            Lcd_WriteData_16Bit(fc);
                        else
                            Lcd_WriteData_16Bit(bc);
                    }
                    else
                    {
                        POINT_COLOR = fc;
                        if (tfont16[k].Msk[i] & (0x80 >> j))
                            LCD_DrawPoint(x, y); //画一个点
                        x++;
                        if ((x - x0) == 16)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }

                }

            }

        }
        continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
    }

    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);  //恢复窗口为全屏
}

/*****************************************************************************
 * @name       :void GUI_DrawFont24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
 * @date       :2018-08-09
 * @function   :Display a single 24x24 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
 y:the bebinning y coordinate of the Chinese character
 fc:the color value of Chinese character
 bc:the background color of Chinese character
 s:the start address of the Chinese character
 mode:0-no overlying,1-overlying
 * @retvalue   :None
 ******************************************************************************/
void GUI_DrawFont24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode)
{
    uint8_t i, j;
    uint16_t k;
    uint16_t HZnum;
    uint16_t x0 = x;
    HZnum = sizeof(tfont24) / sizeof(typFNT_GB24);  //自动统计汉字数目

    for (k = 0; k < HZnum; k++)
    {
        if ((tfont24[k].Index[0] == *(s)) && (tfont24[k].Index[1] == *(s + 1)))
        {
            LCD_SetWindows(x, y, x + 24 - 1, y + 24 - 1);
            for (i = 0; i < 24 * 3; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) //非叠加方式
                    {
                        if (tfont24[k].Msk[i] & (0x80 >> j))
                            Lcd_WriteData_16Bit(fc);
                        else
                            Lcd_WriteData_16Bit(bc);
                    }
                    else
                    {
                        POINT_COLOR = fc;
                        if (tfont24[k].Msk[i] & (0x80 >> j))
                            LCD_DrawPoint(x, y); //画一个点
                        x++;
                        if ((x - x0) == 24)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }

        }
        continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
    }

    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);  //恢复窗口为全屏
}

/*****************************************************************************
 * @name       :void GUI_DrawFont32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
 * @date       :2018-08-09
 * @function   :Display a single 32x32 Chinese character
 * @parameters :x:the bebinning x coordinate of the Chinese character
 y:the bebinning y coordinate of the Chinese character
 fc:the color value of Chinese character
 bc:the background color of Chinese character
 s:the start address of the Chinese character
 mode:0-no overlying,1-overlying
 * @retvalue   :None
 ******************************************************************************/
void GUI_DrawFont32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode)
{
    uint8_t i, j;
    uint16_t k;
    uint16_t HZnum;
    uint16_t x0 = x;
    HZnum = sizeof(tfont32) / sizeof(typFNT_GB32);  //自动统计汉字数目
    for (k = 0; k < HZnum; k++)
    {
        if ((tfont32[k].Index[0] == *(s)) && (tfont32[k].Index[1] == *(s + 1)))
        {
            LCD_SetWindows(x, y, x + 32 - 1, y + 32 - 1);
            for (i = 0; i < 32 * 4; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (!mode) //非叠加方式
                    {
                        if (tfont32[k].Msk[i] & (0x80 >> j))
                            Lcd_WriteData_16Bit(fc);
                        else
                            Lcd_WriteData_16Bit(bc);
                    }
                    else
                    {
                        POINT_COLOR = fc;
                        if (tfont32[k].Msk[i] & (0x80 >> j))
                            LCD_DrawPoint(x, y); //画一个点
                        x++;
                        if ((x - x0) == 32)
                        {
                            x = x0;
                            y++;
                            break;
                        }
                    }
                }
            }

        }
        continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
    }

    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);  //恢复窗口为全屏
}

/*****************************************************************************
 * @name       :void Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode)
 * @date       :2018-08-09
 * @function   :Display Chinese and English strings
 * @parameters :x:the bebinning x coordinate of the Chinese and English strings
 y:the bebinning y coordinate of the Chinese and English strings
 fc:the color value of Chinese and English strings
 bc:the background color of Chinese and English strings
 str:the start address of the Chinese and English strings
 size:the size of Chinese and English strings
 mode:0-no overlying,1-overlying
 * @retvalue   :None
 ******************************************************************************/

void Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str, uint8_t size, uint8_t mode, uint8_t bold)
{
    uint16_t x0 = x;
    uint8_t bHz = 0;     //字符或者中文
    while (*str != 0)     //数据未结束
    {
        if (!bHz)
        {
            if (x > (lcddev.width - size / 2) || y > (lcddev.height - size))
                return;
            if (*str > 0x80)
                bHz = 1;     //中文
            else     //字符
            {
                if (*str == 0x0D)              //换行符号
                {
                    y += size;
                    x = x0;
                    str++;
                }
                else
                {
                    if (size == 32)
                    {
                        LCD_ShowChar_3216(x, y, fc, bc, *str, 32, mode, bold);
                        x += 16; //字符,为全字的一半
                    }
                    else if (size == 24)
                    {
                        LCD_ShowChar_2412(x, y, fc, bc, *str, 24, mode, bold);
                        //LCD_ShowChar(x, y, fc, bc, *str, 24, mode);
                        x += 12; //字符,为全字的一半
                    }
                    else if (size == 16)              //字库中没有集成12X24 16X32的英文字体,用8X16代替
                    {
                        LCD_ShowChar(x, y, fc, bc, *str, 16, mode, bold);
                        x += 8; //字符,为全字的一半
                    }
                    else
                    {
                        LCD_ShowChar(x, y, fc, bc, *str, size, mode, bold);
                        x += size / 2; //字符,为全字的一半
                    }
                }
                str++;
            }
        }
        else //中文
        {
            if (x > (lcddev.width - size) || y > (lcddev.height - size))
            //return;
            {
                x = 0;
                y = y + size;
            }
            bHz = 0; //有汉字库
            if (size == 32)
                GUI_DrawFont32(x, y, fc, bc, str, mode);
            else if (size == 24)
                GUI_DrawFont24(x, y, fc, bc, str, mode);
            else
                GUI_DrawFont16(x, y, fc, bc, str, mode);
            str += 2;
            x += size; //下一个汉字偏移
        }
    }
}

/*****************************************************************************
 * @name       :void Gui_StrCenter(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str,uint8_t size,uint8_t mode)
 * @date       :2018-08-09
 * @function   :Centered display of English and Chinese strings
 * @parameters :x:the bebinning x coordinate of the Chinese and English strings
 y:the bebinning y coordinate of the Chinese and English strings
 fc:the color value of Chinese and English strings
 bc:the background color of Chinese and English strings
 str:the start address of the Chinese and English strings
 size:the size of Chinese and English strings
 mode:0-no overlying,1-overlying
 * @retvalue   :None
 ******************************************************************************/
void Gui_StrCenter(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str, uint8_t size, uint8_t mode, uint8_t bold)
{
    uint16_t x1, len;
    len = strlen((const char*) str);
    switch (size)
    {
    case 16:
        x1 = (lcddev.width - len * 8) / 2;
        break;
    case 24:
        x1 = (lcddev.width - len * 12) / 2;
        break;
    case 32:
        x1 = (lcddev.width - len * 16) / 2;
        break;
    default:
        break;
    }
    Show_Str(x1, y, fc, bc, str, size, mode, bold);
}

/*****************************************************************************
 * @name       :void Gui_Drawbmp16(uint16_t x,uint16_t y,const unsigned char *p)
 * @date       :2018-08-09
 * @function   :Display a 16-bit BMP image
 * @parameters :x:the bebinning x coordinate of the BMP image
 y:the bebinning y coordinate of the BMP image
 p:the start address of image array
 * @retvalue   :None
 ******************************************************************************/
void Gui_Drawbmp16(uint16_t x, uint16_t y, const unsigned char *p) //显示40*40 QQ图片
{
    int i;
    unsigned char picH, picL;
    LCD_SetWindows(x, y, x + 40 - 1, y + 40 - 1); //窗口设置
    for (i = 0; i < 40 * 40; i++)
    {
        picL = *(p + i * 2);  //数据低位在前
        picH = *(p + i * 2 + 1);
        Lcd_WriteData_16Bit(picH << 8 | picL);
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);  //恢复显示窗口为全屏

}

void Gui_Drawbmp_JHL(uint16_t x, uint16_t y, const unsigned char *p) //显示40*40 QQ图片
{
    int i;
    unsigned char picH, picL;
    LCD_SetWindows(x, y, x + 86 - 1, y + 100 - 1); //窗口设置
    for (i = 0; i < 86 * 100; i++)
    {
        picL = *(p + i * 2);  //数据低位在前
        picH = *(p + i * 2 + 1);
        Lcd_WriteData_16Bit(picH << 8 | picL);
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);  //恢复显示窗口为全屏
}

void Gui_Drawbmp_LL(uint16_t x, uint16_t y, const unsigned char *p) //显示40*40 QQ图片
{
    int i;
    unsigned char picH, picL;
    LCD_SetWindows(x, y, x + 91 - 1, y + 100 - 1); //窗口设置
    for (i = 0; i < 91 * 100; i++)
    {
        picL = *(p + i * 2);  //数据低位在前
        picH = *(p + i * 2 + 1);
        Lcd_WriteData_16Bit(picH << 8 | picL);
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);  //恢复显示窗口为全屏
}

void Gui_Drawbmp(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, const unsigned char BMP[]) //显示40*40 QQ图片
{
//    int i;
//    unsigned char picH, picL;
//    LCD_SetWindows(x, y, x + facx - 1, y + facy - 1); //窗口设置
//    for (i = 0; i < facx * facy; i++)
//    {
//        picL = *(p + i * 2);  //数据低位在前
//        picH = *(p + i * 2 + 1);
//        Lcd_WriteData_16Bit(picH << 8 | picL);
//    }
//
//
    unsigned int j = 0;
    unsigned char x, y;
    LCD_SetWindows(x0, y0, x0 + x1 - 1, y0 + y1 - 1); //窗口设置
    if (y1 % 8 == 0)
        y = y1 / 8;
    else
        y = y1 / 8 + 1;
    for (y = y0; y < y1; y++)
    {
        //LCD_SetCursor(x0, y);
        for (x = x0; x < x1; x++)
        {
            Lcd_WriteData_16Bit(BMP[j++]);
        }
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);  //恢复显示窗口为全屏
}
