################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_prog.c \
../GIE_prog.c \
../LCD_prog.c \
../Timer0_prg.c \
../main.c 

OBJS += \
./DIO_prog.o \
./GIE_prog.o \
./LCD_prog.o \
./Timer0_prg.o \
./main.o 

C_DEPS += \
./DIO_prog.d \
./GIE_prog.d \
./LCD_prog.d \
./Timer0_prg.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


