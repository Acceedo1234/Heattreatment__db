################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/srccpp/HeattreatmentLogic/ApplicationSW.cpp 

OBJS += \
./Core/srccpp/HeattreatmentLogic/ApplicationSW.o 

CPP_DEPS += \
./Core/srccpp/HeattreatmentLogic/ApplicationSW.d 


# Each subdirectory must supply rules for building sources it contributes
Core/srccpp/HeattreatmentLogic/%.o Core/srccpp/HeattreatmentLogic/%.su: ../Core/srccpp/HeattreatmentLogic/%.cpp Core/srccpp/HeattreatmentLogic/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"D:/SourceTree/Heattreatment/Core/srccpp/Common" -I"D:/SourceTree/Heattreatment/Core/srccpp/DisplayCPP" -I"D:/SourceTree/Heattreatment/Core/srccpp/Modbus" -I"D:/SourceTree/Heattreatment/Core/srccpp/OfflineStorage" -I"D:/SourceTree/Heattreatment/Core/srccpp/Shift" -I"D:/SourceTree/Heattreatment/Core/srccpp/WifiEsp8266" -I"D:/SourceTree/Heattreatment/Core/srccpp" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-srccpp-2f-HeattreatmentLogic

clean-Core-2f-srccpp-2f-HeattreatmentLogic:
	-$(RM) ./Core/srccpp/HeattreatmentLogic/ApplicationSW.d ./Core/srccpp/HeattreatmentLogic/ApplicationSW.o ./Core/srccpp/HeattreatmentLogic/ApplicationSW.su

.PHONY: clean-Core-2f-srccpp-2f-HeattreatmentLogic

