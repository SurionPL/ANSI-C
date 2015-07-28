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
Seminarka.lss \

FLASH_IMAGE += \
Seminarka.hex \

EEPROM_IMAGE += \
Seminarka.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Seminarka.elf secondary-outputs

# Tool invocations
Seminarka.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Seminarka.map -mmcu=atmega328p -o "Seminarka.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Seminarka.lss: Seminarka.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Seminarka.elf  >"Seminarka.lss"
	@echo 'Finished building: $@'
	@echo ' '

Seminarka.hex: Seminarka.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Seminarka.elf  "Seminarka.hex"
	@echo 'Finished building: $@'
	@echo ' '

Seminarka.eep: Seminarka.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Seminarka.elf  "Seminarka.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Seminarka.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Seminarka.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Seminarka.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
