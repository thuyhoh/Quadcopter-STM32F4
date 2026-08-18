/*
 * nrf24_conf.h
 *
 *  Created on: Aug 12, 2026
 *      Author: thuy
 */

#ifndef NRF24_CONF_H_
#define NRF24_CONF_H_

#include "stm32f4xx_hal.h"

/* SPI CONFIG */
extern SPI_HandleTypeDef hspi1;

#define NRF24_SPI 			&hspi1

/* GPIO CONFIG */
#define NRF24_CS_PORT		GPIOB
#define NRF24_CS_PIN		GPIO_PIN_2

#define NRF24_CE_PORT		GPIOB
#define NRF24_CE_PIN		GPIO_PIN_0

#define NRF24_IRQ_PORT		GPIOB
#define NRF24_IRQ_PIN		GPIO_PIN_1

typedef struct {
	uint16_t roll;
	uint16_t pitch;
	uint16_t throttle;
	uint16_t yaw;

	uint8_t arm;
	uint8_t fly_mode;
//	uint8_t rth;
//	uint8_t aux1;
}RC_Packet;

typedef enum{
	DISARM,
	ARM
}armMode;


#endif /* NRF24_CONF_H_ */
