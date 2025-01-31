################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_bt.c \
../Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_rb.c \
../Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_serial.c \
../Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_stats.c \
../Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/main.c 

OBJS += \
./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_bt.o \
./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_rb.o \
./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_serial.o \
./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_stats.o \
./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/main.o 

C_DEPS += \
./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_bt.d \
./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_rb.d \
./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_serial.d \
./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_stats.d \
./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/main.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/%.o Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/%.su Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/%.cyclo: ../Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/%.c Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -DTFT96 -c -I"C:/Dev/st/projects/Stm32h743Wifi/Core/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/App" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/Target" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/hw" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/ST7735" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/W25QXX" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Rtc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Misc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Gpio" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Pwm" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FatFs/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/network" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/app" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/netif" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/transport" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/virtual_serial_if/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/port/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/serial" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/common/protobuf-c" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/components/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/control_lib/src/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/app/control" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/control_lib/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/app/data" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/transport/spi" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-esp_hosted-2f-host-2f-linux-2f-host_driver-2f-esp32

clean-Middlewares-2f-Third_Party-2f-esp_hosted-2f-host-2f-linux-2f-host_driver-2f-esp32:
	-$(RM) ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_bt.cyclo ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_bt.d ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_bt.o ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_bt.su ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_rb.cyclo ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_rb.d ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_rb.o ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_rb.su ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_serial.cyclo ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_serial.d ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_serial.o ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_serial.su ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_stats.cyclo ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_stats.d ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_stats.o ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/esp_stats.su ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/main.cyclo ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/main.d ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/main.o ./Middlewares/Third_Party/esp_hosted/host/linux/host_driver/esp32/main.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-esp_hosted-2f-host-2f-linux-2f-host_driver-2f-esp32

