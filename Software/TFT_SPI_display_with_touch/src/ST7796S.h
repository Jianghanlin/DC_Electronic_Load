/*
 * ST7796S.h
 *
 *  Created on: 2020年11月22日
 *      Author: www14
 */

#ifndef SRC_ST7796S_H_
#define SRC_ST7796S_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>

//LCD重要参数集
typedef struct
{
    uint16_t width;          //LCD 宽度
    uint16_t height;         //LCD 高度
    uint16_t id;               //LCD ID
    uint8_t dir;              //横屏还是竖屏控制：0，竖屏；1，横屏。
    uint16_t wramcmd;       //开始写gram指令
    uint16_t setxcmd;       //设置x坐标指令
    uint16_t setycmd;       //设置y坐标指令
} _lcd_dev;

//LCD参数
extern _lcd_dev lcddev; //管理LCD重要参数

/////////////////////////////////////用户配置区///////////////////////////////////
#define USE_HORIZONTAL       1//定义液晶屏顺时针旋转方向    0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转

//////////////////////////////////////////////////////////////////////////////////
//定义LCD的尺寸
#define LCD_W 320
#define LCD_H 480

//TFTLCD部分外要调用的函数
extern uint16_t POINT_COLOR; //默认红色
extern uint16_t BACK_COLOR; //背景颜色.默认为白色

//液晶控制口置1操作语句宏定义

//GPIO置位（拉高）
#define LCD_CS_SET  P6OUT |=BIT1    //片选端口     PB11
#define LCD_CS_CLR  P6OUT &=~BIT1     //片选端口     PB11
#define LCD_RS_SET  P4OUT |=BIT4    //数据/命令  PB10
#define LCD_RS_CLR  P4OUT &=~BIT4     //数据/命令  PB10
#define LCD_RST_SET P4OUT |=BIT0  //复位             PB12
#define LCD_RST_CLR P4OUT &=~BIT0    //复位             PB12
#define LCD_ON  P5OUT |=BIT5
#define LCD_OFF P5OUT &=~BIT5
//GPIO复位（拉低）

//画笔颜色
#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define BRED        0XF81F
#define GRED                0XFFE0
#define GBLUE               0X07FF
#define BLUE1  0x3D7E
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN           0XBC40 //棕色
#define BRRED           0XFC07 //棕红色
#define GRAY            0X8430 //灰色
//GUI颜色

#define DARKBLUE         0X01CF //深蓝色
#define LIGHTBLUE        0X7D7C //浅蓝色
#define GRAYBLUE         0X5458 //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN      0X841F //浅绿色
#define LIGHTGRAY     0XEF5B //浅灰色(PANNEL)
#define LGRAY                   0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE       0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)

extern void LCD_Init(void); //LCD初始化函数
extern void LCD_DisplayOn(void); //LCD显示函数
extern void LCD_DisplayOff(void); //LCD关闭函数
extern void LCD_Clear(uint16_t Color); //LCD清屏函数,传入参数（颜色）
extern void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
extern void LCD_DrawPoint(uint16_t x, uint16_t y); //画点
extern uint16_t LCD_ReadPoint(uint16_t x, uint16_t y); //读点
extern void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
extern void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
extern void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd);

extern uint16_t LCD_RD_DATA(void); //读取LCD数据
extern void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
extern void LCD_WR_DATA(uint8_t data);
extern uint16_t LCD_ReadReg(uint8_t LCD_Reg);
extern void LCD_WriteRAM_Prepare(void);
extern void LCD_WriteRAM(uint16_t RGB_Code);
extern uint16_t LCD_ReadRAM(void);
extern uint16_t LCD_BGR2RGB(uint16_t c);
extern void LCD_SetParam(void);
extern void Lcd_WriteData_16Bit(uint16_t data);
extern void LCD_direction(uint8_t direction);
extern void spi_b0_init();

extern void GUI_DrawPoint(uint16_t x, uint16_t y, uint16_t color); //画点函数，传入参数为(X轴坐标，Y轴坐标，前景色);
extern void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);
extern void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
extern void LCD_DrawboldLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t bold); //绘制粗线函数，江瀚林制作于2021.1.6
extern void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
extern void Draw_Circle(uint16_t x0, uint16_t y0, uint16_t fc, uint8_t r);
extern void Draw_Triangel(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
extern void Fill_Triangel(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
extern void LCD_ShowChar(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode, uint8_t bold);
extern void LCD_ShowChar_2412(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode, uint8_t bold); //24号英文字库，江瀚林制作于2021.1.6
extern void LCD_ShowChar_3216(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode, uint8_t bold); //32号英文字库，江瀚林制作于2021.1.6
extern void LCD_ShowNum(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint8_t bold);
extern void LCD_Show2Num(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint8_t size, uint8_t mode);
extern void LCD_ShowString(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t size, uint8_t *p, uint8_t mode, uint8_t bold); //只能显示英文字符和数字

extern void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode);
extern void GUI_DrawFont24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode); //24号中文字库，江瀚林制作于2021.1.6
extern void GUI_DrawFont32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode); //32号中文字库，江瀚林制作于2021.1.6
extern void Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str, uint8_t size, uint8_t mode, uint8_t bold); //能显示英文字符、数字和中文字符，江瀚林制作于2021.1.6

extern void Gui_Drawbmp16(uint16_t x, uint16_t y, const unsigned char *p); //显示40*40 QQ图片
extern void Gui_Drawbmp_JHL(uint16_t x, uint16_t y, const unsigned char *p); //显示江瀚林的一寸照，江瀚林制作于2021.1.6
extern void Gui_Drawbmp_LL(uint16_t x, uint16_t y, const unsigned char *p); //显示刘露的一寸照，江瀚林制作于2021.1.6

extern void gui_circle(int xc, int yc, uint16_t c, int r, int fill);
extern void Gui_StrCenter(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str, uint8_t size, uint8_t mode, uint8_t bold);
extern void LCD_DrawFillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

#endif /* SRC_ST7796S_H_ */
