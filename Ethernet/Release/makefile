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
Ethernet.lss \

FLASH_IMAGE += \
Ethernet.hex \

EEPROM_IMAGE += \
Ethernet.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Ethernet.elf secondary-outputs

# Tool invocations
Ethernet.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Ethernet.map -mmcu=atmega328p -o "Ethernet.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Ethernet.lss: Ethernet.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Ethernet.elf  >"Ethernet.lss"
	@echo 'Finished building: $@'
	@echo ' '

Ethernet.hex: Ethernet.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Ethernet.elf  "Ethernet.hex"
	@echo 'Finished building: $@'
	@echo ' '

Ethernet.eep: Ethernet.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Ethernet.elf  "Ethernet.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Ethernet.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Ethernet.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Ethernet.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
