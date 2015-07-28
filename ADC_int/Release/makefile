################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
ADC_int.lss \

FLASH_IMAGE += \
ADC_int.hex \

EEPROM_IMAGE += \
ADC_int.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ADC_int.elf secondary-outputs

# Tool invocations
ADC_int.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ADC_int.map -mmcu=atmega328p -o "ADC_int.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ADC_int.lss: ADC_int.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ADC_int.elf  >"ADC_int.lss"
	@echo 'Finished building: $@'
	@echo ' '

ADC_int.hex: ADC_int.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex ADC_int.elf  "ADC_int.hex"
	@echo 'Finished building: $@'
	@echo ' '

ADC_int.eep: ADC_int.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ADC_int.elf  "ADC_int.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ADC_int.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p ADC_int.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ADC_int.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
