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
    TIMER_A0->CCR[0] = 16383; //时钟源选择ACLK，中断时间=16383/32768=0.5s
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__ACLK | TIMER_A_CTL_MC__UP; // SMCLK, UP mode
    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);
}

void wdt_init()
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_SSEL__ACLK | WDT_A_CTL_TMSEL | WDT_A_CTL_CNTCL | WDT_A_CTL_IS_5; //解锁看门狗寄存器，时钟源选择32.768KHz，启用看门狗的定时模式，清除计数器的值，中断时间选择250 ms
    NVIC->ISER[0] = 1 << ((WDT_A_IRQn) & 31);  //启用看门狗终中断
}

void system_clk_init() //将运行频率锁定在48MHz,开启步骤原因详见：http://dev.ti.com/tirex/explore/node?node=AIt11.GE8nvJkpoVjCiItQ__z-lQYNj__LATEST
{
    /*    P4DIR |= BIT3; //将P4.3作为MCLK的输出引脚
     P4SEL0 |= BIT3;
     P4SEL1 &= ~BIT3;*/

    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY))
        ; //判断此时电源模式转换是否忙，忙的话执行空循环，直到电源模式转换完成
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY))
        ; //判断此时电源模式转换是否忙，忙的话执行空循环，直到电源模式转换完成

    //将存储体0和1的Flash等待状态都配置为1
    FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) | FLCTL_BANK0_RDCTL_WAIT_1;
    FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK1_RDCTL_WAIT_MASK)) | FLCTL_BANK1_RDCTL_WAIT_1;

    //步骤3：将DCO配置为48MHz，确保MCLK使用DCO作为源
    CS->KEY = CS_KEY_VAL;                  // 解锁CS模块以进行寄存器访问
    CS->CTL0 = 0;                           // 重置调整参数
    CS->CTL0 = CS_CTL0_DCORSEL_5;           // Set DCO to 48MHz
    /* Select MCLK =SMCLK= DCO=48MHz, no divider */
    CS->CTL1 = CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    CS->KEY = 0; // 锁定CS模块以防止意外访问
}

void system_init()
{
    system_clk_init();                            //系统时钟初始化
    delay_init(48);                            //滴答定时器延时初始化，因为系统是48MHz，所以填入48MHz
    timer_init();
    // wdt_init();
}
