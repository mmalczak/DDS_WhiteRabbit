################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/axi_to_wb.c \
../src/spi_general.c \
../src/spi_mine.c 

OBJS += \
./src/axi_to_wb.o \
./src/spi_general.o \
./src/spi_mine.o 

C_DEPS += \
./src/axi_to_wb.d \
./src/spi_general.d \
./src/spi_mine.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -I/home/milosz/Desktop/Xilinx/Vivado/projects/AXI_TO_WISHBONE_edit_slave/sf/axi_to_wb/include -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../axi_to_wb_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


