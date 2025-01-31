################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/src/api/api_lib.c \
../Middlewares/Third_Party/lwip/src/api/api_msg.c \
../Middlewares/Third_Party/lwip/src/api/err.c \
../Middlewares/Third_Party/lwip/src/api/if_api.c \
../Middlewares/Third_Party/lwip/src/api/netbuf.c \
../Middlewares/Third_Party/lwip/src/api/netdb.c \
../Middlewares/Third_Party/lwip/src/api/netifapi.c \
../Middlewares/Third_Party/lwip/src/api/sockets.c \
../Middlewares/Third_Party/lwip/src/api/tcpip.c 

OBJS += \
./Middlewares/Third_Party/lwip/src/api/api_lib.o \
./Middlewares/Third_Party/lwip/src/api/api_msg.o \
./Middlewares/Third_Party/lwip/src/api/err.o \
./Middlewares/Third_Party/lwip/src/api/if_api.o \
./Middlewares/Third_Party/lwip/src/api/netbuf.o \
./Middlewares/Third_Party/lwip/src/api/netdb.o \
./Middlewares/Third_Party/lwip/src/api/netifapi.o \
./Middlewares/Third_Party/lwip/src/api/sockets.o \
./Middlewares/Third_Party/lwip/src/api/tcpip.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/src/api/api_lib.d \
./Middlewares/Third_Party/lwip/src/api/api_msg.d \
./Middlewares/Third_Party/lwip/src/api/err.d \
./Middlewares/Third_Party/lwip/src/api/if_api.d \
./Middlewares/Third_Party/lwip/src/api/netbuf.d \
./Middlewares/Third_Party/lwip/src/api/netdb.d \
./Middlewares/Third_Party/lwip/src/api/netifapi.d \
./Middlewares/Third_Party/lwip/src/api/sockets.d \
./Middlewares/Third_Party/lwip/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/src/api/%.o Middlewares/Third_Party/lwip/src/api/%.su Middlewares/Third_Party/lwip/src/api/%.cyclo: ../Middlewares/Third_Party/lwip/src/api/%.c Middlewares/Third_Party/lwip/src/api/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -DTFT96 -c -I"C:/Dev/st/projects/Stm32h743Wifi/Core/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/App" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/Target" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/hw" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/ST7735" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/W25QXX" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Rtc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Misc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Gpio" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Pwm" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FatFs/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/control" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/data" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/netif" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/network" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/serial" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/spi" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/host_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Core/lwip" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/protobuf-c" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/lwip/contrib/ports/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-api

clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-api:
	-$(RM) ./Middlewares/Third_Party/lwip/src/api/api_lib.cyclo ./Middlewares/Third_Party/lwip/src/api/api_lib.d ./Middlewares/Third_Party/lwip/src/api/api_lib.o ./Middlewares/Third_Party/lwip/src/api/api_lib.su ./Middlewares/Third_Party/lwip/src/api/api_msg.cyclo ./Middlewares/Third_Party/lwip/src/api/api_msg.d ./Middlewares/Third_Party/lwip/src/api/api_msg.o ./Middlewares/Third_Party/lwip/src/api/api_msg.su ./Middlewares/Third_Party/lwip/src/api/err.cyclo ./Middlewares/Third_Party/lwip/src/api/err.d ./Middlewares/Third_Party/lwip/src/api/err.o ./Middlewares/Third_Party/lwip/src/api/err.su ./Middlewares/Third_Party/lwip/src/api/if_api.cyclo ./Middlewares/Third_Party/lwip/src/api/if_api.d ./Middlewares/Third_Party/lwip/src/api/if_api.o ./Middlewares/Third_Party/lwip/src/api/if_api.su ./Middlewares/Third_Party/lwip/src/api/netbuf.cyclo ./Middlewares/Third_Party/lwip/src/api/netbuf.d ./Middlewares/Third_Party/lwip/src/api/netbuf.o ./Middlewares/Third_Party/lwip/src/api/netbuf.su ./Middlewares/Third_Party/lwip/src/api/netdb.cyclo ./Middlewares/Third_Party/lwip/src/api/netdb.d ./Middlewares/Third_Party/lwip/src/api/netdb.o ./Middlewares/Third_Party/lwip/src/api/netdb.su ./Middlewares/Third_Party/lwip/src/api/netifapi.cyclo ./Middlewares/Third_Party/lwip/src/api/netifapi.d ./Middlewares/Third_Party/lwip/src/api/netifapi.o ./Middlewares/Third_Party/lwip/src/api/netifapi.su ./Middlewares/Third_Party/lwip/src/api/sockets.cyclo ./Middlewares/Third_Party/lwip/src/api/sockets.d ./Middlewares/Third_Party/lwip/src/api/sockets.o ./Middlewares/Third_Party/lwip/src/api/sockets.su ./Middlewares/Third_Party/lwip/src/api/tcpip.cyclo ./Middlewares/Third_Party/lwip/src/api/tcpip.d ./Middlewares/Third_Party/lwip/src/api/tcpip.o ./Middlewares/Third_Party/lwip/src/api/tcpip.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-api

