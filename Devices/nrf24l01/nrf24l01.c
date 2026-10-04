 /*
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************

  File:		  NRF24L01.c
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


//#include "stm32f1xx_hal.h"
#include "nrf24l01.h"


/* static functions */
static void nrf24_cs_high();
static void nrf24_cs_low();
static void nrf24_ce_high();
static void nrf24_ce_low();
static uint8_t nrf24_read_reg(uint8_t reg);
static uint8_t nrf24_write_reg (uint8_t reg, uint8_t value);
static void nrf24_write_multi_reg(uint8_t reg, uint8_t *data, uint8_t len);
static void nrf24_read_multi_reg(uint8_t reg, uint8_t *data, uint8_t len);


/* static functions */
static void nrf24_cs_low (void)
{
	HAL_GPIO_WritePin(NRF24_CS_PORT, NRF24_CS_PIN, GPIO_PIN_RESET);
}

static void nrf24_cs_high (void)
{
	HAL_GPIO_WritePin(NRF24_CS_PORT, NRF24_CS_PIN, GPIO_PIN_SET);
}


static void nrf24_ce_high (void)
{
	HAL_GPIO_WritePin(NRF24_CE_PORT, NRF24_CE_PIN, GPIO_PIN_SET);
}

static void nrf24_ce_low(void)
{
	HAL_GPIO_WritePin(NRF24_CE_PORT, NRF24_CE_PIN, GPIO_PIN_RESET);
}

static uint8_t nrf24_write_reg (uint8_t reg, uint8_t value)
{
	uint8_t command = CMD_W_REGISTER | reg;
	uint8_t status;
    uint8_t write_val = value;

	nrf24_cs_low();

    HAL_SPI_TransmitReceive(NRF24_SPI, &command, &status, 1, 2000);
    HAL_SPI_Transmit(NRF24_SPI, &write_val, 1, 2000);
	nrf24_cs_high();

	return write_val;
}

static uint8_t nrf24_read_reg(uint8_t reg)
{
	uint8_t command = CMD_R_REGISTER | reg;
	uint8_t status;
	uint8_t read_val;

	nrf24_cs_low();

	HAL_SPI_TransmitReceive(NRF24_SPI, &command, &status, 1, 2000);
	HAL_SPI_Receive(NRF24_SPI, &read_val, 1, 2000);
	nrf24_cs_high();

	return read_val;
}

static void nrf24_write_multi_reg(uint8_t reg, uint8_t* data, uint8_t length)
{
	uint8_t command = CMD_W_REGISTER | reg;
	uint8_t status;

	nrf24_cs_low();

	HAL_SPI_TransmitReceive(NRF24_SPI, &command, &status, 1, 2000);
	HAL_SPI_Transmit(NRF24_SPI, data, length, 2000);
	
	nrf24_cs_high();
}


// send the command to the NRF
void nrfsendCmd (uint8_t cmd)
{
	// Pull the CS Pin LOW to select the device
	nrf24_cs_low();

	HAL_SPI_Transmit(NRF24_SPI, &cmd, 1, 100);

	// Pull the CS HIGH to release the device
	nrf24_cs_high();
}

void nrf24_clear_status()
{

}

