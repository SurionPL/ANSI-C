################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include LCD/subdir.mk
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
Termometr_int.lss \

FLASH_IMAGE += \
Termometr_int.hex \

EEPROM_IMAGE += \
Termometr_int.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Termometr_int.elf secondary-outputs

# Tool invocations
Termometr_int.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Termometr_int.map -mmcu=atmega328p -o "Termometr_int.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Termometr_int.lss: Termometr_int.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Termometr_int.elf  >"Termometr_int.lss"
	@echo 'Finished building: $@'
	@echo ' '

Termometr_int.hex: Termometr_int.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Termometr_int.elf  "Termometr_int.hex"
	@echo 'Finished building: $@'
	@echo ' '

Termometr_int.eep: Termometr_int.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Termometr_int.elf  "Termometr_int.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Termometr_int.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Termometr_int.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Termometr_int.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
