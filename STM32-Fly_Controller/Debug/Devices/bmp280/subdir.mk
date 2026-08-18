################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Devices/bmp280/bmp280.c 

OBJS += \
./Devices/bmp280/bmp280.o 

C_DEPS += \
./Devices/bmp280/bmp280.d 


# Each subdirectory must supply rules for building sources it contributes
Devices/bmp280/%.o Devices/bmp280/%.su Devices/bmp280/%.cyclo: ../Devices/bmp280/%.c Devices/bmp280/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/thuy/embedded/project/Quadcopter-STM32F4/STM32-Fly_Controller/Devices/nrf24l01" -I"/home/thuy/embedded/project/Quadcopter-STM32F4/STM32-Fly_Controller/Devices/bmp280" -I"/home/thuy/embedded/project/Quadcopter-STM32F4/STM32-Fly_Controller/Devices/hmc5883l" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Devices-2f-bmp280

clean-Devices-2f-bmp280:
	-$(RM) ./Devices/bmp280/bmp280.cyclo ./Devices/bmp280/bmp280.d ./Devices/bmp280/bmp280.o ./Devices/bmp280/bmp280.su

.PHONY: clean-Devices-2f-bmp280

