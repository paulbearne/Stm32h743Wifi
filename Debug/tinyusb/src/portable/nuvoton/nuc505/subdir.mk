################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/src/portable/nuvoton/nuc505/dcd_nuc505.c 

OBJS += \
./tinyusb/src/portable/nuvoton/nuc505/dcd_nuc505.o 

C_DEPS += \
./tinyusb/src/portable/nuvoton/nuc505/dcd_nuc505.d 


# Each subdirectory must supply rules for building sources it contributes
tinyusb/src/portable/nuvoton/nuc505/%.o tinyusb/src/portable/nuvoton/nuc505/%.su tinyusb/src/portable/nuvoton/nuc505/%.cyclo: ../tinyusb/src/portable/nuvoton/nuc505/%.c tinyusb/src/portable/nuvoton/nuc505/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -DTFT96 -c -I"C:/Dev/st/projects/Stm32h743Wifi/Core/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/App" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/Target" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/hw" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/ST7735" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/W25QXX" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Rtc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Misc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Gpio" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Pwm" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FatFs/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/network" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/app" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/netif" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/transport" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/virtual_serial_if/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/port/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/serial" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/common/protobuf-c" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/components/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/control_lib/src/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/app/control" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/control_lib/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/app/data" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/transport/spi" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Camera" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-tinyusb-2f-src-2f-portable-2f-nuvoton-2f-nuc505

clean-tinyusb-2f-src-2f-portable-2f-nuvoton-2f-nuc505:
	-$(RM) ./tinyusb/src/portable/nuvoton/nuc505/dcd_nuc505.cyclo ./tinyusb/src/portable/nuvoton/nuc505/dcd_nuc505.d ./tinyusb/src/portable/nuvoton/nuc505/dcd_nuc505.o ./tinyusb/src/portable/nuvoton/nuc505/dcd_nuc505.su

.PHONY: clean-tinyusb-2f-src-2f-portable-2f-nuvoton-2f-nuc505

