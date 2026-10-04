#ifndef __NRF24L01_H__
#define __NRF24L01_H__

/*
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************

  File:		  NRF24L01.h
  Author:     ControllersTech.com
  Updated:    30th APRIL 2021

  ***************************************************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ***************************************************************************************************************
*/


#include "stm32f1xx_hal.h"

extern SPI_HandleTypeDef hspi2;

#define NRF24_SPI 			&hspi2

/* GPIO CONFIG */
#define NRF24_CS_PORT		GPIOA
#define NRF24_CS_PIN		GPIO_PIN_11

#define NRF24_CE_PORT		GPIOA
#define NRF24_CE_PIN		GPIO_PIN_8

#define NRF24_IRQ_PORT		GPIOB
#define NRF24_IRQ_PIN		GPIO_PIN_12


#define NRF24_PAYLOAD_LENGTH          32     // 1 - 32bytes
#define NRF24_AIR_DATA_RATE          _2Mbps
#define NRF24_RF_TX_OUTPUT_POWER     _0dBm

typedef enum
{
    _250kbps = 2,
    _1Mbps   = 0,
    _2Mbps   = 1
} air_data_rate;

typedef enum
{
    _0dBm  = 3,
    _6dBm  = 2,
    _12dBm = 1,
    _18dBm = 0
} output_power;

typedef enum
{
    _pipe0 = 0,
    _pipe1 = 1,
    _pipe2 = 2,
    _pipe3 = 3,
    _pipe4 = 4,
    _pipe5 = 5
} pipe_e;

/* Main Functions */
void NRF24_Init (void);

void NRF24_TxMode (uint8_t *Address, uint8_t channel);
uint8_t NRF24_Transmit (uint8_t *data);

void NRF24_RxMode (uint8_t *Address, uint8_t channel);
uint8_t isDataAvailable (int pipenum);
void NRF24_Receive (uint8_t *data);

void NRF24_ReadAll (uint8_t *data);



void nrf24_tx_init(uint8_t *addr, uint16_t Mhz);
void nrf24_rx_init(uint8_t *addr, uint16_t MHz, pipe_e _pipe);

uint8_t nrf24_tx_transmit(uint8_t *tx_payload);
void nrf24_rx_receive(pipe_e _pipe,uint8_t *rx_payload);

/* Sub Functions */
void nrf24_reset(uint8_t reg);

void nrf24_prx_mode();
void nrf24_ptx_mode();

void nrf24_power_up();
void nrf24_power_down();

uint8_t nrf24_get_status();
void nrf24_clear_status();
uint8_t nrf24_get_fifo_status();
void nrf24_clear_fifo_status();

//
void nrf24_set_address_widths(uint8_t byte);
void nrf24_set_tx_addr(uint8_t *addr, uint8_t addr_width);
void nrf24_set_tx_addr(uint8_t *addr, uint8_t addr_width);

// Static payload lengths
void nrf24_rx_set_payload_widths(pipe_e _pipe, uint8_t bytes);
uint8_t nrf24_read_rx_fifo(uint8_t* rx_payload);
uint8_t nrf24_write_tx_fifo(uint8_t* tx_payload);

void nrf24_flush_rx_fifo();
void nrf24_flush_tx_fifo();

// Clear IRQ pin. Change LOW to HIGH
void nrf24_clear_rx_dr();
void nrf24_clear_tx_ds();
void nrf24_clear_max_rt();

void nrf24_set_rf_channel(uint16_t MHz);
void nrf24_set_rf_tx_output_power(output_power dBm);
void nrf24_set_rf_air_data_rate(air_data_rate bps);

void nrf24_set_crc_length(uint8_t bytes);
void nrf24_auto_retransmit_count(uint8_t cnt);
void nrf24_auto_retransmit_delay(uint8_t us);
uint8_t nrf24_rx_is_avalible(pipe_e _pipe);

/* Memory Map */
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17
#define DYNPD	    0x1C
#define FEATURE	    0x1D

/* Instruction Mnemonics */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF



/* nRF24L01+ Commands */
#define CMD_R_REGISTER                  0b00000000
#define CMD_W_REGISTER                  0b00100000
#define CMD_R_RX_PAYLOAD                0b01100001
#define CMD_W_TX_PAYLOAD                0b10100000
#define CMD_FLUSH_TX                    0b11100001
#define CMD_FLUSH_RX                    0b11100010
#define CMD_REUSE_TX_PL                 0b11100011
#define CMD_R_RX_PL_WID                 0b01100000
#define CMD_W_ACK_PAYLOAD               0b10101000
#define CMD_W_TX_PAYLOAD_NOACK          0b10110000
#define CMD_NOP                         0b11111111


/* nRF24L01+ Registers */
#define REG_CONFIG            0x00
#define REG_EN_AA             0x01
#define REG_EN_RXADDR         0x02
#define REG_SETUP_AW          0x03
#define REG_SETUP_RETR        0x04
#define REG_RF_CH             0x05
#define REG_RF_SETUP          0x06
#define REG_STATUS            0x07
#define REG_OBSERVE_TX        0x08    // Read-Only
#define REG_RPD               0x09    // Read-Only
#define REG_RX_ADDR_P0        0x0A
#define REG_RX_ADDR_P1        0x0B
#define REG_RX_ADDR_P2        0x0C
#define REG_RX_ADDR_P3        0x0D
#define REG_RX_ADDR_P4        0x0E
#define REG_RX_ADDR_P5        0x0F
#define REG_TX_ADDR           0x10
#define REG_RX_PW_P0          0x11
#define REG_RX_PW_P1          0x12
#define REG_RX_PW_P2          0x13
#define REG_RX_PW_P3          0x14
#define REG_RX_PW_P4          0x15
#define REG_RX_PW_P5          0x16
#define REG_FIFO_STATUS       0x17
#define REG_DYNPD             0x1C
#define REG_FEATURE           0x1D




#endif /* __NRF24L01_H__ */
