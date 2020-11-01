################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
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
rs485.lss \

FLASH_IMAGE += \
rs485.hex \

EEPROM_IMAGE += \
rs485.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: rs485.elf secondary-outputs

# Tool invocations
rs485.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,rs485.map -mmcu=atmega128 -o "rs485.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

rs485.lss: rs485.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S rs485.elf  >"rs485.lss"
	@echo 'Finished building: $@'
	@echo ' '

rs485.hex: rs485.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex rs485.elf  "rs485.hex"
	@echo 'Finished building: $@'
	@echo ' '

rs485.eep: rs485.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex rs485.elf  "rs485.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: rs485.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 rs485.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) rs485.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
