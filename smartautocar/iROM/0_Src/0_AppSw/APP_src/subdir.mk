################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../0_Src/0_AppSw/APP_src/QspiDemo.c \
../0_Src/0_AppSw/APP_src/Sensor.c \
../0_Src/0_AppSw/APP_src/TLF35584Demo.c \
../0_Src/0_AppSw/APP_src/Test_Adc.c \
../0_Src/0_AppSw/APP_src/Test_Camera.c \
../0_Src/0_AppSw/APP_src/Test_Dio.c \
../0_Src/0_AppSw/APP_src/Test_Encoder.c \
../0_Src/0_AppSw/APP_src/Test_Icu.c \
../0_Src/0_AppSw/APP_src/Test_ModuleInit.c \
../0_Src/0_AppSw/APP_src/Test_Pwm.c \
../0_Src/0_AppSw/APP_src/Test_Uart.c 

OBJS += \
./0_Src/0_AppSw/APP_src/QspiDemo.o \
./0_Src/0_AppSw/APP_src/Sensor.o \
./0_Src/0_AppSw/APP_src/TLF35584Demo.o \
./0_Src/0_AppSw/APP_src/Test_Adc.o \
./0_Src/0_AppSw/APP_src/Test_Camera.o \
./0_Src/0_AppSw/APP_src/Test_Dio.o \
./0_Src/0_AppSw/APP_src/Test_Encoder.o \
./0_Src/0_AppSw/APP_src/Test_Icu.o \
./0_Src/0_AppSw/APP_src/Test_ModuleInit.o \
./0_Src/0_AppSw/APP_src/Test_Pwm.o \
./0_Src/0_AppSw/APP_src/Test_Uart.o 

C_DEPS += \
./0_Src/0_AppSw/APP_src/QspiDemo.d \
./0_Src/0_AppSw/APP_src/Sensor.d \
./0_Src/0_AppSw/APP_src/TLF35584Demo.d \
./0_Src/0_AppSw/APP_src/Test_Adc.d \
./0_Src/0_AppSw/APP_src/Test_Camera.d \
./0_Src/0_AppSw/APP_src/Test_Dio.d \
./0_Src/0_AppSw/APP_src/Test_Encoder.d \
./0_Src/0_AppSw/APP_src/Test_Icu.d \
./0_Src/0_AppSw/APP_src/Test_ModuleInit.d \
./0_Src/0_AppSw/APP_src/Test_Pwm.d \
./0_Src/0_AppSw/APP_src/Test_Uart.d 


# Each subdirectory must supply rules for building sources it contributes
0_Src/0_AppSw/APP_src/%.o: ../0_Src/0_AppSw/APP_src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -IC:/Users/kimwayne/HanyangUniv_Project/TC237L_DemoPack_HanyangUniv/h -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Qspi\SpiMaster" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Multican" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Multican\Can" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Multican\Std" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\_Impl" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\_Lib\DataHandling" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\_Lib\InternalMux" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\_PinMap" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Asclin\Asc" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Asclin\Lin" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Asclin\Spi" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Asclin\Std" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Cpu\CStart" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Cpu\Irq" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Cpu\Std" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Cpu\Trap" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Dma\Dma" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Dma\Std" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Gtm\Std" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Gtm\Tom" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Gtm\Trig" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Port\Io" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Port\Std" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Scu\Std" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Src\Std" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Stm\Std" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Vadc\Adc" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\Vadc\Std" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore\_Reg" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\1_SrvSw\Config\Common" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\1_SrvSw" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\1_SrvSw\Tricore\Compilers" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\0_AppSw\APP_inc" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\1_SrvSw\_Utilities" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\1_SrvSw\Config" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\1_SrvSw\If" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\1_SrvSw\StdIf" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\1_SrvSw\SysSe" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\1_SrvSw\Tricore" -I"C:\Users\kdh95\Desktop\liunx\Erica\smartcar\TC237L_DemoPack_HanyangUniv\0_Src\4_McHal\Tricore" -fno-common -Os -g3 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -DAPPKIT_TC237TFT -fshort-double -mcpu=tc23xx -mversion-info -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


