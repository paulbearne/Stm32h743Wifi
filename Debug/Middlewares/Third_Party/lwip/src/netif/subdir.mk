################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/src/netif/bridgeif.c \
../Middlewares/Third_Party/lwip/src/netif/bridgeif_fdb.c \
../Middlewares/Third_Party/lwip/src/netif/ethernet.c \
../Middlewares/Third_Party/lwip/src/netif/lowpan6.c \
../Middlewares/Third_Party/lwip/src/netif/lowpan6_ble.c \
../Middlewares/Third_Party/lwip/src/netif/lowpan6_common.c \
../Middlewares/Third_Party/lwip/src/netif/slipif.c \
../Middlewares/Third_Party/lwip/src/netif/zepif.c 

OBJS += \
./Middlewares/Third_Party/lwip/src/netif/bridgeif.o \
./Middlewares/Third_Party/lwip/src/netif/bridgeif_fdb.o \
./Middlewares/Third_Party/lwip/src/netif/ethernet.o \
./Middlewares/Third_Party/lwip/src/netif/lowpan6.o \
./Middlewares/Third_Party/lwip/src/netif/lowpan6_ble.o \
./Middlewares/Third_Party/lwip/src/netif/lowpan6_common.o \
./Middlewares/Third_Party/lwip/src/netif/slipif.o \
./Middlewares/Third_Party/lwip/src/netif/zepif.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/src/netif/bridgeif.d \
./Middlewares/Third_Party/lwip/src/netif/bridgeif_fdb.d \
./Middlewares/Third_Party/lwip/src/netif/ethernet.d \
./Middlewares/Third_Party/lwip/src/netif/lowpan6.d \
./Middlewares/Third_Party/lwip/src/netif/lowpan6_ble.d \
./Middlewares/Third_Party/lwip/src/netif/lowpan6_common.d \
./Middlewares/Third_Party/lwip/src/netif/slipif.d \
./Middlewares/Third_Party/lwip/src/netif/zepif.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/src/netif/%.o Middlewares/Third_Party/lwip/src/netif/%.su Middlewares/Third_Party/lwip/src/netif/%.cyclo: ../Middlewares/Third_Party/lwip/src/netif/%.c Middlewares/Third_Party/lwip/src/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -DTFT96 -c -I"C:/Dev/st/projects/Stm32h743Wifi/Core/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/App" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/Target" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/hw" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/ST7735" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/W25QXX" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Rtc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Misc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Gpio" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Pwm" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FatFs/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/control" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/data" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/netif" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/network" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/serial" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/spi" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/host_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Core/lwip" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/protobuf-c" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/lwip/contrib/ports/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-netif

clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-netif:
	-$(RM) ./Middlewares/Third_Party/lwip/src/netif/bridgeif.cyclo ./Middlewares/Third_Party/lwip/src/netif/bridgeif.d ./Middlewares/Third_Party/lwip/src/netif/bridgeif.o ./Middlewares/Third_Party/lwip/src/netif/bridgeif.su ./Middlewares/Third_Party/lwip/src/netif/bridgeif_fdb.cyclo ./Middlewares/Third_Party/lwip/src/netif/bridgeif_fdb.d ./Middlewares/Third_Party/lwip/src/netif/bridgeif_fdb.o ./Middlewares/Third_Party/lwip/src/netif/bridgeif_fdb.su ./Middlewares/Third_Party/lwip/src/netif/ethernet.cyclo ./Middlewares/Third_Party/lwip/src/netif/ethernet.d ./Middlewares/Third_Party/lwip/src/netif/ethernet.o ./Middlewares/Third_Party/lwip/src/netif/ethernet.su ./Middlewares/Third_Party/lwip/src/netif/lowpan6.cyclo ./Middlewares/Third_Party/lwip/src/netif/lowpan6.d ./Middlewares/Third_Party/lwip/src/netif/lowpan6.o ./Middlewares/Third_Party/lwip/src/netif/lowpan6.su ./Middlewares/Third_Party/lwip/src/netif/lowpan6_ble.cyclo ./Middlewares/Third_Party/lwip/src/netif/lowpan6_ble.d ./Middlewares/Third_Party/lwip/src/netif/lowpan6_ble.o ./Middlewares/Third_Party/lwip/src/netif/lowpan6_ble.su ./Middlewares/Third_Party/lwip/src/netif/lowpan6_common.cyclo ./Middlewares/Third_Party/lwip/src/netif/lowpan6_common.d ./Middlewares/Third_Party/lwip/src/netif/lowpan6_common.o ./Middlewares/Third_Party/lwip/src/netif/lowpan6_common.su ./Middlewares/Third_Party/lwip/src/netif/slipif.cyclo ./Middlewares/Third_Party/lwip/src/netif/slipif.d ./Middlewares/Third_Party/lwip/src/netif/slipif.o ./Middlewares/Third_Party/lwip/src/netif/slipif.su ./Middlewares/Third_Party/lwip/src/netif/zepif.cyclo ./Middlewares/Third_Party/lwip/src/netif/zepif.d ./Middlewares/Third_Party/lwip/src/netif/zepif.o ./Middlewares/Third_Party/lwip/src/netif/zepif.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-netif

