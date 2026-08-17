/*
 * nrf24_reg_addr.h
 *
 *  Created on: Aug 12, 2026
 *      Author: thuy
 */

#ifndef NRF24_REG_ADDR_H_
#define NRF24_REG_ADDR_H_

/* REG */
#define CONFIG 		0x00
#define EN_AA		0x01
#define EN_RXADDR	0x02
#define SETUP_AW	0x03
#define SETUP_RETR	0x04
#define RF_CH		0x05
#define RF_SETUP	0x06
#define STATUS		0x07
#define OBSERVE_TX	0x08
#define CD			0x09
#define RX_ADDR_P0	0x0A
//#define RX_ADDR_P1
//#define RX_ADDR_P2
//#define RX_ADDR_P3
//#define RX_ADDR_P4
//#define RX_ADDR_P5
#define TX_ADDR		0x10
#define RX_PW_P0	0x11
//#define RX_PW_P1
//#define RX_PW_P2
//#define RX_PW_P3
//#define RX_PW_P4
//#define RX_PW_P5
#define FIFO_STATUS	0x17
//#define ACK_PLDc
//#define TX_PLD
//#define RX_PLD
#define DYNPDc		0x1C
#define FEATUREc	0x1D



#endif /* NRF24_REG_ADDR_H_ */
