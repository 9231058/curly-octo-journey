################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AddressUtility.c \
../GetAddrInfo.c \
../Practical.c 

OBJS += \
./AddressUtility.o \
./GetAddrInfo.o \
./Practical.o 

C_DEPS += \
./AddressUtility.d \
./GetAddrInfo.d \
./Practical.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


