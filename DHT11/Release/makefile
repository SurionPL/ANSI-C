################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MKUART/subdir.mk
-include LCD/subdir.mk
-include DHT/subdir.mk
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
DHT11.lss \

FLASH_IMAGE += \
DHT11.hex \

EEPROM_IMAGE += \
DHT11.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: DHT11.elf secondary-outputs

# Tool invocations
DHT11.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,DHT11.map -mmcu=atmega8 -o "DHT11.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

DHT11.lss: DHT11.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S DHT11.elf  >"DHT11.lss"
	@echo 'Finished building: $@'
	@echo ' '

DHT11.hex: DHT11.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex DHT11.elf  "DHT11.hex"
	@echo 'Finished building: $@'
	@echo ' '

DHT11.eep: DHT11.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex DHT11.elf  "DHT11.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: DHT11.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 DHT11.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) DHT11.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
