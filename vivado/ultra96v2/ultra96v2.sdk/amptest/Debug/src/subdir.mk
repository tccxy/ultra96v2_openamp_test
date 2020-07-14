################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/can_app.c \
../src/helper.c \
../src/platform_info.c \
../src/rsc_table.c \
../src/tcc_app.c \
../src/test.c 

OBJS += \
./src/can_app.o \
./src/helper.o \
./src/platform_info.o \
./src/rsc_table.o \
./src/tcc_app.o \
./src/test.o 

C_DEPS += \
./src/can_app.d \
./src/helper.d \
./src/platform_info.d \
./src/rsc_table.d \
./src/tcc_app.d \
./src/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM R5 gcc compiler'
	armr5-none-eabi-gcc -DARMR5 -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-r5 -I../../amptest_bsp/psu_cortexr5_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


