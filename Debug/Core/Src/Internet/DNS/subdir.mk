################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Internet/DNS/dns.c 

C_DEPS += \
./Core/Src/Internet/DNS/dns.d 

OBJS += \
./Core/Src/Internet/DNS/dns.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Internet/DNS/%.o Core/Src/Internet/DNS/%.su: ../Core/Src/Internet/DNS/%.c Core/Src/Internet/DNS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/Src/ESP8266" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/Src/Internet" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/Src/RTC" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/Src/W25Q64" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/Src/W5500_C" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/Src/W5500_C/W5500" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/Src/Internet/DHCP" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/Src/Internet/DNS" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Internet-2f-DNS

clean-Core-2f-Src-2f-Internet-2f-DNS:
	-$(RM) ./Core/Src/Internet/DNS/dns.d ./Core/Src/Internet/DNS/dns.o ./Core/Src/Internet/DNS/dns.su

.PHONY: clean-Core-2f-Src-2f-Internet-2f-DNS

