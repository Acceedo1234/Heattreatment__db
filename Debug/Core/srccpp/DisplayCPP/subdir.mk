################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/srccpp/DisplayCPP/DisplayRoutine.cpp \
../Core/srccpp/DisplayCPP/GLCD.cpp 

OBJS += \
./Core/srccpp/DisplayCPP/DisplayRoutine.o \
./Core/srccpp/DisplayCPP/GLCD.o 

CPP_DEPS += \
./Core/srccpp/DisplayCPP/DisplayRoutine.d \
./Core/srccpp/DisplayCPP/GLCD.d 


# Each subdirectory must supply rules for building sources it contributes
Core/srccpp/DisplayCPP/%.o Core/srccpp/DisplayCPP/%.su: ../Core/srccpp/DisplayCPP/%.cpp Core/srccpp/DisplayCPP/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"D:/SourceTree/Heattreatment/Core/srccpp/Common" -I"D:/SourceTree/Heattreatment/Core/srccpp/DisplayCPP" -I"D:/SourceTree/Heattreatment/Core/srccpp/Modbus" -I"D:/SourceTree/Heattreatment/Core/srccpp/OfflineStorage" -I"D:/SourceTree/Heattreatment/Core/srccpp/Shift" -I"D:/SourceTree/Heattreatment/Core/srccpp/WifiEsp8266" -I"D:/SourceTree/Heattreatment/Core/srccpp" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-srccpp-2f-DisplayCPP

clean-Core-2f-srccpp-2f-DisplayCPP:
	-$(RM) ./Core/srccpp/DisplayCPP/DisplayRoutine.d ./Core/srccpp/DisplayCPP/DisplayRoutine.o ./Core/srccpp/DisplayCPP/DisplayRoutine.su ./Core/srccpp/DisplayCPP/GLCD.d ./Core/srccpp/DisplayCPP/GLCD.o ./Core/srccpp/DisplayCPP/GLCD.su

.PHONY: clean-Core-2f-srccpp-2f-DisplayCPP

