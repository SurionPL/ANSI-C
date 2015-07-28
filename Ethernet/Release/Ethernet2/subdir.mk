################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Ethernet2/enc28j60.c \
../Ethernet2/ip_arp_udp.c \
../Ethernet2/timeout.c 

OBJS += \
./Ethernet2/enc28j60.o \
./Ethernet2/ip_arp_udp.o \
./Ethernet2/timeout.o 

C_DEPS += \
./Ethernet2/enc28j60.d \
./Ethernet2/ip_arp_udp.d \
./Ethernet2/timeout.d 


# Each subdirectory must supply rules for building sources it contributes
Ethernet2/%.o: ../Ethernet2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega88p -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


