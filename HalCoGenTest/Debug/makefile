################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccsv6/tools/compiler/arm_5.1.7

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./source/ti_fee_writeSync.obj" \
"./source/ti_fee_writeAsync.obj" \
"./source/ti_fee_util.obj" \
"./source/ti_fee_shutdown.obj" \
"./source/ti_fee_readSync.obj" \
"./source/ti_fee_read.obj" \
"./source/ti_fee_main.obj" \
"./source/ti_fee_invalidateblock.obj" \
"./source/ti_fee_ini.obj" \
"./source/ti_fee_format.obj" \
"./source/ti_fee_eraseimmediateblock.obj" \
"./source/ti_fee_cancel.obj" \
"./source/ti_fee_Info.obj" \
"./source/ti_fee_Cfg.obj" \
"./source/system.obj" \
"./source/sys_vim.obj" \
"./source/sys_startup.obj" \
"./source/sys_selftest.obj" \
"./source/sys_pmu.obj" \
"./source/sys_phantom.obj" \
"./source/sys_pcr.obj" \
"./source/sys_mpu.obj" \
"./source/sys_main.obj" \
"./source/sys_intvecs.obj" \
"./source/sys_core.obj" \
"./source/spi.obj" \
"./source/sci.obj" \
"./source/pinmux.obj" \
"./source/pfabort.obj" \
"./source/os_timer.obj" \
"./source/os_tasks.obj" \
"./source/os_queue.obj" \
"./source/os_portasm.obj" \
"./source/os_port.obj" \
"./source/os_mpu_wrappers.obj" \
"./source/os_list.obj" \
"./source/os_heap.obj" \
"./source/os_croutine.obj" \
"./source/notification.obj" \
"./source/mibspi.obj" \
"./source/het.obj" \
"./source/gio.obj" \
"./source/esm.obj" \
"./source/eqep.obj" \
"./source/dcc.obj" \
"./source/dabort.obj" \
"./source/crc.obj" \
"./source/can.obj" \
"./source/adc.obj" \
"./source/Fapi_UserDefinedFunctions.obj" \
"./source/Device_TMS570LS04.obj" \
"../source/sys_link.cmd" \
"../include/F021/F021_API_CortexR4_BE.lib" \
-l"rtsv7R4_T_be_eabi.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include source/subdir_vars.mk
-include include/F021/subdir_vars.mk
-include source/subdir_rules.mk
-include include/F021/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
HalCoGenTest.out \

EXE_OUTPUTS__QUOTED += \
"HalCoGenTest.out" \

BIN_OUTPUTS += \
HalCoGenTest.hex \

BIN_OUTPUTS__QUOTED += \
"HalCoGenTest.hex" \


# All Target
all: HalCoGenTest.out

# Tool invocations
HalCoGenTest.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"D:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armcl" -mv7R4 --code_state=32 --abi=eabi -g --display_error_number --diag_warning=225 --diag_wrap=off --enum_type=packed -z -m"HalCoGenTest.map" --heap_size=0x800 --stack_size=0x800 -i"D:/ti/ccsv6/tools/compiler/arm_5.1.7/lib" -i"D:/ti/ccsv6/tools/compiler/arm_5.1.7/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="HalCoGenTest_linkInfo.xml" --rom_model --be32 -o "HalCoGenTest.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

HalCoGenTest.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"D:/ti/ccsv6/tools/compiler/arm_5.1.7/bin/armhex"  -o "HalCoGenTest.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "source\Device_TMS570LS04.pp" "source\Fapi_UserDefinedFunctions.pp" "source\adc.pp" "source\can.pp" "source\crc.pp" "source\dcc.pp" "source\eqep.pp" "source\esm.pp" "source\gio.pp" "source\het.pp" "source\mibspi.pp" "source\notification.pp" "source\os_croutine.pp" "source\os_heap.pp" "source\os_list.pp" "source\os_mpu_wrappers.pp" "source\os_port.pp" "source\os_queue.pp" "source\os_tasks.pp" "source\os_timer.pp" "source\pinmux.pp" "source\sci.pp" "source\spi.pp" "source\sys_main.pp" "source\sys_pcr.pp" "source\sys_phantom.pp" "source\sys_selftest.pp" "source\sys_startup.pp" "source\sys_vim.pp" "source\system.pp" "source\ti_fee_Cfg.pp" "source\ti_fee_Info.pp" "source\ti_fee_cancel.pp" "source\ti_fee_eraseimmediateblock.pp" "source\ti_fee_format.pp" "source\ti_fee_ini.pp" "source\ti_fee_invalidateblock.pp" "source\ti_fee_main.pp" "source\ti_fee_read.pp" "source\ti_fee_readSync.pp" "source\ti_fee_shutdown.pp" "source\ti_fee_util.pp" "source\ti_fee_writeAsync.pp" "source\ti_fee_writeSync.pp" 
	-$(RM) "source\Device_TMS570LS04.obj" "source\Fapi_UserDefinedFunctions.obj" "source\adc.obj" "source\can.obj" "source\crc.obj" "source\dabort.obj" "source\dcc.obj" "source\eqep.obj" "source\esm.obj" "source\gio.obj" "source\het.obj" "source\mibspi.obj" "source\notification.obj" "source\os_croutine.obj" "source\os_heap.obj" "source\os_list.obj" "source\os_mpu_wrappers.obj" "source\os_port.obj" "source\os_portasm.obj" "source\os_queue.obj" "source\os_tasks.obj" "source\os_timer.obj" "source\pfabort.obj" "source\pinmux.obj" "source\sci.obj" "source\spi.obj" "source\sys_core.obj" "source\sys_intvecs.obj" "source\sys_main.obj" "source\sys_mpu.obj" "source\sys_pcr.obj" "source\sys_phantom.obj" "source\sys_pmu.obj" "source\sys_selftest.obj" "source\sys_startup.obj" "source\sys_vim.obj" "source\system.obj" "source\ti_fee_Cfg.obj" "source\ti_fee_Info.obj" "source\ti_fee_cancel.obj" "source\ti_fee_eraseimmediateblock.obj" "source\ti_fee_format.obj" "source\ti_fee_ini.obj" "source\ti_fee_invalidateblock.obj" 
	-$(RM) "source\ti_fee_main.obj" "source\ti_fee_read.obj" "source\ti_fee_readSync.obj" "source\ti_fee_shutdown.obj" "source\ti_fee_util.obj" "source\ti_fee_writeAsync.obj" "source\ti_fee_writeSync.obj" 
	-$(RM) "source\dabort.pp" "source\os_portasm.pp" "source\pfabort.pp" "source\sys_core.pp" "source\sys_intvecs.pp" "source\sys_mpu.pp" "source\sys_pmu.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

