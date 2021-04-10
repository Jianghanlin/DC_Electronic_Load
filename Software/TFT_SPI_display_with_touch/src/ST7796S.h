/*
 * ST7796S.h
 *
 *  Created on: 2020��11��22��
 *      Author: www14
 */

#ifndef SRC_ST7796S_H_
#define SRC_ST7796S_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>

//LCD��Ҫ������
typedef struct
{
    uint16_t width;          //LCD ���
    uint16_t height;         //LCD �߶�
    uint16_t id;               //LCD ID
    uint8_t dir;              //���������������ƣ�0��������1��������
    uint16_t wramcmd;       //��ʼдgramָ��
    uint16_t setxcmd;       //����x����ָ��
    uint16_t setycmd;       //����y����ָ��
} _lcd_dev;

//LCD����
extern _lcd_dev lcddev; //����LCD��Ҫ����

/////////////////////////////////////�û�������///////////////////////////////////
#define USE_HORIZONTAL       1//����Һ����˳ʱ����ת����    0-0����ת��1-90����ת��2-180����ת��3-270����ת

//////////////////////////////////////////////////////////////////////////////////
//����LCD�ĳߴ�
#define LCD_W 320
#define LCD_H 480

//TFTLCD������Ҫ���õĺ���
extern uint16_t POINT_COLOR; //Ĭ�Ϻ�ɫ
extern uint16_t BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//Һ�����ƿ���1�������궨��

//GPIO��λ�����ߣ�
#define LCD_CS_SET  P6OUT |=BIT1    //Ƭѡ�˿�     PB11
#define LCD_CS_CLR  P6OUT &=~BIT1     //Ƭѡ�˿�     PB11
#define LCD_RS_SET  P4OUT |=BIT4    //����/����  PB10
#define LCD_RS_CLR  P4OUT &=~BIT4     //����/����  PB10
#define LCD_RST_SET P4OUT |=BIT0  //��λ             PB12
#define LCD_RST_CLR P4OUT &=~BIT0    //��λ             PB12
#define LCD_ON  P5OUT |=BIT5
#define LCD_OFF P5OUT &=~BIT5
//GPIO��λ�����ͣ�

//������ɫ
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
#define BROWN           0XBC40 //��ɫ
#define BRRED           0XFC07 //�غ�ɫ
#define GRAY            0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE         0X01CF //����ɫ
#define LIGHTBLUE        0X7D7C //ǳ��ɫ
#define GRAYBLUE         0X5458 //����ɫ
//������ɫΪPANEL����ɫ

#define LIGHTGREEN      0X841F //ǳ��ɫ
#define LIGHTGRAY     0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY                   0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE       0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE          0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

extern void LCD_Init(void); //LCD��ʼ������
extern void LCD_DisplayOn(void); //LCD��ʾ����
extern void LCD_DisplayOff(void); //LCD�رպ���
extern void LCD_Clear(uint16_t Color); //LCD��������,�����������ɫ��
extern void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
extern void LCD_DrawPoint(uint16_t x, uint16_t y); //����
extern uint16_t LCD_ReadPoint(uint16_t x, uint16_t y); //����
extern void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
extern void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
extern void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd);

extern uint16_t LCD_RD_DATA(void); //��ȡLCD����
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

extern void GUI_DrawPoint(uint16_t x, uint16_t y, uint16_t color); //���㺯�����������Ϊ(X�����꣬Y�����꣬ǰ��ɫ);
extern void LCD_Fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);
extern void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
extern void LCD_DrawboldLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t bold); //���ƴ��ߺ����������������2021.1.6
extern void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
extern void Draw_Circle(uint16_t x0, uint16_t y0, uint16_t fc, uint8_t r);
extern void Draw_Triangel(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
extern void Fill_Triangel(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
extern void LCD_ShowChar(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode, uint8_t bold);
extern void LCD_ShowChar_2412(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode, uint8_t bold); //24��Ӣ���ֿ⣬�����������2021.1.6
extern void LCD_ShowChar_3216(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t num, uint8_t size, uint8_t mode, uint8_t bold); //32��Ӣ���ֿ⣬�����������2021.1.6
extern void LCD_ShowNum(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint32_t num, uint8_t len, uint8_t size, uint8_t mode, uint8_t bold);
extern void LCD_Show2Num(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint8_t size, uint8_t mode);
extern void LCD_ShowString(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t size, uint8_t *p, uint8_t mode, uint8_t bold); //ֻ����ʾӢ���ַ�������

extern void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode);
extern void GUI_DrawFont24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode); //24�������ֿ⣬�����������2021.1.6
extern void GUI_DrawFont32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s, uint8_t mode); //32�������ֿ⣬�����������2021.1.6
extern void Show_Str(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str, uint8_t size, uint8_t mode, uint8_t bold); //����ʾӢ���ַ������ֺ������ַ��������������2021.1.6

extern void Gui_Drawbmp16(uint16_t x, uint16_t y, const unsigned char *p); //��ʾ40*40 QQͼƬ
extern void Gui_Drawbmp_JHL(uint16_t x, uint16_t y, const unsigned char *p); //��ʾ����ֵ�һ���գ������������2021.1.6
extern void Gui_Drawbmp_LL(uint16_t x, uint16_t y, const unsigned char *p); //��ʾ��¶��һ���գ������������2021.1.6

extern void gui_circle(int xc, int yc, uint16_t c, int r, int fill);
extern void Gui_StrCenter(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *str, uint8_t size, uint8_t mode, uint8_t bold);
extern void LCD_DrawFillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

#endif /* SRC_ST7796S_H_ */
