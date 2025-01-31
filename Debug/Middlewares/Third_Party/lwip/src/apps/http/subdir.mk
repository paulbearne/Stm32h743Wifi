################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/lwip/src/apps/http/altcp_proxyconnect.c \
../Middlewares/Third_Party/lwip/src/apps/http/fs.c \
../Middlewares/Third_Party/lwip/src/apps/http/http_client.c \
../Middlewares/Third_Party/lwip/src/apps/http/httpd.c 

OBJS += \
./Middlewares/Third_Party/lwip/src/apps/http/altcp_proxyconnect.o \
./Middlewares/Third_Party/lwip/src/apps/http/fs.o \
./Middlewares/Third_Party/lwip/src/apps/http/http_client.o \
./Middlewares/Third_Party/lwip/src/apps/http/httpd.o 

C_DEPS += \
./Middlewares/Third_Party/lwip/src/apps/http/altcp_proxyconnect.d \
./Middlewares/Third_Party/lwip/src/apps/http/fs.d \
./Middlewares/Third_Party/lwip/src/apps/http/http_client.d \
./Middlewares/Third_Party/lwip/src/apps/http/httpd.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/lwip/src/apps/http/%.o Middlewares/Third_Party/lwip/src/apps/http/%.su Middlewares/Third_Party/lwip/src/apps/http/%.cyclo: ../Middlewares/Third_Party/lwip/src/apps/http/%.c Middlewares/Third_Party/lwip/src/apps/http/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -DTFT96 -c -I"C:/Dev/st/projects/Stm32h743Wifi/Core/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/App" -I"C:/Dev/st/projects/Stm32h743Wifi/FATFS/Target" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/tinyusb/hw" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/ST7735" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/W25QXX" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Rtc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Misc" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Gpio" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/BSP/Pwm" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FatFs/src" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Dev/st/projects/Stm32h743Wifi/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/control" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app/data" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/app" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/netif" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/network" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/serial" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver/spi" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/host_common/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Core/lwip" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common" -I"C:/Dev/st/projects/Stm32h743Wifi/Wifi/driver_common/protobuf-c" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/lwip/src/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/lwip/contrib/ports/freertos/include" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/lwip/contrib/ports/cmsis/arch" -I"C:/Dev/st/projects/Stm32h743Wifi/Middlewares/Third_Party/lwip/contrib/ports/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-apps-2f-http

clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-apps-2f-http:
	-$(RM) ./Middlewares/Third_Party/lwip/src/apps/http/altcp_proxyconnect.cyclo ./Middlewares/Third_Party/lwip/src/apps/http/altcp_proxyconnect.d ./Middlewares/Third_Party/lwip/src/apps/http/altcp_proxyconnect.o ./Middlewares/Third_Party/lwip/src/apps/http/altcp_proxyconnect.su ./Middlewares/Third_Party/lwip/src/apps/http/fs.cyclo ./Middlewares/Third_Party/lwip/src/apps/http/fs.d ./Middlewares/Third_Party/lwip/src/apps/http/fs.o ./Middlewares/Third_Party/lwip/src/apps/http/fs.su ./Middlewares/Third_Party/lwip/src/apps/http/http_client.cyclo ./Middlewares/Third_Party/lwip/src/apps/http/http_client.d ./Middlewares/Third_Party/lwip/src/apps/http/http_client.o ./Middlewares/Third_Party/lwip/src/apps/http/http_client.su ./Middlewares/Third_Party/lwip/src/apps/http/httpd.cyclo ./Middlewares/Third_Party/lwip/src/apps/http/httpd.d ./Middlewares/Third_Party/lwip/src/apps/http/httpd.o ./Middlewares/Third_Party/lwip/src/apps/http/httpd.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-lwip-2f-src-2f-apps-2f-http

