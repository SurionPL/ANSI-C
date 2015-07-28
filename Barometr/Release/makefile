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
Barometr.lss \

FLASH_IMAGE += \
Barometr.hex \

EEPROM_IMAGE += \
Barometr.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Barometr.elf secondary-outputs

# Tool invocations
Barometr.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Barometr.map -mmcu=atmega8 -o "Barometr.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Barometr.lss: Barometr.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Barometr.elf  >"Barometr.lss"
	@echo 'Finished building: $@'
	@echo ' '

Barometr.hex: Barometr.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Barometr.elf  "Barometr.hex"
	@echo 'Finished building: $@'
	@echo ' '

Barometr.eep: Barometr.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Barometr.elf  "Barometr.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Barometr.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 Barometr.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Barometr.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
