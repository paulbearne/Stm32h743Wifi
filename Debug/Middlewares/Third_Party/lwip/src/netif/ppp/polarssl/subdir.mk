################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/arc4.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/des.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md4.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md5.c \
../Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/sha1.c 

OBJS += \
./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/arc4.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/des.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md4.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md5.o \
./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/sha1.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/arc4.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/des.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md4.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md5.d \
./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/sha1.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/%.o Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/%.su Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/%.cyclo: ../Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/%.c Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -DTFT96 -c -I"C:/Dev/st/projects/Stm32h743Wifi/Core/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/App" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/Target" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/hw" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/ST7735" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/W25QXX" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Rtc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Misc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Gpio" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Pwm" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FatFs/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/control" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/data" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/netif" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/network" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/serial" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/spi" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/host_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Core/lwip" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/protobuf-c" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/lwip/contrib/ports/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-netif-2f-ppp-2f-polarssl

clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-netif-2f-ppp-2f-polarssl:
	-$(RM) ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/arc4.cyclo ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/arc4.d ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/arc4.o ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/arc4.su ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/des.cyclo ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/des.d ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/des.o ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/des.su ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md4.cyclo ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md4.d ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md4.o ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md4.su ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md5.cyclo ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md5.d ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md5.o ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/md5.su ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/sha1.cyclo ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/sha1.d ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/sha1.o ./Middlewares/Third_Party/lwip/src/netif/ppp/polarssl/sha1.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-netif-2f-ppp-2f-polarssl

