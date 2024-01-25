################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Internet/DHCP/dhcp.c 

C_DEPS += \
./Core/Src/Internet/DHCP/dhcp.d 

OBJS += \
./Core/Src/Internet/DHCP/dhcp.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Internet/DHCP/%.o Core/Src/Internet/DHCP/%.su: ../Core/Src/Internet/DHCP/%.c Core/Src/Internet/DHCP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"D:/SourceTree/Heattreatment/Core/Src/ESP8266" -I"D:/SourceTree/Heattreatment/Core/Src/Internet" -I"D:/SourceTree/Heattreatment/Core/Src/RTC" -I"D:/SourceTree/Heattreatment/Core/Src/W25Q64" -I"D:/SourceTree/Heattreatment/Core/Src/W5500_C" -I"D:/SourceTree/Heattreatment/Core/Src/W5500_C/W5500" -I"D:/SourceTree/Heattreatment/Core/Src/Internet/DHCP" -I"D:/SourceTree/Heattreatment/Core/Src/Internet/DNS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Internet-2f-DHCP

clean-Core-2f-Src-2f-Internet-2f-DHCP:
	-$(RM) ./Core/Src/Internet/DHCP/dhcp.d ./Core/Src/Internet/DHCP/dhcp.o ./Core/Src/Internet/DHCP/dhcp.su

.PHONY: clean-Core-2f-Src-2f-Internet-2f-DHCP

