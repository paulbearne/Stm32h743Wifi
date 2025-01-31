################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Camera/bspcamera.c \
../Drivers/BSP/Camera/ov2640.c \
../Drivers/BSP/Camera/ov2640_regs.c \
../Drivers/BSP/Camera/ov5640.c \
../Drivers/BSP/Camera/ov5640_regs.c \
../Drivers/BSP/Camera/ov7670.c \
../Drivers/BSP/Camera/ov7670_regs.c \
../Drivers/BSP/Camera/ov7725.c \
../Drivers/BSP/Camera/ov7725_regs.c 

OBJS += \
./Drivers/BSP/Camera/bspcamera.o \
./Drivers/BSP/Camera/ov2640.o \
./Drivers/BSP/Camera/ov2640_regs.o \
./Drivers/BSP/Camera/ov5640.o \
./Drivers/BSP/Camera/ov5640_regs.o \
./Drivers/BSP/Camera/ov7670.o \
./Drivers/BSP/Camera/ov7670_regs.o \
./Drivers/BSP/Camera/ov7725.o \
./Drivers/BSP/Camera/ov7725_regs.o 

C_DEPS += \
./Drivers/BSP/Camera/bspcamera.d \
./Drivers/BSP/Camera/ov2640.d \
./Drivers/BSP/Camera/ov2640_regs.d \
./Drivers/BSP/Camera/ov5640.d \
./Drivers/BSP/Camera/ov5640_regs.d \
./Drivers/BSP/Camera/ov7670.d \
./Drivers/BSP/Camera/ov7670_regs.d \
./Drivers/BSP/Camera/ov7725.d \
./Drivers/BSP/Camera/ov7725_regs.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Camera/%.o Drivers/BSP/Camera/%.su Drivers/BSP/Camera/%.cyclo: ../Drivers/BSP/Camera/%.c Drivers/BSP/Camera/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -DTFT96 -c -I"C:/Dev/st/projects/Stm32h743Wifi/Core/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/App" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/Target" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/hw" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/ST7735" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/W25QXX" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Rtc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Misc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Gpio" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Pwm" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FatFs/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/network" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/app" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/netif" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/transport" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/virtual_serial_if/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/port/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/serial" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/common/protobuf-c" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/components/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/control_lib/src/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/app/control" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/control_lib/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/app/data" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/esp_hosted/host/stm32/driver/transport/spi" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Camera" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Camera

clean-Drivers-2f-BSP-2f-Camera:
	-$(RM) ./Drivers/BSP/Camera/bspcamera.cyclo ./Drivers/BSP/Camera/bspcamera.d ./Drivers/BSP/Camera/bspcamera.o ./Drivers/BSP/Camera/bspcamera.su ./Drivers/BSP/Camera/ov2640.cyclo ./Drivers/BSP/Camera/ov2640.d ./Drivers/BSP/Camera/ov2640.o ./Drivers/BSP/Camera/ov2640.su ./Drivers/BSP/Camera/ov2640_regs.cyclo ./Drivers/BSP/Camera/ov2640_regs.d ./Drivers/BSP/Camera/ov2640_regs.o ./Drivers/BSP/Camera/ov2640_regs.su ./Drivers/BSP/Camera/ov5640.cyclo ./Drivers/BSP/Camera/ov5640.d ./Drivers/BSP/Camera/ov5640.o ./Drivers/BSP/Camera/ov5640.su ./Drivers/BSP/Camera/ov5640_regs.cyclo ./Drivers/BSP/Camera/ov5640_regs.d ./Drivers/BSP/Camera/ov5640_regs.o ./Drivers/BSP/Camera/ov5640_regs.su ./Drivers/BSP/Camera/ov7670.cyclo ./Drivers/BSP/Camera/ov7670.d ./Drivers/BSP/Camera/ov7670.o ./Drivers/BSP/Camera/ov7670.su ./Drivers/BSP/Camera/ov7670_regs.cyclo ./Drivers/BSP/Camera/ov7670_regs.d ./Drivers/BSP/Camera/ov7670_regs.o ./Drivers/BSP/Camera/ov7670_regs.su ./Drivers/BSP/Camera/ov7725.cyclo ./Drivers/BSP/Camera/ov7725.d ./Drivers/BSP/Camera/ov7725.o ./Drivers/BSP/Camera/ov7725.su ./Drivers/BSP/Camera/ov7725_regs.cyclo ./Drivers/BSP/Camera/ov7725_regs.d ./Drivers/BSP/Camera/ov7725_regs.o ./Drivers/BSP/Camera/ov7725_regs.su

.PHONY: clean-Drivers-2f-BSP-2f-Camera

