################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/srccpp/Modbus/Modbusrtu.cpp 

OBJS += \
./Core/srccpp/Modbus/Modbusrtu.o 

CPP_DEPS += \
./Core/srccpp/Modbus/Modbusrtu.d 


# Each subdirectory must supply rules for building sources it contributes
Core/srccpp/Modbus/%.o Core/srccpp/Modbus/%.su: ../Core/srccpp/Modbus/%.cpp Core/srccpp/Modbus/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/srccpp/Common" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/srccpp/DisplayCPP" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/srccpp/Modbus" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/srccpp/OfflineStorage" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/srccpp/Shift" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/srccpp/WifiEsp8266" -I"D:/Naveen_wrkspace/Heattreatment/USM_stm32_migration/heattreatment_USM2_stm_09_10_23_B1/Core/srccpp" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-srccpp-2f-Modbus

clean-Core-2f-srccpp-2f-Modbus:
	-$(RM) ./Core/srccpp/Modbus/Modbusrtu.d ./Core/srccpp/Modbus/Modbusrtu.o ./Core/srccpp/Modbus/Modbusrtu.su

.PHONY: clean-Core-2f-srccpp-2f-Modbus

