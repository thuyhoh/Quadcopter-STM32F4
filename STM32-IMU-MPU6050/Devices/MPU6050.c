#include "MPU6050.h"

void MPU6050_Init(void)
{
	uint8_t check;
	uint8_t Data;
	
	// 
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 1000); 
	if(check == 0x68)
	{
		// power management
		Data = 0;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, 1000);
		
		// Config Gyroscope Output Rate = 8KHz
		Data = 0;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, CONFIG_REG, 1, &Data, 1, 1000); 
		
		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		// Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
    Data = 0x07;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000);
		
		// Set accelerometer configuration in ACCEL_CONFIG Register
		Data = 0x00;  // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> <strong>±</strong> 2g
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		Data = 0x00;  // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> <strong>±</strong> 250 ?/s
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);
		
	}
}

void MPU6050_Read_ACCEL(ACCELVal_TypeDef *AccelVal)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from ACCEL_XOUT_H (0x3B) register
	HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, 0x3B, 1, Rec_Data, 6, 1000);
	
	AccelVal->AccelX_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	AccelVal->AccelY_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	AccelVal->AccelZ_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);
	
	AccelVal->Ax = (float)(AccelVal->AccelX_RAW /16384.0); 
	AccelVal->Ay = (float)(AccelVal->AccelY_RAW /16384.0);
	AccelVal->Az = (float)(AccelVal->AccelZ_RAW /16384.0);
}

void MPU6050_Read_Gyro(GYROVal_TypeDef *GyroVal)
{
	uint8_t Rec_Data[6];
	// Read 6 BYTES of data starting from GYRO_XOUT_H register
	HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, 0x43, 1, Rec_Data, 6, 1000);

	GyroVal->GyroX_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	GyroVal->GyroY_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	GyroVal->GyroZ_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	GyroVal->Gx = (float)(GyroVal->GyroX_RAW/131.0);
	GyroVal->Gy = (float)(GyroVal->GyroX_RAW/131.0);
	GyroVal->Gz = (float)(GyroVal->GyroX_RAW/131.0);
}



void IMUV_Calculation(IMUVal_TypeDef *IMUVal, GYROVal_TyPeDef *GyroVal)
{
	IMUVal->Roll = float(IMUVal->Roll_pre + GyroVal->Gx*0.01);
	IMUVal->Pitch = float(IMUVal->Pitch_pre + GyroVal->Gy*0.01);
	IMUVal->Yaw = float(IMUVal->Yaw_pre + GyroVal->Gz*0.01);
}
