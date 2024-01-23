################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/srccpp/Common/common.cpp 

OBJS += \
./Core/srccpp/Common/common.o 

CPP_DEPS += \
./Core/srccpp/Common/common.d 


# Each subdirectory must supply rules for building sources it contributes
Core/srccpp/Common/%.o Core/srccpp/Common/%.su: ../Core/srccpp/Common/%.cpp Core/srccpp/Common/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/WifiEsp8266" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/Shift" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/OfflineStorage" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/Modbus" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/LpdcLogic" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/Ethernet" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/DisplayCPP" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/Common" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-srccpp-2f-Common

clean-Core-2f-srccpp-2f-Common:
	-$(RM) ./Core/srccpp/Common/common.d ./Core/srccpp/Common/common.o ./Core/srccpp/Common/common.su

.PHONY: clean-Core-2f-srccpp-2f-Common

