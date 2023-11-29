################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01.c \
../Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_audio.c \
../Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_bus.c \
../Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_env_sensors.c \
../Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_motion_sensors.c 

OBJS += \
./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01.o \
./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_audio.o \
./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_bus.o \
./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_env_sensors.o \
./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_motion_sensors.o 

C_DEPS += \
./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01.d \
./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_audio.d \
./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_bus.d \
./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_env_sensors.d \
./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_motion_sensors.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/B-L475E-IOT01/%.o Drivers/BSP/B-L475E-IOT01/%.su: ../Drivers/BSP/B-L475E-IOT01/%.c Drivers/BSP/B-L475E-IOT01/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/AI/Inc" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Drivers/CMSIS/DSP/Include" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Drivers/BSP/B-L475E-IOT01" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/Audio Preprocessing/Inc" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-B-2d-L475E-2d-IOT01

clean-Drivers-2f-BSP-2f-B-2d-L475E-2d-IOT01:
	-$(RM) ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01.d ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01.o ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01.su ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_audio.d ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_audio.o ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_audio.su ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_bus.d ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_bus.o ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_bus.su ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_env_sensors.d ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_env_sensors.o ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_env_sensors.su ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_motion_sensors.d ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_motion_sensors.o ./Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_motion_sensors.su

.PHONY: clean-Drivers-2f-BSP-2f-B-2d-L475E-2d-IOT01

