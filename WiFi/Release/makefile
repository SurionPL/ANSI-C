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
WiFi.lss \

FLASH_IMAGE += \
WiFi.hex \

EEPROM_IMAGE += \
WiFi.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: WiFi.elf secondary-outputs

# Tool invocations
WiFi.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,WiFi.map -mmcu=atmega8 -o "WiFi.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

WiFi.lss: WiFi.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S WiFi.elf  >"WiFi.lss"
	@echo 'Finished building: $@'
	@echo ' '

WiFi.hex: WiFi.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex WiFi.elf  "WiFi.hex"
	@echo 'Finished building: $@'
	@echo ' '

WiFi.eep: WiFi.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex WiFi.elf  "WiFi.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: WiFi.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 WiFi.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) WiFi.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
