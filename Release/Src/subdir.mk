################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ADC_Prog.c \
../Src/DS18B20.c \
../Src/GPIO_Prog.c \
../Src/PH_Prog.c \
../Src/RCC_Prog.c \
../Src/SYSTICK_Prog.c \
../Src/UART_Program.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/ADC_Prog.o \
./Src/DS18B20.o \
./Src/GPIO_Prog.o \
./Src/PH_Prog.o \
./Src/RCC_Prog.o \
./Src/SYSTICK_Prog.o \
./Src/UART_Program.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/ADC_Prog.d \
./Src/DS18B20.d \
./Src/GPIO_Prog.d \
./Src/PH_Prog.d \
./Src/RCC_Prog.d \
./Src/SYSTICK_Prog.d \
./Src/UART_Program.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/ADC_Prog.cyclo ./Src/ADC_Prog.d ./Src/ADC_Prog.o ./Src/ADC_Prog.su ./Src/DS18B20.cyclo ./Src/DS18B20.d ./Src/DS18B20.o ./Src/DS18B20.su ./Src/GPIO_Prog.cyclo ./Src/GPIO_Prog.d ./Src/GPIO_Prog.o ./Src/GPIO_Prog.su ./Src/PH_Prog.cyclo ./Src/PH_Prog.d ./Src/PH_Prog.o ./Src/PH_Prog.su ./Src/RCC_Prog.cyclo ./Src/RCC_Prog.d ./Src/RCC_Prog.o ./Src/RCC_Prog.su ./Src/SYSTICK_Prog.cyclo ./Src/SYSTICK_Prog.d ./Src/SYSTICK_Prog.o ./Src/SYSTICK_Prog.su ./Src/UART_Program.cyclo ./Src/UART_Program.d ./Src/UART_Program.o ./Src/UART_Program.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

