################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include LCD/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
1Wire.lss \

FLASH_IMAGE += \
1Wire.hex \

EEPROM_IMAGE += \
1Wire.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 1Wire.elf secondary-outputs

# Tool invocations
1Wire.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,1Wire.map -mmcu=atmega8 -o "1Wire.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

1Wire.lss: 1Wire.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 1Wire.elf  >"1Wire.lss"
	@echo 'Finished building: $@'
	@echo ' '

1Wire.hex: 1Wire.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex 1Wire.elf  "1Wire.hex"
	@echo 'Finished building: $@'
	@echo ' '

1Wire.eep: 1Wire.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 1Wire.elf  "1Wire.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 1Wire.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 1Wire.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 1Wire.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
