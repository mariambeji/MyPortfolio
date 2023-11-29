################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/common_tables.c \
../Core/Src/dct.c \
../Core/Src/es_wifi.c \
../Core/Src/es_wifi_io.c \
../Core/Src/feature_extraction.c \
../Core/Src/main.c \
../Core/Src/mel_filterbank.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/wifi.c \
../Core/Src/window.c 

OBJS += \
./Core/Src/common_tables.o \
./Core/Src/dct.o \
./Core/Src/es_wifi.o \
./Core/Src/es_wifi_io.o \
./Core/Src/feature_extraction.o \
./Core/Src/main.o \
./Core/Src/mel_filterbank.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/wifi.o \
./Core/Src/window.o 

C_DEPS += \
./Core/Src/common_tables.d \
./Core/Src/dct.d \
./Core/Src/es_wifi.d \
./Core/Src/es_wifi_io.d \
./Core/Src/feature_extraction.d \
./Core/Src/main.d \
./Core/Src/mel_filterbank.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/wifi.d \
./Core/Src/window.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/AI/Inc" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Drivers/CMSIS/DSP/Include" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Drivers/BSP/B-L475E-IOT01" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/Audio Preprocessing/Inc" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/common_tables.d ./Core/Src/common_tables.o ./Core/Src/common_tables.su ./Core/Src/dct.d ./Core/Src/dct.o ./Core/Src/dct.su ./Core/Src/es_wifi.d ./Core/Src/es_wifi.o ./Core/Src/es_wifi.su ./Core/Src/es_wifi_io.d ./Core/Src/es_wifi_io.o ./Core/Src/es_wifi_io.su ./Core/Src/feature_extraction.d ./Core/Src/feature_extraction.o ./Core/Src/feature_extraction.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mel_filterbank.d ./Core/Src/mel_filterbank.o ./Core/Src/mel_filterbank.su ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su ./Core/Src/wifi.d ./Core/Src/wifi.o ./Core/Src/wifi.su ./Core/Src/window.d ./Core/Src/window.o ./Core/Src/window.su

.PHONY: clean-Core-2f-Src

