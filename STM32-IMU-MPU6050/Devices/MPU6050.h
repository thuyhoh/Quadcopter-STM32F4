#ifndef MPU6050_H
#define MPU6050_H

#include "stm32f1xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

#define MPU6050_ADDR 0xD0
#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define CONFIG_REG	0x1A
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C

typedef struct {
	uint16_t AccelX_RAW, AccelZ_RAW, AccelY_RAW;
	float Ax, Ay, Az;
}ACCELVal_TypeDef;

typedef struct {
	uint16_t GyroX_RAW, GyroZ_RAW, GyroY_RAW;
	float Gx, Gy, Gz;
}GYROVal_TyPeDef;

typedef struct {
	float Roll_pre, Pitch_pre, Yaw_pre;
	float Roll, Pitch, Yaw;
}IMUVal_TypeDef;


void MPU6050_Init(void);
void MPU6050_Read_ACCEL(ACCELVal_Tydef *AccelVal);
void MPU6050_Read_Gyro(GYROVal_Tydef *GyroVal);
void IMUV_Calculation(IMUVal_TypeDef *IMUVal, GYROVal_TyPeDef *GyroVal)

#endif