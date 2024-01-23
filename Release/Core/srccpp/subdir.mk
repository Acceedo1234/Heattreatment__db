################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/srccpp/main.cpp 

OBJS += \
./Core/srccpp/main.o 

CPP_DEPS += \
./Core/srccpp/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/srccpp/%.o Core/srccpp/%.su: ../Core/srccpp/%.cpp Core/srccpp/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/WifiEsp8266" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/Shift" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/OfflineStorage" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/Modbus" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/LpdcLogic" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/Ethernet" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/DisplayCPP" -I"E:/naveen Work space/LPDC/stm32/20_2_2023_Lpdc_B1/Core/srccpp/Common" -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-srccpp

clean-Core-2f-srccpp:
	-$(RM) ./Core/srccpp/main.d ./Core/srccpp/main.o ./Core/srccpp/main.su

.PHONY: clean-Core-2f-srccpp

