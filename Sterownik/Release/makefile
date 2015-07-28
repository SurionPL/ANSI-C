################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Ethernet/subdir.mk
-include 1Wire/subdir.mk
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
Sterownik.lss \

FLASH_IMAGE += \
Sterownik.hex \

EEPROM_IMAGE += \
Sterownik.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Sterownik.elf secondary-outputs

# Tool invocations
Sterownik.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Sterownik.map -mmcu=atmega328p -o "Sterownik.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Sterownik.lss: Sterownik.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Sterownik.elf  >"Sterownik.lss"
	@echo 'Finished building: $@'
	@echo ' '

Sterownik.hex: Sterownik.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Sterownik.elf  "Sterownik.hex"
	@echo 'Finished building: $@'
	@echo ' '

Sterownik.eep: Sterownik.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Sterownik.elf  "Sterownik.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Sterownik.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Sterownik.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Sterownik.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
