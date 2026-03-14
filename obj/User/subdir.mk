################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/adc_read.c \
../User/ch32v00x_it.c \
../User/font6x8.c \
../User/main.c \
../User/pwm_write.c \
../User/st7567.c \
../User/system_ch32v00x.c 

C_DEPS += \
./User/adc_read.d \
./User/ch32v00x_it.d \
./User/font6x8.d \
./User/main.d \
./User/pwm_write.d \
./User/st7567.d \
./User/system_ch32v00x.d 

OBJS += \
./User/adc_read.o \
./User/ch32v00x_it.o \
./User/font6x8.o \
./User/main.o \
./User/pwm_write.o \
./User/st7567.o \
./User/system_ch32v00x.o 

DIR_OBJS += \
./User/*.o \

DIR_DEPS += \
./User/*.d \

DIR_EXPANDS += \
./User/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/chami/mounriver-studio-projects/CH32V003F4P_PWM_with_ADC/Debug" -I"c:/Users/chami/mounriver-studio-projects/CH32V003F4P_PWM_with_ADC/Core" -I"c:/Users/chami/mounriver-studio-projects/CH32V003F4P_PWM_with_ADC/User" -I"c:/Users/chami/mounriver-studio-projects/CH32V003F4P_PWM_with_ADC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

