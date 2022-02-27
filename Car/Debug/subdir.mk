################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DC_Motor.c \
../DIO.c \
../Gpt.c \
../Gpt_Lcfg.c \
../LCD.c \
../Pwm.c \
../Pwm_Lcfg.c \
../main.c 

OBJS += \
./DC_Motor.o \
./DIO.o \
./Gpt.o \
./Gpt_Lcfg.o \
./LCD.o \
./Pwm.o \
./Pwm_Lcfg.o \
./main.o 

C_DEPS += \
./DC_Motor.d \
./DIO.d \
./Gpt.d \
./Gpt_Lcfg.d \
./LCD.d \
./Pwm.d \
./Pwm_Lcfg.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


