################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP_Control.c \
../BUZZER.c \
../PWM.c \
../Timer_1.c \
../UART.c \
../external_eeprom.c \
../gpio.c \
../motor.c \
../twi.c 

OBJS += \
./APP_Control.o \
./BUZZER.o \
./PWM.o \
./Timer_1.o \
./UART.o \
./external_eeprom.o \
./gpio.o \
./motor.o \
./twi.o 

C_DEPS += \
./APP_Control.d \
./BUZZER.d \
./PWM.d \
./Timer_1.d \
./UART.d \
./external_eeprom.d \
./gpio.d \
./motor.d \
./twi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


