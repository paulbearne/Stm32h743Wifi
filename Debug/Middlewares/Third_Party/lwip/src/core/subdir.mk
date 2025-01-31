################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/src/core/altcp.c \
../Middlewares/Third_Party/lwip/src/core/altcp_alloc.c \
../Middlewares/Third_Party/lwip/src/core/altcp_tcp.c \
../Middlewares/Third_Party/lwip/src/core/def.c \
../Middlewares/Third_Party/lwip/src/core/dns.c \
../Middlewares/Third_Party/lwip/src/core/inet_chksum.c \
../Middlewares/Third_Party/lwip/src/core/init.c \
../Middlewares/Third_Party/lwip/src/core/ip.c \
../Middlewares/Third_Party/lwip/src/core/mem.c \
../Middlewares/Third_Party/lwip/src/core/memp.c \
../Middlewares/Third_Party/lwip/src/core/netif.c \
../Middlewares/Third_Party/lwip/src/core/pbuf.c \
../Middlewares/Third_Party/lwip/src/core/raw.c \
../Middlewares/Third_Party/lwip/src/core/stats.c \
../Middlewares/Third_Party/lwip/src/core/sys.c \
../Middlewares/Third_Party/lwip/src/core/tcp.c \
../Middlewares/Third_Party/lwip/src/core/tcp_in.c \
../Middlewares/Third_Party/lwip/src/core/tcp_out.c \
../Middlewares/Third_Party/lwip/src/core/timeouts.c \
../Middlewares/Third_Party/lwip/src/core/udp.c 

OBJS += \
./Middlewares/Third_Party/lwip/src/core/altcp.o \
./Middlewares/Third_Party/lwip/src/core/altcp_alloc.o \
./Middlewares/Third_Party/lwip/src/core/altcp_tcp.o \
./Middlewares/Third_Party/lwip/src/core/def.o \
./Middlewares/Third_Party/lwip/src/core/dns.o \
./Middlewares/Third_Party/lwip/src/core/inet_chksum.o \
./Middlewares/Third_Party/lwip/src/core/init.o \
./Middlewares/Third_Party/lwip/src/core/ip.o \
./Middlewares/Third_Party/lwip/src/core/mem.o \
./Middlewares/Third_Party/lwip/src/core/memp.o \
./Middlewares/Third_Party/lwip/src/core/netif.o \
./Middlewares/Third_Party/lwip/src/core/pbuf.o \
./Middlewares/Third_Party/lwip/src/core/raw.o \
./Middlewares/Third_Party/lwip/src/core/stats.o \
./Middlewares/Third_Party/lwip/src/core/sys.o \
./Middlewares/Third_Party/lwip/src/core/tcp.o \
./Middlewares/Third_Party/lwip/src/core/tcp_in.o \
./Middlewares/Third_Party/lwip/src/core/tcp_out.o \
./Middlewares/Third_Party/lwip/src/core/timeouts.o \
./Middlewares/Third_Party/lwip/src/core/udp.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/src/core/altcp.d \
./Middlewares/Third_Party/lwip/src/core/altcp_alloc.d \
./Middlewares/Third_Party/lwip/src/core/altcp_tcp.d \
./Middlewares/Third_Party/lwip/src/core/def.d \
./Middlewares/Third_Party/lwip/src/core/dns.d \
./Middlewares/Third_Party/lwip/src/core/inet_chksum.d \
./Middlewares/Third_Party/lwip/src/core/init.d \
./Middlewares/Third_Party/lwip/src/core/ip.d \
./Middlewares/Third_Party/lwip/src/core/mem.d \
./Middlewares/Third_Party/lwip/src/core/memp.d \
./Middlewares/Third_Party/lwip/src/core/netif.d \
./Middlewares/Third_Party/lwip/src/core/pbuf.d \
./Middlewares/Third_Party/lwip/src/core/raw.d \
./Middlewares/Third_Party/lwip/src/core/stats.d \
./Middlewares/Third_Party/lwip/src/core/sys.d \
./Middlewares/Third_Party/lwip/src/core/tcp.d \
./Middlewares/Third_Party/lwip/src/core/tcp_in.d \
./Middlewares/Third_Party/lwip/src/core/tcp_out.d \
./Middlewares/Third_Party/lwip/src/core/timeouts.d \
./Middlewares/Third_Party/lwip/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/src/core/%.o Middlewares/Third_Party/lwip/src/core/%.su Middlewares/Third_Party/lwip/src/core/%.cyclo: ../Middlewares/Third_Party/lwip/src/core/%.c Middlewares/Third_Party/lwip/src/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -DTFT96 -c -I"C:/Dev/st/projects/Stm32h743Wifi/Core/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/App" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/Target" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/hw" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/ST7735" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/W25QXX" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Rtc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Misc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Gpio" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Pwm" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FatFs/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/control" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/data" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/netif" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/network" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/serial" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/spi" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/host_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Core/lwip" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/protobuf-c" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/lwip/contrib/ports/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core

clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core:
	-$(RM) ./Middlewares/Third_Party/lwip/src/core/altcp.cyclo ./Middlewares/Third_Party/lwip/src/core/altcp.d ./Middlewares/Third_Party/lwip/src/core/altcp.o ./Middlewares/Third_Party/lwip/src/core/altcp.su ./Middlewares/Third_Party/lwip/src/core/altcp_alloc.cyclo ./Middlewares/Third_Party/lwip/src/core/altcp_alloc.d ./Middlewares/Third_Party/lwip/src/core/altcp_alloc.o ./Middlewares/Third_Party/lwip/src/core/altcp_alloc.su ./Middlewares/Third_Party/lwip/src/core/altcp_tcp.cyclo ./Middlewares/Third_Party/lwip/src/core/altcp_tcp.d ./Middlewares/Third_Party/lwip/src/core/altcp_tcp.o ./Middlewares/Third_Party/lwip/src/core/altcp_tcp.su ./Middlewares/Third_Party/lwip/src/core/def.cyclo ./Middlewares/Third_Party/lwip/src/core/def.d ./Middlewares/Third_Party/lwip/src/core/def.o ./Middlewares/Third_Party/lwip/src/core/def.su ./Middlewares/Third_Party/lwip/src/core/dns.cyclo ./Middlewares/Third_Party/lwip/src/core/dns.d ./Middlewares/Third_Party/lwip/src/core/dns.o ./Middlewares/Third_Party/lwip/src/core/dns.su ./Middlewares/Third_Party/lwip/src/core/inet_chksum.cyclo ./Middlewares/Third_Party/lwip/src/core/inet_chksum.d ./Middlewares/Third_Party/lwip/src/core/inet_chksum.o ./Middlewares/Third_Party/lwip/src/core/inet_chksum.su ./Middlewares/Third_Party/lwip/src/core/init.cyclo ./Middlewares/Third_Party/lwip/src/core/init.d ./Middlewares/Third_Party/lwip/src/core/init.o ./Middlewares/Third_Party/lwip/src/core/init.su ./Middlewares/Third_Party/lwip/src/core/ip.cyclo ./Middlewares/Third_Party/lwip/src/core/ip.d ./Middlewares/Third_Party/lwip/src/core/ip.o ./Middlewares/Third_Party/lwip/src/core/ip.su ./Middlewares/Third_Party/lwip/src/core/mem.cyclo ./Middlewares/Third_Party/lwip/src/core/mem.d ./Middlewares/Third_Party/lwip/src/core/mem.o ./Middlewares/Third_Party/lwip/src/core/mem.su ./Middlewares/Third_Party/lwip/src/core/memp.cyclo ./Middlewares/Third_Party/lwip/src/core/memp.d ./Middlewares/Third_Party/lwip/src/core/memp.o ./Middlewares/Third_Party/lwip/src/core/memp.su ./Middlewares/Third_Party/lwip/src/core/netif.cyclo ./Middlewares/Third_Party/lwip/src/core/netif.d ./Middlewares/Third_Party/lwip/src/core/netif.o ./Middlewares/Third_Party/lwip/src/core/netif.su ./Middlewares/Third_Party/lwip/src/core/pbuf.cyclo ./Middlewares/Third_Party/lwip/src/core/pbuf.d ./Middlewares/Third_Party/lwip/src/core/pbuf.o ./Middlewares/Third_Party/lwip/src/core/pbuf.su ./Middlewares/Third_Party/lwip/src/core/raw.cyclo ./Middlewares/Third_Party/lwip/src/core/raw.d ./Middlewares/Third_Party/lwip/src/core/raw.o ./Middlewares/Third_Party/lwip/src/core/raw.su ./Middlewares/Third_Party/lwip/src/core/stats.cyclo ./Middlewares/Third_Party/lwip/src/core/stats.d ./Middlewares/Third_Party/lwip/src/core/stats.o ./Middlewares/Third_Party/lwip/src/core/stats.su ./Middlewares/Third_Party/lwip/src/core/sys.cyclo ./Middlewares/Third_Party/lwip/src/core/sys.d ./Middlewares/Third_Party/lwip/src/core/sys.o ./Middlewares/Third_Party/lwip/src/core/sys.su ./Middlewares/Third_Party/lwip/src/core/tcp.cyclo ./Middlewares/Third_Party/lwip/src/core/tcp.d ./Middlewares/Third_Party/lwip/src/core/tcp.o ./Middlewares/Third_Party/lwip/src/core/tcp.su ./Middlewares/Third_Party/lwip/src/core/tcp_in.cyclo ./Middlewares/Third_Party/lwip/src/core/tcp_in.d ./Middlewares/Third_Party/lwip/src/core/tcp_in.o ./Middlewares/Third_Party/lwip/src/core/tcp_in.su ./Middlewares/Third_Party/lwip/src/core/tcp_out.cyclo ./Middlewares/Third_Party/lwip/src/core/tcp_out.d ./Middlewares/Third_Party/lwip/src/core/tcp_out.o ./Middlewares/Third_Party/lwip/src/core/tcp_out.su ./Middlewares/Third_Party/lwip/src/core/timeouts.cyclo ./Middlewares/Third_Party/lwip/src/core/timeouts.d ./Middlewares/Third_Party/lwip/src/core/timeouts.o ./Middlewares/Third_Party/lwip/src/core/timeouts.su ./Middlewares/Third_Party/lwip/src/core/udp.cyclo ./Middlewares/Third_Party/lwip/src/core/udp.d ./Middlewares/Third_Party/lwip/src/core/udp.o ./Middlewares/Third_Party/lwip/src/core/udp.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-core

