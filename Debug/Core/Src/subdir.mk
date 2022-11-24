################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bsp_ov7725.c \
../Core/Src/bsp_sccb.c \
../Core/Src/color_detection.c \
../Core/Src/fsmc.c \
../Core/Src/gpio.c \
../Core/Src/lcd.c \
../Core/Src/main.c \
../Core/Src/motorDriver.c \
../Core/Src/solve.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/bsp_ov7725.o \
./Core/Src/bsp_sccb.o \
./Core/Src/color_detection.o \
./Core/Src/fsmc.o \
./Core/Src/gpio.o \
./Core/Src/lcd.o \
./Core/Src/main.o \
./Core/Src/motorDriver.o \
./Core/Src/solve.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/bsp_ov7725.d \
./Core/Src/bsp_sccb.d \
./Core/Src/color_detection.d \
./Core/Src/fsmc.d \
./Core/Src/gpio.d \
./Core/Src/lcd.d \
./Core/Src/main.d \
./Core/Src/motorDriver.d \
./Core/Src/solve.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DSTM32F103xE -DUSE_HAL_DRIVER -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/bsp_ov7725.d ./Core/Src/bsp_ov7725.o ./Core/Src/bsp_ov7725.su ./Core/Src/bsp_sccb.d ./Core/Src/bsp_sccb.o ./Core/Src/bsp_sccb.su ./Core/Src/color_detection.d ./Core/Src/color_detection.o ./Core/Src/color_detection.su ./Core/Src/fsmc.d ./Core/Src/fsmc.o ./Core/Src/fsmc.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/lcd.d ./Core/Src/lcd.o ./Core/Src/lcd.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motorDriver.d ./Core/Src/motorDriver.o ./Core/Src/motorDriver.su ./Core/Src/solve.d ./Core/Src/solve.o ./Core/Src/solve.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

