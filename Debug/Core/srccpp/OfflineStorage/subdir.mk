################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/srccpp/OfflineStorage/OfflineStorage.cpp 

OBJS += \
./Core/srccpp/OfflineStorage/OfflineStorage.o 

CPP_DEPS += \
./Core/srccpp/OfflineStorage/OfflineStorage.d 


# Each subdirectory must supply rules for building sources it contributes
Core/srccpp/OfflineStorage/%.o Core/srccpp/OfflineStorage/%.su: ../Core/srccpp/OfflineStorage/%.cpp Core/srccpp/OfflineStorage/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L433xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"D:/SourceTree/Heattreatment/Core/srccpp/Common" -I"D:/SourceTree/Heattreatment/Core/srccpp/DisplayCPP" -I"D:/SourceTree/Heattreatment/Core/srccpp/Modbus" -I"D:/SourceTree/Heattreatment/Core/srccpp/OfflineStorage" -I"D:/SourceTree/Heattreatment/Core/srccpp/Shift" -I"D:/SourceTree/Heattreatment/Core/srccpp/WifiEsp8266" -I"D:/SourceTree/Heattreatment/Core/srccpp" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-srccpp-2f-OfflineStorage

clean-Core-2f-srccpp-2f-OfflineStorage:
	-$(RM) ./Core/srccpp/OfflineStorage/OfflineStorage.d ./Core/srccpp/OfflineStorage/OfflineStorage.o ./Core/srccpp/OfflineStorage/OfflineStorage.su

.PHONY: clean-Core-2f-srccpp-2f-OfflineStorage

