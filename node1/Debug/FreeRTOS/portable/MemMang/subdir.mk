################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./FreeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./FreeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/MemMang/%.o FreeRTOS/portable/MemMang/%.su FreeRTOS/portable/MemMang/%.cyclo: ../FreeRTOS/portable/MemMang/%.c FreeRTOS/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"C:/Users/Alexis/STM32CubeIDE/workspace_2.1.1/PROJECT_5_CAN_BMS1/node1/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/Alexis/STM32CubeIDE/workspace_2.1.1/PROJECT_5_CAN_BMS1/node1/FreeRTOS" -I"C:/Users/Alexis/STM32CubeIDE/workspace_2.1.1/PROJECT_5_CAN_BMS1/node1/FreeRTOS/portable" -I"C:/Users/Alexis/STM32CubeIDE/workspace_2.1.1/PROJECT_5_CAN_BMS1/node1/FreeRTOS/Include" -I"C:/Users/Alexis/STM32CubeIDE/workspace_2.1.1/PROJECT_5_CAN_BMS1/node1/FreeRTOS/portable/MemMang" -I"C:/Users/Alexis/STM32CubeIDE/workspace_2.1.1/PROJECT_5_CAN_BMS1/node1/FreeRTOS/portable/GCC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2f-portable-2f-MemMang

clean-FreeRTOS-2f-portable-2f-MemMang:
	-$(RM) ./FreeRTOS/portable/MemMang/heap_4.cyclo ./FreeRTOS/portable/MemMang/heap_4.d ./FreeRTOS/portable/MemMang/heap_4.o ./FreeRTOS/portable/MemMang/heap_4.su

.PHONY: clean-FreeRTOS-2f-portable-2f-MemMang

