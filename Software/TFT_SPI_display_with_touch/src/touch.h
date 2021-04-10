#ifndef __TOUCH_H__
#define __TOUCH_H__
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdint.h>

#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 	  

//�봥����оƬ��������
#define PEN  (P6IN & BIT0)
#define DOUT (P3IN & BIT3)
#define TDIN_H     P4OUT |=BIT1
#define TDIN_L     P4OUT &=~BIT1
#define TCS_H      P4OUT |=BIT3
#define TCS_L      P4OUT &=~BIT3
#define TCLK_H     P4OUT |=BIT6
#define TCLK_L     P4OUT &=~BIT6

//������������
typedef struct
{
    uint8_t (*init)(void);          //��ʼ��������������
    uint8_t (*scan)(uint8_t);               //ɨ�败����.0,��Ļɨ��;1,��������;
    void (*adjust)(void);       //������У׼
    uint16_t x0;                        //ԭʼ����(��һ�ΰ���ʱ������)
    uint16_t y0;
    uint16_t x;                         //��ǰ����(�˴�ɨ��ʱ,����������)
    uint16_t y;
    uint8_t sta;                    //�ʵ�״̬
    //b7:����1/�ɿ�0;
    //b6:0,û�а�������;1,�а�������.
////////////////////////������У׼����/////////////////////////
    float xfac;
    float yfac;
    short xoff;
    short yoff;
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//touchtype=0��ʱ��,�ʺ�����ΪX����,����ΪY�����TP.
//touchtype=1��ʱ��,�ʺ�����ΪY����,����ΪX�����TP.
    uint8_t touchtype;
} _m_tp_dev;

extern _m_tp_dev tp_dev;        //������������touch.c���涨��
extern void TP_Write_Byte(uint8_t num);						//�����оƬд��һ������
extern uint16_t TP_Read_AD(uint8_t CMD);							//��ȡADת��ֵ
extern uint16_t TP_Read_XOY(uint8_t xy);							//���˲��������ȡ(X/Y)
extern uint8_t TP_Read_XY(uint16_t *x, uint16_t *y);					//˫�����ȡ(X+Y)
extern uint8_t TP_Read_XY2(uint16_t *x, uint16_t *y);					//����ǿ�˲���˫���������ȡ
extern void TP_Drow_Touch_Point(uint16_t x, uint16_t y, uint16_t color);					//��һ������У׼��
extern void TP_Draw_Big_Point(uint16_t x, uint16_t y, uint16_t color);	//��һ�����
extern uint8_t TP_Scan(uint8_t tp);								//ɨ��
extern void TP_Save_Adjdata(void);						//����У׼����
extern uint8_t TP_Get_Adjdata(void);						//��ȡУ׼����
extern void TP_Adjust(void);							//������У׼
extern uint8_t TP_Init(void);								//��ʼ��
extern void TP_Adj_Info_Show(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t fac, uint8_t bold);								//��ʾУ׼��Ϣ

#endif