void nrf24_reset(uint8_t REG)
{
	if (REG == STATUS)
	{
		nrf24_write_reg(STATUS, 0x00);
	}

	else if (REG == FIFO_STATUS)
	{
		nrf24_write_reg(FIFO_STATUS, 0x11);
	}

	else {
	nrf24_write_reg(CONFIG, 0x08);
	nrf24_write_reg(EN_AA, 0x00);
	nrf24_write_reg(EN_RXADDR, 0x03);
	nrf24_write_reg(SETUP_AW, 0x03);
	nrf24_write_reg(SETUP_RETR, 0x00);
	nrf24_write_reg(RF_CH,  0x03);
	nrf24_write_reg(RF_SETUP, 0x0E);
	nrf24_write_reg(STATUS, 0x00);
	nrf24_write_reg(OBSERVE_TX, 0x00);
	nrf24_write_reg(CD, 0x00);
	uint8_t rx_addr_p0_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	nrf24_write_multi_reg(RX_ADDR_P0, rx_addr_p0_def, 5);
	uint8_t rx_addr_p1_def[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
	nrf24_write_multi_reg(RX_ADDR_P1, rx_addr_p1_def, 5);
	nrf24_write_reg(RX_ADDR_P2, 0xC3);
	nrf24_write_reg(RX_ADDR_P3, 0xC4);
	nrf24_write_reg(RX_ADDR_P4, 0xC5);
	nrf24_write_reg(RX_ADDR_P5, 0xC6);
	uint8_t tx_addr_def[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
	nrf24_write_multi_reg(TX_ADDR, tx_addr_def, 5);
	nrf24_write_reg(RX_PW_P0, 0);
	nrf24_write_reg(RX_PW_P1, 0);
	nrf24_write_reg(RX_PW_P2, 0);
	nrf24_write_reg(RX_PW_P3, 0);
	nrf24_write_reg(RX_PW_P4, 0);
	nrf24_write_reg(RX_PW_P5, 0);
	nrf24_write_reg(FIFO_STATUS, 0x11);
	nrf24_write_reg(DYNPD, 0);
	nrf24_write_reg(FEATURE, 0);
	}
}




void NRF24_Init (void)
{
	// disable the chip before configuring the device
	nrf24_ce_low();

	// reset everything
	 nrf24_reset (0);

	nrf24_write_reg(CONFIG, 0);  // will be configured later

	nrf24_write_reg(EN_AA, 0);  // No Auto ACK

	nrf24_write_reg (EN_RXADDR, 0);  // Not Enabling any data pipe right now
	nrf24_write_reg (SETUP_AW, 0x03);  // 5 Bytes for the TX/RX address
	nrf24_write_reg (SETUP_RETR, 0);   // No retransmission

	nrf24_write_reg (RF_CH, 0);  // will be setup during Tx or RX

	nrf24_write_reg (RF_SETUP, 0x0E);   // Power= 0db, data rate = 2Mbps

	// Enable the chip after configuring the device
	nrf24_ce_high();
}


// set up the Tx mode

void NRF24_TxMode (uint8_t *Address, uint8_t channel)
{
	// disable the chip before configuring the device
	nrf24_ce_low();

	nrf24_write_reg (RF_CH, channel);  // select the channel

	nrf24_write_multi_reg(TX_ADDR, Address, 5);  // Write the TX address


	// power up the device
	uint8_t config = nrf24_read_reg(CONFIG);
	config = config | (1<<1);   // write 1 in the PWR_UP bit
//	config = config & (0xF2);    // write 0 in the PRIM_RX, and 1 in the PWR_UP, and all other bits are masked
	nrf24_write_reg (CONFIG, config);

	// Enable the chip after configuring the device
	nrf24_ce_high();
}

void nrf24_tx_init(uint8_t *addr, uint16_t MHz)
{
	nrf24_ce_low();
	nrf24_reset (0);

	HAL_Delay(1);

	nrf24_set_rf_tx_output_power(NRF24_RF_TX_OUTPUT_POWER);
	nrf24_set_rf_air_data_rate(NRF24_AIR_DATA_RATE);

	nrf24_set_rf_channel(MHz);

	nrf24_set_tx_addr(addr, 5);

	// nrf24_set_crc_length(1);

    // nrf24_auto_retransmit_count(3);
    // nrf24_auto_retransmit_delay(250);

	nrf24_ptx_mode();
	nrf24_power_up();

	nrf24_ce_high();
}

uint8_t nrf24_tx_transmit(uint8_t *data)
{
	nrf24_write_tx_fifo(data);

	HAL_Delay(1);
	uint8_t fifo_status = nrf24_get_fifo_status();

	if ((fifo_status&(1<<4)) && (!(fifo_status&(1<<3))))
	{
		nrf24_flush_tx_fifo();
		nrf24_clear_fifo_status();
		return 1;
	}

	return 0;
}

void nrf24_rx_init(uint8_t *addr, uint16_t MHz, pipe_e _pipe)
{
	nrf24_ce_low();
	nrf24_reset (0);

	HAL_Delay(1);

	nrf24_set_rf_tx_output_power(NRF24_RF_TX_OUTPUT_POWER);
	nrf24_set_rf_air_data_rate(NRF24_AIR_DATA_RATE);

	nrf24_set_rf_channel(MHz);

	nrf24_prx_mode();
	nrf24_power_up();

	nrf24_ce_high();
}

void nrf24_set_tx_addr(uint8_t *addr, uint8_t addr_width)
{
	nrf24_set_address_widths(addr_width);
	nrf24_write_multi_reg(REG_TX_ADDR, addr, addr_width);
}

// transmit the data

uint8_t NRF24_Transmit (uint8_t *data)
{
	uint8_t cmdtosend = 0;

	// select the device
	nrf24_cs_low();

	// payload command
	cmdtosend = W_TX_PAYLOAD;
	HAL_SPI_Transmit(NRF24_SPI, &cmdtosend, 1, 100);

	// send the payload
	HAL_SPI_Transmit(NRF24_SPI, data, 32, 1000);

	// Unselect the device
	nrf24_cs_high();

	HAL_Delay(1);

	uint8_t fifostatus = nrf24_read_reg(FIFO_STATUS);

	// check the fourth bit of FIFO_STATUS to know if the TX fifo is empty
	if ((fifostatus&(1<<4)) && (!(fifostatus&(1<<3))))
	{
		cmdtosend = FLUSH_TX;
		nrfsendCmd(cmdtosend);

		// reset FIFO_STATUS
		nrf24_reset (FIFO_STATUS);

		return 1;
	}

	return 0;
}


void NRF24_RxMode (uint8_t *Address, uint8_t channel)
{
	// disable the chip before configuring the device
	nrf24_ce_low();

//	nrf24_reset (STATUS);

	nrf24_write_reg (RF_CH, channel);  // select the channel

	// select data pipe 1
	uint8_t en_rxaddr = nrf24_read_reg(EN_RXADDR);
	en_rxaddr = en_rxaddr | (1<<1);
	nrf24_write_reg (EN_RXADDR, en_rxaddr);

	/* We must write the address for Data Pipe 1, if we want to use any pipe from 2 to 5
	 * The Address from DATA Pipe 2 to Data Pipe 5 differs only in the LSB
	 * Their 4 MSB Bytes will still be same as Data Pipe 1
	 *
	 * For Eg->
	 * Pipe 1 ADDR = 0xAABBCCDD11
	 * Pipe 2 ADDR = 0xAABBCCDD22
	 * Pipe 3 ADDR = 0xAABBCCDD33
	 *
	 */
	nrf24_write_multi_reg(RX_ADDR_P1, Address, 5);  // Write the Pipe1 address
//	nrf24_write_reg(RX_ADDR_P2, 0xEE);  // Write the Pipe2 LSB address

	nrf24_write_reg (RX_PW_P1, 32);   // 32 bit payload size for pipe 2


	// power up the device in Rx mode
	uint8_t config = nrf24_read_reg(CONFIG);
	config = config | (1<<1) | (1<<0);
	nrf24_write_reg (CONFIG, config);

	// Enable the chip after configuring the device
	nrf24_ce_high();
}


uint8_t isDataAvailable (int pipenum)
{
	uint8_t status = nrf24_read_reg(STATUS);

	if ((status&(1<<6))&&(status&(pipenum<<1)))
	{

		nrf24_write_reg(STATUS, (1<<6));

		return 1;
	}

	return 0;
}


void NRF24_Receive (uint8_t *data)
{
	uint8_t cmdtosend = 0;

	// select the device
	nrf24_cs_low();

	// payload command
	cmdtosend = R_RX_PAYLOAD;
	HAL_SPI_Transmit(NRF24_SPI, &cmdtosend, 1, 100);

	// Receive the payload
	HAL_SPI_Receive(NRF24_SPI, data, 32, 1000);

	// Unselect the device
	nrf24_cs_high();

	HAL_Delay(1);

	cmdtosend = FLUSH_RX;
	nrfsendCmd(cmdtosend);
}



/* sub functions */
void nrf24_prx_mode()
{
    uint8_t new_config = nrf24_read_reg(REG_CONFIG);
    new_config |= 1 << 0;

    nrf24_write_reg(REG_CONFIG, new_config);
}

void nrf24_ptx_mode()
{
    uint8_t new_config = nrf24_read_reg(REG_CONFIG);
    new_config &= 0xFE;

    nrf24_write_reg(REG_CONFIG, new_config);
}

uint8_t nrf24_read_rx_fifo(uint8_t* rx_payload)
{
    uint8_t command = CMD_R_RX_PAYLOAD;
    uint8_t status;

    nrf24_cs_low();
    HAL_SPI_TransmitReceive(NRF24_SPI, &command, &status, 1, 2000);
    HAL_SPI_Receive(NRF24_SPI, rx_payload, NRF24_PAYLOAD_LENGTH, 2000);
    nrf24_cs_high();

    return status;
}

uint8_t nrf24_write_tx_fifo(uint8_t* tx_payload)
{
    uint8_t command = CMD_W_TX_PAYLOAD;
    uint8_t status;

    nrf24_cs_low();
    HAL_SPI_TransmitReceive(NRF24_SPI, &command, &status, 1, 2000);
    HAL_SPI_Transmit(NRF24_SPI, tx_payload, NRF24_PAYLOAD_LENGTH, 2000);
    nrf24_cs_high(); 

    return status;
}

void nrf24_flush_rx_fifo()
{
    uint8_t command = CMD_FLUSH_RX;
    uint8_t status;

    nrf24_cs_low();
    HAL_SPI_TransmitReceive(NRF24_SPI, &command, &status, 1, 2000);
    nrf24_cs_high();
}

void nrf24_flush_tx_fifo()
{
    uint8_t command = CMD_FLUSH_TX;
    uint8_t status;

    nrf24_cs_low();
	HAL_SPI_TransmitReceive(NRF24_SPI, &command, &status, 1, 2000);
    nrf24_cs_high();
}

void nrf24_clear_fifo_status()
{
	uint8_t new_fifo_statis = nrf24_get_fifo_status();
	new_fifo_statis |= 0x11;
	nrf24_write_reg(REG_FIFO_STATUS, new_fifo_statis);
}	

uint8_t nrf24_get_status()
{
    uint8_t command = CMD_NOP;
    uint8_t status;

    nrf24_cs_low();
    HAL_SPI_TransmitReceive(NRF24_SPI, &command, &status, 1, 2000);
    nrf24_cs_high(); 

    return status;
}

uint8_t nrf24_get_fifo_status()
{
    return nrf24_read_reg(REG_FIFO_STATUS);
}

void nrf24_rx_set_payload_widths(pipe_e _pipe, uint8_t bytes)
{
    nrf24_write_reg(REG_RX_PW_P0 + _pipe, bytes);
}

void nrf24_power_up()
{
    uint8_t new_config = nrf24_read_reg(REG_CONFIG);
    new_config |= 1 << 1;

    nrf24_write_reg(REG_CONFIG, new_config);
}

void nrf24_power_down()
{
    uint8_t new_config = nrf24_read_reg(REG_CONFIG);
    new_config &= 0xFD;

    nrf24_write_reg(REG_CONFIG, new_config);
}

void nrf24_set_crc_length(uint8_t bytes)
{
    uint8_t new_config = nrf24_read_reg(REG_CONFIG);
    
    switch(bytes)
    {
        // CRCO bit in CONFIG resiger set 0
        case 1:
            new_config &= 0xFB;
            break;
        // CRCO bit in CONFIG resiger set 1
        case 2:
            new_config |= 1 << 2;
            break;
    }

    nrf24_write_reg(REG_CONFIG, new_config);
}

void nrf24_set_address_widths(uint8_t bytes)
{
    nrf24_write_reg(REG_SETUP_AW, bytes - 2);
}

void nrf24_auto_retransmit_count(uint8_t cnt)
{
    uint8_t new_setup_retr = nrf24_read_reg(REG_SETUP_RETR);
    
    // Reset ARC register 0
    new_setup_retr |= 0xF0;
    new_setup_retr |= cnt;
    nrf24_write_reg(REG_SETUP_RETR, new_setup_retr);
}

void nrf24_auto_retransmit_delay(uint8_t us)
{
    uint8_t new_setup_retr = nrf24_read_reg(REG_SETUP_RETR);

    // Reset ARD register 0
    new_setup_retr |= 0x0F;
    new_setup_retr |= ((us / 250) - 1) << 4;
    nrf24_write_reg(REG_SETUP_RETR, new_setup_retr);
}

void nrf24_set_rf_channel(uint16_t MHz)
{
	uint16_t new_rf_ch = MHz - 2400;
    nrf24_write_reg(REG_RF_CH, new_rf_ch);
}

void nrf24_set_rf_air_data_rate(air_data_rate bps)
{
    // Set value to 0
    uint8_t new_rf_setup = nrf24_read_reg(REG_RF_SETUP) & 0xD7;
    
    switch(bps)
    {
        case _1Mbps: 
            break;
        case _2Mbps: 
            new_rf_setup |= 1 << 3;
            break;
        case _250kbps:
            new_rf_setup |= 1 << 5;
            break;
    }
    nrf24_write_reg(REG_RF_SETUP, new_rf_setup);
}

void nrf24_set_tx_address(uint8_t* tx_addr, uint8_t tx_addr_width)
{
	nrf24_set_address_widths(tx_addr_width);
	nrf24_write_multi_reg(REG_TX_ADDR, tx_addr, tx_addr_width);
}

void nrf24_set_rx_pipe(pipe_e _pipe)
{
	nrf24_write_reg(REG_EN_RXADDR, (1 << _pipe));
}

void nrf24_set_rf_tx_output_power(output_power dBm)
{
    uint8_t new_rf_setup = nrf24_read_reg(REG_RF_SETUP) & 0xF9;
    new_rf_setup |= (dBm << 1);

    nrf24_write_reg(REG_RF_SETUP, new_rf_setup);
}

uint8_t nrf24_rx_is_avalible(pipe_e _pipe)
{
	uint8_t status = nrf24_get_status();
	if((status & (1<<6)) &&(status &(1<<_pipe)))
	{
		nrf24_write_reg(REG_STATUS, (1<<6));
		return 1;
	}
	return 0;
}
