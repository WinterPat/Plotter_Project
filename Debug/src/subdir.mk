################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Main.cpp 

OBJS += \
./src/Main.o 

CPP_DEPS += \
./src/Main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"D:\Githubin jutut\Plotter_Project\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\lpc_board_nxp_lpcxpresso_1549\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\lpc_chip_15xx\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\FreeRTOS\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\FreeRTOS\src\include" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\FreeRTOS\src\portable\GCC\ARM_CM3" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\lpc_chip_15xx\inc\usbd" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


