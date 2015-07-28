################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Ethernet/enc28j60.c \
../Ethernet/ip_arp_udp_tcp.c 

OBJS += \
./Ethernet/enc28j60.o \
./Ethernet/ip_arp_udp_tcp.o 

C_DEPS += \
./Ethernet/enc28j60.d \
./Ethernet/ip_arp_udp_tcp.d 


# Each subdirectory must supply rules for building sources it contributes
Ethernet/%.o: ../Ethernet/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


