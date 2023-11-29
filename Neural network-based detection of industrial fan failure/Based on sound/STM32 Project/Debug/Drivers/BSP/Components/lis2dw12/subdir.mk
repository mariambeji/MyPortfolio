################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/lis2dw12/lis2dw12.c \
../Drivers/BSP/Components/lis2dw12/lis2dw12_reg.c 

OBJS += \
./Drivers/BSP/Components/lis2dw12/lis2dw12.o \
./Drivers/BSP/Components/lis2dw12/lis2dw12_reg.o 

C_DEPS += \
./Drivers/BSP/Components/lis2dw12/lis2dw12.d \
./Drivers/BSP/Components/lis2dw12/lis2dw12_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/lis2dw12/%.o Drivers/BSP/Components/lis2dw12/%.su: ../Drivers/BSP/Components/lis2dw12/%.c Drivers/BSP/Components/lis2dw12/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/AI/Inc" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Drivers/CMSIS/DSP/Include" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Inc" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Drivers/BSP/B-L475E-IOT01" -I"C:/Users/khalil/STM32CubeIDE/workspace_1.4.0/stage2/AI2/Middlewares/ST/Audio Preprocessing/Inc" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-lis2dw12

clean-Drivers-2f-BSP-2f-Components-2f-lis2dw12:
	-$(RM) ./Drivers/BSP/Components/lis2dw12/lis2dw12.d ./Drivers/BSP/Components/lis2dw12/lis2dw12.o ./Drivers/BSP/Components/lis2dw12/lis2dw12.su ./Drivers/BSP/Components/lis2dw12/lis2dw12_reg.d ./Drivers/BSP/Components/lis2dw12/lis2dw12_reg.o ./Drivers/BSP/Components/lis2dw12/lis2dw12_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-lis2dw12

