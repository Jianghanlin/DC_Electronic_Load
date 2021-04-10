/*
 * USCI_B0_SPI.c
 *
 *  Created on: 2020Äê11ÔÂ23ÈÕ
 *      Author: www14
 */

//* -----USCI_B0_SPI------
//* PORT     TYPE    PIN
//* MOSI     OUT     P1.6
//* MISO     IN      P1.7
//* SCK      OUT     P1.5
//* ----------------------
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
static unsigned char *spi_tx_buff;
static unsigned char *spi_rx_buff;

static unsigned char spi_tx_num = 0;
static unsigned char spi_rx_num = 0;

void usci_b0_spi_init()
{
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    NVIC->ISER[0] = 1 << ((EUSCIB0_IRQn) & 31); // Enable eUSCIA3 interrupt in NVIC module

    UCB0CTLW0 |= UCSWRST;                     // **Put state machine in reset**
    UCB0CTLW0 |= UCMST | UCSYNC | UCCKPL | UCMSB;   // 3-pin, 8-bit SPI master
                                                    // Clock polarity high, MSB
    UCB0CTLW0 |= UCSSEL__SMCLK;                // SMCLK
    UCB0BR0 = 4;                           // /2,fBitClock = fBRCLK/(UCBRx+1).
    UCB0BR1 = 0;                              //
    //UCA3MCTLW = 0;                            // No modulation
    UCB0CTLW0 &= ~UCSWRST;                    // **Initialize USCI state machine**
    UCB0IFG &= ~(UCTXIFG + UCRXIFG);
}

unsigned char usci_b0_spi_transmit_frame(uint8_t *p_buff, uint8_t num)
{
    if (UCB0STAT & UCBUSY)
        return 0;
    __disable_interrupt();
    UCB0IE |= UCTXIE;
    UCB0IE &= ~UCRXIE;
    __enable_interrupt();
    spi_tx_buff = p_buff;
    spi_tx_num = num;
    UCB0TXBUF = *spi_tx_buff++;
    while (UCB0STAT & UCBUSY)
        ;
    return 1;
}

unsigned char usci_b0_spi_receive_frame(unsigned char *p_buff, unsigned char num)
{
    if (UCB0STAT & UCBUSY)
        return 0;
    __disable_interrupt();
    UCB0IE &= ~UCTXIE;
    UCB0IE |= UCRXIE;
    __enable_interrupt();
    spi_rx_buff = p_buff;
    spi_rx_num = num;
    UCB0TXBUF = 0xff;
    while (UCB0STAT & UCBUSY)
        ;
    return 1;
}

inline void usci_b0_spi_rx_isr_handle(void)
{
    *spi_rx_buff++ = UCB0RXBUF;
    spi_rx_num--;
    if (spi_rx_num)
    {
        UCB0TXBUF = 0xff;
    }
    else
    {
        UCB0IFG &= ~UCRXIFG;
        UCB0IE &= ~UCRXIE;
    }
}

inline void usci_b0_spi_tx_isr_handle(void)
{
    UCB0RXBUF;
    spi_tx_num--;
    if (spi_tx_num)
    {
        UCB0TXBUF = *spi_tx_buff++;
    }
    else
    {
        UCB0IFG &= ~UCTXIFG;
        UCB0IE &= ~UCTXIE;
    }
}

