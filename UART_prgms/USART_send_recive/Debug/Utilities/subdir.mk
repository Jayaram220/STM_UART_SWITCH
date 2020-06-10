################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/stm32f0308_discovery.c 

OBJS += \
./Utilities/stm32f0308_discovery.o 

C_DEPS += \
./Utilities/stm32f0308_discovery.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/%.o: ../Utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F0 -DSTM32F030R8Tx -DSTM32F0308_DISCO -DDEBUG -DSTM32F030 -DUSE_STDPERIPH_DRIVER -I"C:/Users/Devsys3/workspace/USART_send_recive/Utilities" -I"C:/Users/Devsys3/workspace/USART_send_recive/StdPeriph_Driver/inc" -I"C:/Users/Devsys3/workspace/USART_send_recive/inc" -I"C:/Users/Devsys3/workspace/USART_send_recive/CMSIS/device" -I"C:/Users/Devsys3/workspace/USART_send_recive/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


