################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ESP8266/esp8266.c \
../Core/Src/ESP8266/esp8266_rx.c 

C_DEPS += \
./Core/Src/ESP8266/esp8266.d \
./Core/Src/ESP8266/esp8266_rx.d 

OBJS += \
./Core/Src/ESP8266/esp8266.o \
./Core/Src/ESP8266/esp8266_rx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/ESP8266/%.o Core/Src/ESP8266/%.su: ../Core/Src/ESP8266/%.c Core/Src/ESP8266/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"D:/SourceTree/Heattreatment/Core/Src/ESP8266" -I"D:/SourceTree/Heattreatment/Core/Src/Internet" -I"D:/SourceTree/Heattreatment/Core/Src/RTC" -I"D:/SourceTree/Heattreatment/Core/Src/W25Q64" -I"D:/SourceTree/Heattreatment/Core/Src/W5500_C" -I"D:/SourceTree/Heattreatment/Core/Src/W5500_C/W5500" -I"D:/SourceTree/Heattreatment/Core/Src/Internet/DHCP" -I"D:/SourceTree/Heattreatment/Core/Src/Internet/DNS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-ESP8266

clean-Core-2f-Src-2f-ESP8266:
	-$(RM) ./Core/Src/ESP8266/esp8266.d ./Core/Src/ESP8266/esp8266.o ./Core/Src/ESP8266/esp8266.su ./Core/Src/ESP8266/esp8266_rx.d ./Core/Src/ESP8266/esp8266_rx.o ./Core/Src/ESP8266/esp8266_rx.su

.PHONY: clean-Core-2f-Src-2f-ESP8266

