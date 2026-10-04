/*
 * bmp280.h
 *
 *  Created on: Aug 17, 2026
 *      Author: thuy
 */

#ifndef __BMP280_H_
#define __BMP280_H_


#include "stm32f4xx_hal.h"


/**
 * *************************************
 * *********** BMP280 CONFIG ***********
 * *************************************
 * */
extern I2C_HandleTypeDef hi2c1;

#define BMP280_I2C &hi2c1

#define SDO_PIN_HIGH 0    // Logic level of sdo pin
#if SDO_PIN_HIGH
#define BMP280_SLAVE_ADDR (0x77<<1)
#else
#define BMP280_SLAVE_ADDR (0x76<<1)
#endif

#define BPM280_MODE 			MODE_NORMAL
#define BPM280_TEMP_OSRS		OSRS_2			/* Temperature Oversampling  => Oversampling definitions */
#define BPM280_PRES_OSRS		OSRS_2			/* Pressure Oversampling     => Oversampling definitions */
#define BPM280_IIR_FILTER		IIR_4			/* IIR Filter				 => IIR Filter Coefficients */
#define BMP280_TIME_SB			T_SB_125		/* Standby Time				 => Standby Time*/


/*********** BMP280 DEFINE ***********/
// Define data types
#define BMP280_U64_t uint64_t
#define BMP280_U32_t uint32_t
#define BMP280_S64_t int64_t
#define BMP280_S32_t int32_t

// Define Oversampling definitions
#define OSRS_OFF    	0x00
#define OSRS_1    		0x01
#define OSRS_2    		0x02
#define OSRS_4    		0x03
#define OSRS_8    		0x04
#define OSRS_16    		0x05

// Define MODE Definitions
#define MODE_SLEEP      0x00
#define MODE_FORCED     0x01
#define MODE_NORMAL     0x03

// Define Standby Time
#define T_SB_0p5    	0x00
#define T_SB_62p5    	0x01
#define T_SB_125    	0x02
#define T_SB_250    	0x03
#define T_SB_500    	0x04
#define T_SB_1000    	0x05
#define T_SB_2000    	0x06
#define T_SB_4000    	0x07

// Define IIR Filter Coefficients
#define IIR_OFF     	0x00
#define IIR_2     		0x01
#define IIR_4     		0x02
#define IIR_8     		0x03
#define IIR_16     		0x04

/*********** MAIN FUNCTIONS ***********/
uint8_t bmp280_init();
void bmp280_measure(float *temperature, float *pressure);

/*********** SUB FUNCTIONS ***********/
void bmp280_wakeup(void);
uint8_t bmp280_check(void);

/* Memory map */
#define ID_REG 			0xD0
#define RESET_REG 		0xE0
#define STATUS_REG 		0xF3
#define CTRL_MEAS_REG	0xF4
#define CONFIG_REG		0xF5
#define PRESS_MSB_REG	0xF7
#define PRESS_LSB_REG	0xF8
#define PRESS_XLSB_REG	0xF9
#define TEMP_MSP_REG	0xFA
#define TEMP_LSB_REG	0xFB
#define TEMP_XLSB_REG 	0xFC

#endif /* __BMP280_H_ */
