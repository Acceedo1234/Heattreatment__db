################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/W5500_C/W5500/w5500.c 

C_DEPS += \
./Core/Src/W5500_C/W5500/w5500.d 

OBJS += \
./Core/Src/W5500_C/W5500/w5500.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/W5500_C/W5500/%.o Core/Src/W5500_C/W5500/%.su: ../Core/Src/W5500_C/W5500/%.c Core/Src/W5500_C/W5500/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"D:/SourceTree/Heattreatment/Core/Src/ESP8266" -I"D:/SourceTree/Heattreatment/Core/Src/Internet" -I"D:/SourceTree/Heattreatment/Core/Src/RTC" -I"D:/SourceTree/Heattreatment/Core/Src/W25Q64" -I"D:/SourceTree/Heattreatment/Core/Src/W5500_C" -I"D:/SourceTree/Heattreatment/Core/Src/W5500_C/W5500" -I"D:/SourceTree/Heattreatment/Core/Src/Internet/DHCP" -I"D:/SourceTree/Heattreatment/Core/Src/Internet/DNS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-W5500_C-2f-W5500

clean-Core-2f-Src-2f-W5500_C-2f-W5500:
	-$(RM) ./Core/Src/W5500_C/W5500/w5500.d ./Core/Src/W5500_C/W5500/w5500.o ./Core/Src/W5500_C/W5500/w5500.su

.PHONY: clean-Core-2f-Src-2f-W5500_C-2f-W5500

