################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include X-CUBE-AI/App/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Drivers/Components/wm8994/subdir.mk
-include Drivers/Components/stmpe811/subdir.mk
-include Drivers/Components/stmpe1600/subdir.mk
-include Drivers/Components/st7789h2/subdir.mk
-include Drivers/Components/st7735/subdir.mk
-include Drivers/Components/st25dv/subdir.mk
-include Drivers/Components/ov9655/subdir.mk
-include Drivers/Components/mfxstm32l152/subdir.mk
-include Drivers/Components/m24sr/subdir.mk
-include Drivers/Components/lsm6dsl/subdir.mk
-include Drivers/Components/lsm303dlhc/subdir.mk
-include Drivers/Components/lsm303c/subdir.mk
-include Drivers/Components/ls016b8uy/subdir.mk
-include Drivers/Components/lps22hb/subdir.mk
-include Drivers/Components/lis3mdl/subdir.mk
-include Drivers/Components/l3gd20/subdir.mk
-include Drivers/Components/hx8347i/subdir.mk
-include Drivers/Components/hx8347g/subdir.mk
-include Drivers/Components/hts221/subdir.mk
-include Drivers/Components/ft6x06/subdir.mk
-include Drivers/Components/ft5336/subdir.mk
-include Drivers/Components/ft3x67/subdir.mk
-include Drivers/Components/cy8c4014lqi/subdir.mk
-include Drivers/Components/cs43l22/subdir.mk
-include Drivers/Components/cs42l51/subdir.mk
-include Drivers/B-L475E-IOT01/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := IMU_Sensor_Fusion
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
IMU_Sensor_Fusion.elf \

MAP_FILES += \
IMU_Sensor_Fusion.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
IMU_Sensor_Fusion.list \


# All Target
all: main-build

# Main-build Target
main-build: IMU_Sensor_Fusion.elf secondary-outputs

# Tool invocations
IMU_Sensor_Fusion.elf IMU_Sensor_Fusion.map: $(OBJS) $(USER_OBJS) C:\Users\khalil\STM32CubeIDE\workspace_1.4.0\PFA\IMU_Sensor_Fusion\STM32L475VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "IMU_Sensor_Fusion.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\khalil\STM32CubeIDE\workspace_1.4.0\PFA\IMU_Sensor_Fusion\STM32L475VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="IMU_Sensor_Fusion.map" -Wl,--gc-sections -static -L../Middlewares/ST/AI/Lib --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

IMU_Sensor_Fusion.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "IMU_Sensor_Fusion.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) IMU_Sensor_Fusion.elf IMU_Sensor_Fusion.list IMU_Sensor_Fusion.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
