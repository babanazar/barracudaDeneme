################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/SEGGER_RTT/subdir.mk
-include src/subdir.mk
-include ra_gen/subdir.mk
-include ra/fsp/src/r_wdt/subdir.mk
-include ra/fsp/src/r_sci_uart/subdir.mk
-include ra/fsp/src/r_rtc/subdir.mk
-include ra/fsp/src/r_iwdt/subdir.mk
-include ra/fsp/src/r_ioport/subdir.mk
-include ra/fsp/src/r_gpt/subdir.mk
-include ra/fsp/src/r_dtc/subdir.mk
-include ra/fsp/src/r_dmac/subdir.mk
-include ra/fsp/src/r_cgc/subdir.mk
-include ra/fsp/src/r_agt/subdir.mk
-include ra/fsp/src/r_adc/subdir.mk
-include ra/fsp/src/bsp/mcu/ra2l1/subdir.mk
-include ra/fsp/src/bsp/mcu/all/subdir.mk
-include ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
barracudaDeneme0.hex \

SECONDARY_SIZE += \
barracudaDeneme0.siz \


# All Target
all: barracudaDeneme0.elf secondary-outputs

# Tool invocations
barracudaDeneme0.elf: $(OBJS) $(USER_OBJS) $(LINKER_SCRIPT)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m23 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -T "fsp.ld" -Xlinker --gc-sections -L "C:\\e2_studio\\marti\\barracudaDeneme0/script" -Wl,-Map,"barracudaDeneme0.map" --specs=nano.specs --specs=rdimon.specs -o "barracudaDeneme0.elf" -Wl,--start-group $(OBJS) $(USER_OBJS) $(LIBS) -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

barracudaDeneme0.hex: barracudaDeneme0.elf
	@echo 'Invoking: GNU ARM Cross Create Flash Image'
	arm-none-eabi-objcopy -O ihex "barracudaDeneme0.elf"  "barracudaDeneme0.hex"
	@echo 'Finished building: $@'
	@echo ' '

barracudaDeneme0.siz: barracudaDeneme0.elf
	@echo 'Invoking: GNU ARM Cross Print Size'
	arm-none-eabi-size --format=berkeley "barracudaDeneme0.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SRC_DEPS)$(JMP_DEPS)$(PP_DEPS)$(SX_DEPS)$(FSY_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(P_DEPS)$(C_DEPS) barracudaDeneme0.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
