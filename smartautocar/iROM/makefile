################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include 0_Src/4_McHal/Tricore/_PinMap/subdir.mk
-include 0_Src/4_McHal/Tricore/_Lib/InternalMux/subdir.mk
-include 0_Src/4_McHal/Tricore/_Lib/DataHandling/subdir.mk
-include 0_Src/4_McHal/Tricore/_Impl/subdir.mk
-include 0_Src/4_McHal/Tricore/Vadc/Std/subdir.mk
-include 0_Src/4_McHal/Tricore/Vadc/Adc/subdir.mk
-include 0_Src/4_McHal/Tricore/Stm/Std/subdir.mk
-include 0_Src/4_McHal/Tricore/Src/Std/subdir.mk
-include 0_Src/4_McHal/Tricore/Scu/Std/subdir.mk
-include 0_Src/4_McHal/Tricore/Qspi/Std/subdir.mk
-include 0_Src/4_McHal/Tricore/Qspi/SpiSlave/subdir.mk
-include 0_Src/4_McHal/Tricore/Qspi/SpiMaster/subdir.mk
-include 0_Src/4_McHal/Tricore/Port/Std/subdir.mk
-include 0_Src/4_McHal/Tricore/Port/Io/subdir.mk
-include 0_Src/4_McHal/Tricore/Multican/Std/subdir.mk
-include 0_Src/4_McHal/Tricore/Multican/Can/subdir.mk
-include 0_Src/4_McHal/Tricore/Gtm/Trig/subdir.mk
-include 0_Src/4_McHal/Tricore/Gtm/Tom/Timer/subdir.mk
-include 0_Src/4_McHal/Tricore/Gtm/Tom/PwmHl/subdir.mk
-include 0_Src/4_McHal/Tricore/Gtm/Tom/Pwm/subdir.mk
-include 0_Src/4_McHal/Tricore/Gtm/Std/subdir.mk
-include 0_Src/4_McHal/Tricore/Dma/Std/subdir.mk
-include 0_Src/4_McHal/Tricore/Dma/Dma/subdir.mk
-include 0_Src/4_McHal/Tricore/Cpu/Trap/subdir.mk
-include 0_Src/4_McHal/Tricore/Cpu/Std/subdir.mk
-include 0_Src/4_McHal/Tricore/Cpu/Irq/subdir.mk
-include 0_Src/4_McHal/Tricore/Cpu/CStart/subdir.mk
-include 0_Src/4_McHal/Tricore/Asclin/Std/subdir.mk
-include 0_Src/4_McHal/Tricore/Asclin/Spi/subdir.mk
-include 0_Src/4_McHal/Tricore/Asclin/Lin/subdir.mk
-include 0_Src/4_McHal/Tricore/Asclin/Asc/subdir.mk
-include 0_Src/1_SrvSw/Tricore/Compilers/subdir.mk
-include 0_Src/1_SrvSw/SysSe/Time/subdir.mk
-include 0_Src/1_SrvSw/SysSe/Math/subdir.mk
-include 0_Src/1_SrvSw/SysSe/General/subdir.mk
-include 0_Src/1_SrvSw/SysSe/Comm/subdir.mk
-include 0_Src/1_SrvSw/SysSe/Bsp/subdir.mk
-include 0_Src/1_SrvSw/StdIf/subdir.mk
-include 0_Src/1_SrvSw/If/subdir.mk
-include 0_Src/1_SrvSw/Config/Common/subdir.mk
-include 0_Src/0_AppSw/Main/subdir.mk
-include 0_Src/0_AppSw/APP_src/subdir.mk
-include .metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

#rebuild target
rebuild: clean all

# All Target
all: TC237L_DemoPack_HanyangUniv.elf

