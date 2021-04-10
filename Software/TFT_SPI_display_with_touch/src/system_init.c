/*
 * @Author: jianghanlin 
 * @Date: 2021-01-02 19:19:08 
 * @Last Modified by: jianghanlin
 * @Last Modified time: 2021-01-02 19:21:05
 */

#include "ti/devices/msp432p4xx/inc/msp.h"
#include "delay.h"

void timer_init()
{
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    //TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
    TIMER_A0->CCR[0] = 16383; //ʱ��Դѡ��ACLK���ж�ʱ��=16383/32768=0.5s
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__ACLK | TIMER_A_CTL_MC__UP; // SMCLK, UP mode
    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);
}

void wdt_init()
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_SSEL__ACLK | WDT_A_CTL_TMSEL | WDT_A_CTL_CNTCL | WDT_A_CTL_IS_5; //�������Ź��Ĵ�����ʱ��Դѡ��32.768KHz�����ÿ��Ź��Ķ�ʱģʽ�������������ֵ���ж�ʱ��ѡ��250 ms
    NVIC->ISER[0] = 1 << ((WDT_A_IRQn) & 31);  //���ÿ��Ź����ж�
}

void system_clk_init() //������Ƶ��������48MHz,��������ԭ�������http://dev.ti.com/tirex/explore/node?node=AIt11.GE8nvJkpoVjCiItQ__z-lQYNj__LATEST
{
    /*    P4DIR |= BIT3; //��P4.3��ΪMCLK���������
     P4SEL0 |= BIT3;
     P4SEL1 &= ~BIT3;*/

    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY))
        ; //�жϴ�ʱ��Դģʽת���Ƿ�æ��æ�Ļ�ִ�п�ѭ����ֱ����Դģʽת�����
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY))
        ; //�жϴ�ʱ��Դģʽת���Ƿ�æ��æ�Ļ�ִ�п�ѭ����ֱ����Դģʽת�����

    //���洢��0��1��Flash�ȴ�״̬������Ϊ1
    FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) | FLCTL_BANK0_RDCTL_WAIT_1;
    FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK1_RDCTL_WAIT_MASK)) | FLCTL_BANK1_RDCTL_WAIT_1;

    //����3����DCO����Ϊ48MHz��ȷ��MCLKʹ��DCO��ΪԴ
    CS->KEY = CS_KEY_VAL;                  // ����CSģ���Խ��мĴ�������
    CS->CTL0 = 0;                           // ���õ�������
    CS->CTL0 = CS_CTL0_DCORSEL_5;           // Set DCO to 48MHz
    /* Select MCLK =SMCLK= DCO=48MHz, no divider */
    CS->CTL1 = CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    CS->KEY = 0; // ����CSģ���Է�ֹ�������
}

void system_init()
{
    system_clk_init();                            //ϵͳʱ�ӳ�ʼ��
    delay_init(48);                            //�δ�ʱ����ʱ��ʼ������Ϊϵͳ��48MHz����������48MHz
    timer_init();
    // wdt_init();
}
