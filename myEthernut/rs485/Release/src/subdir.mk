################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/debounce.c \
../src/main.c \
../src/myTrash.c \
../src/myUart.c \
../src/myUtil.c \
../src/nokia_lcd.c \
../src/usscalc.c 

OBJS += \
./src/debounce.o \
./src/main.o \
./src/myTrash.o \
./src/myUart.o \
./src/myUtil.o \
./src/nokia_lcd.o \
./src/usscalc.o 

C_DEPS += \
./src/debounce.d \
./src/main.d \
./src/myTrash.d \
./src/myUart.d \
./src/myUtil.d \
./src/nokia_lcd.d \
./src/usscalc.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=14745600UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


