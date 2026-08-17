/*
 * nrf24_conf.h
 *
 *  Created on: Aug 12, 2026
 *      Author: thuy
 */

#ifndef NRF24_CONF_H_
#define NRF24_CONF_H_

#include "stm32f1xx_hal.h"

/* SPI CONFIG */
extern SPI_HandleTypeDef hspi2;

#define NRF24_SPI 			hspi2

/* GPIO CONFIG */
#define NRF24_CSN_PORT		GPIOA
#define NRF24_CSN_PIN		GPIO_PIN_11

#define NRF24_CE_PORT		GPIOA
#define NRF24_CE_PIN		GPIO_PIN_8

#define NRF24_IRQ_PORT		GPIOB
#define NRF24_IRQ_PIN		GPIO_PIN_12

#define

#endif /* NRF24_CONF_H_ */
