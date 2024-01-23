################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/W5500_C/socket.c \
../Core/Src/W5500_C/w5500_spi.c \
../Core/Src/W5500_C/wizchip_conf.c 

C_DEPS += \
./Core/Src/W5500_C/socket.d \
./Core/Src/W5500_C/w5500_spi.d \
./Core/Src/W5500_C/wizchip_conf.d 

OBJS += \
./Core/Src/W5500_C/socket.o \
./Core/Src/W5500_C/w5500_spi.o \
./Core/Src/W5500_C/wizchip_conf.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/W5500_C/%.o Core/Src/W5500_C/%.su: ../Core/Src/W5500_C/%.c Core/Src/W5500_C/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/Src/W5500_C" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/Src/W25Q64" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/Src/RTC" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/Src/ESP8266" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-W5500_C

clean-Core-2f-Src-2f-W5500_C:
	-$(RM) ./Core/Src/W5500_C/socket.d ./Core/Src/W5500_C/socket.o ./Core/Src/W5500_C/socket.su ./Core/Src/W5500_C/w5500_spi.d ./Core/Src/W5500_C/w5500_spi.o ./Core/Src/W5500_C/w5500_spi.su ./Core/Src/W5500_C/wizchip_conf.d ./Core/Src/W5500_C/wizchip_conf.o ./Core/Src/W5500_C/wizchip_conf.su

.PHONY: clean-Core-2f-Src-2f-W5500_C