# Tool invocations
TC237L_DemoPack_HanyangUniv.elf: $(OBJS) $(USER_OBJS) $(ASM)
	@echo 'Building target: $@'
	@echo 'Invoking: TriCore C Linker'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -o  "TC237L_DemoPack_HanyangUniv.elf" -T"../Lcf_Gnuc.ld" ".metadata\.plugins\org.eclipse.cdt.make.core\specs.o" "0_Src\0_AppSw\APP_src\QspiDemo.o" "0_Src\0_AppSw\APP_src\Sensor.o" "0_Src\0_AppSw\APP_src\TLF35584Demo.o" "0_Src\0_AppSw\APP_src\Test_Adc.o" "0_Src\0_AppSw\APP_src\Test_Camera.o" "0_Src\0_AppSw\APP_src\Test_Dio.o" "0_Src\0_AppSw\APP_src\Test_Encoder.o" "0_Src\0_AppSw\APP_src\Test_Icu.o" "0_Src\0_AppSw\APP_src\Test_ModuleInit.o" "0_Src\0_AppSw\APP_src\Test_Pwm.o" "0_Src\0_AppSw\APP_src\Test_Uart.o" "0_Src\0_AppSw\Main\Cpu0_Main.o" "0_Src\1_SrvSw\Config\Common\Ifx_InterfaceConst.o" "0_Src\1_SrvSw\If\SpiIf.o" "0_Src\1_SrvSw\StdIf\IfxStdIf_DPipe.o" "0_Src\1_SrvSw\StdIf\IfxStdIf_Pos.o" "0_Src\1_SrvSw\StdIf\IfxStdIf_PwmHl.o" "0_Src\1_SrvSw\StdIf\IfxStdIf_Timer.o" "0_Src\1_SrvSw\SysSe\Bsp\Assert.o" "0_Src\1_SrvSw\SysSe\Bsp\Bsp.o" "0_Src\1_SrvSw\SysSe\Comm\Ifx_Console.o" "0_Src\1_SrvSw\SysSe\Comm\Ifx_Shell.o" "0_Src\1_SrvSw\SysSe\General\Ifx_GlobalResources.o" "0_Src\1_SrvSw\SysSe\Math\Ifx_LowPassPt1.o" "0_Src\1_SrvSw\SysSe\Time\Ifx_DateTime.o" "0_Src\1_SrvSw\Tricore\Compilers\CompilerGnuc.o" "0_Src\4_McHal\Tricore\Asclin\Asc\IfxAsclin_Asc.o" "0_Src\4_McHal\Tricore\Asclin\Lin\IfxAsclin_Lin.o" "0_Src\4_McHal\Tricore\Asclin\Spi\IfxAsclin_Spi.o" "0_Src\4_McHal\Tricore\Asclin\Std\IfxAsclin.o" "0_Src\4_McHal\Tricore\Cpu\CStart\IfxCpu_CStart0.o" "0_Src\4_McHal\Tricore\Cpu\Irq\IfxCpu_Irq.o" "0_Src\4_McHal\Tricore\Cpu\Std\IfxCpu.o" "0_Src\4_McHal\Tricore\Cpu\Trap\IfxCpu_Trap.o" "0_Src\4_McHal\Tricore\Dma\Dma\IfxDma_Dma.o" "0_Src\4_McHal\Tricore\Dma\Std\IfxDma.o" "0_Src\4_McHal\Tricore\Gtm\Std\IfxGtm.o" "0_Src\4_McHal\Tricore\Gtm\Std\IfxGtm_Cmu.o" "0_Src\4_McHal\Tricore\Gtm\Std\IfxGtm_Dpll.o" "0_Src\4_McHal\Tricore\Gtm\Std\IfxGtm_Tbu.o" "0_Src\4_McHal\Tricore\Gtm\Std\IfxGtm_Tim.o" "0_Src\4_McHal\Tricore\Gtm\Std\IfxGtm_Tom.o" "0_Src\4_McHal\Tricore\Gtm\Tom\Pwm\IfxGtm_Tom_Pwm.o" "0_Src\4_McHal\Tricore\Gtm\Tom\PwmHl\IfxGtm_Tom_PwmHl.o" "0_Src\4_McHal\Tricore\Gtm\Tom\Timer\IfxGtm_Tom_Timer.o" "0_Src\4_McHal\Tricore\Gtm\Trig\IfxGtm_Trig.o" "0_Src\4_McHal\Tricore\Multican\Can\IfxMultican_Can.o" "0_Src\4_McHal\Tricore\Multican\Std\IfxMultican.o" "0_Src\4_McHal\Tricore\Port\Io\IfxPort_Io.o" "0_Src\4_McHal\Tricore\Port\Std\IfxPort.o" "0_Src\4_McHal\Tricore\Qspi\SpiMaster\IfxQspi_SpiMaster.o" "0_Src\4_McHal\Tricore\Qspi\SpiSlave\IfxQspi_SpiSlave.o" "0_Src\4_McHal\Tricore\Qspi\Std\IfxQspi.o" "0_Src\4_McHal\Tricore\Scu\Std\IfxScuCcu.o" "0_Src\4_McHal\Tricore\Scu\Std\IfxScuEru.o" "0_Src\4_McHal\Tricore\Scu\Std\IfxScuWdt.o" "0_Src\4_McHal\Tricore\Src\Std\IfxSrc.o" "0_Src\4_McHal\Tricore\Stm\Std\IfxStm.o" "0_Src\4_McHal\Tricore\Vadc\Adc\IfxVadc_Adc.o" "0_Src\4_McHal\Tricore\Vadc\Std\IfxVadc.o" "0_Src\4_McHal\Tricore\_Impl\IfxCcu6_cfg.o" "0_Src\4_McHal\Tricore\_Impl\IfxCpu_cfg.o" "0_Src\4_McHal\Tricore\_Impl\IfxDma_cfg.o" "0_Src\4_McHal\Tricore\_Impl\IfxFlash_cfg.o" "0_Src\4_McHal\Tricore\_Impl\IfxMtu_cfg.o" "0_Src\4_McHal\Tricore\_Impl\IfxMultican_cfg.o" "0_Src\4_McHal\Tricore\_Impl\IfxPort_cfg.o" "0_Src\4_McHal\Tricore\_Impl\IfxScu_cfg.o" "0_Src\4_McHal\Tricore\_Impl\IfxSent_cfg.o" "0_Src\4_McHal\Tricore\_Impl\IfxSrc_cfg.o" "0_Src\4_McHal\Tricore\_Impl\IfxStm_cfg.o" "0_Src\4_McHal\Tricore\_Impl\IfxVadc_cfg.o" "0_Src\4_McHal\Tricore\_Lib\DataHandling\Ifx_CircularBuffer.asm.o" "0_Src\4_McHal\Tricore\_Lib\DataHandling\Ifx_CircularBuffer.o" "0_Src\4_McHal\Tricore\_Lib\DataHandling\Ifx_Fifo.o" "0_Src\4_McHal\Tricore\_Lib\InternalMux\Ifx_InternalMux.o" "0_Src\4_McHal\Tricore\_PinMap\IfxAsclin_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxCcu6_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxEray_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxEth_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxGpt12_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxGtm_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxMultican_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxPort_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxQspi_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxScu_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxSent_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxSmu_PinMap.o" "0_Src\4_McHal\Tricore\_PinMap\IfxVadc_PinMap.o" -Wl,--gc-sections -mcpu=tc23xx -Wl,--mem-holes -Wl,--no-warn-flags -Wl,-Map="$(basename $(notdir $@)).map" -Wl,--cref -fshort-double -Wl,--extmap="a"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(PCP_S)$(EXECUTABLES)$(OBJS)$(C_DEPS)$(CPCP_DEPS) TC237L_DemoPack_HanyangUniv.elf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
