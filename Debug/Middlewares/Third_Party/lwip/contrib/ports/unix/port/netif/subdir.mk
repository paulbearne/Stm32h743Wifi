################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/fifo.c \
../Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/list.c \
../Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/pcapif.c \
../Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/sio.c \
../Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/tapif.c 

OBJS += \
./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/fifo.o \
./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/list.o \
./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/pcapif.o \
./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/sio.o \
./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/tapif.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/fifo.d \
./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/list.d \
./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/pcapif.d \
./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/sio.d \
./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/tapif.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/%.o Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/%.su Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/%.cyclo: ../Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/%.c Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -DTFT96 -c -I"C:/Dev/st/projects/Stm32h743Wifi/Core/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/App" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/Target" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/hw" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/ST7735" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/W25QXX" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Rtc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Misc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Gpio" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Pwm" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FatFs/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/control" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/data" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/netif" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/network" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/serial" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/spi" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/host_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Core/lwip" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/protobuf-c" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/lwip/src/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/lwip/contrib/ports/freertos/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-contrib-2f-ports-2f-unix-2f-port-2f-netif

clean-Middlewares-2f-Third_Party-2f-lwip-2f-contrib-2f-ports-2f-unix-2f-port-2f-netif:
	-$(RM) ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/fifo.cyclo ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/fifo.d ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/fifo.o ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/fifo.su ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/list.cyclo ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/list.d ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/list.o ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/list.su ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/pcapif.cyclo ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/pcapif.d ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/pcapif.o ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/pcapif.su ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/sio.cyclo ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/sio.d ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/sio.o ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/sio.su ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/tapif.cyclo ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/tapif.d ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/tapif.o ./Middlewares/Third_Party/lwip/contrib/ports/unix/port/netif/tapif.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-contrib-2f-ports-2f-unix-2f-port-2f-netif

