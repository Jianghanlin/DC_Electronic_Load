/*
 * USCI_B0_SPI.h
 *
 *  Created on: 2020Äê11ÔÂ23ÈÕ
 *      Author: www14
 */

#ifndef SRC_USCI_B0_SPI_H_
#define SRC_USCI_B0_SPI_H_
#include <stdint.h>
extern unsigned char usci_b0_spi_transmit_frame(uint8_t *p_buff, uint8_t num);
extern unsigned char usci_b0_spi_receive_frame(uint8_t *p_buff, uint8_t num);

extern void usci_b0_spi_tx_isr_handle(void);
extern void usci_b0_spi_rx_isr_handle(void);

extern void usci_b0_spi_init(void);

#endif /* SRC_USCI_B0_SPI_H_ */
