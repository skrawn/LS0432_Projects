################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../source/sys_link.cmd 

ASM_SRCS += \
../source/dabort.asm \
../source/os_portasm.asm \
../source/pfabort.asm \
../source/sys_core.asm \
../source/sys_intvecs.asm \
../source/sys_mpu.asm \
../source/sys_pmu.asm 

C_SRCS += \
../source/Device_TMS570LS04.c \
../source/Fapi_UserDefinedFunctions.c \
../source/adc.c \
../source/can.c \
../source/crc.c \
../source/dcc.c \
../source/eqep.c \
../source/esm.c \
../source/gio.c \
../source/het.c \
../source/mibspi.c \
../source/notification.c \
../source/os_croutine.c \
../source/os_heap.c \
../source/os_list.c \
../source/os_mpu_wrappers.c \
../source/os_port.c \
../source/os_queue.c \
../source/os_tasks.c \
../source/os_timer.c \
../source/pinmux.c \
../source/sci.c \
../source/spi.c \
../source/sys_main.c \
../source/sys_pcr.c \
../source/sys_phantom.c \
../source/sys_selftest.c \
../source/sys_startup.c \
../source/sys_vim.c \
../source/system.c \
../source/ti_fee_Cfg.c \
../source/ti_fee_Info.c \
../source/ti_fee_cancel.c \
../source/ti_fee_eraseimmediateblock.c \
../source/ti_fee_format.c \
../source/ti_fee_ini.c \
../source/ti_fee_invalidateblock.c \
../source/ti_fee_main.c \
../source/ti_fee_read.c \
../source/ti_fee_readSync.c \
../source/ti_fee_shutdown.c \
../source/ti_fee_util.c \
../source/ti_fee_writeAsync.c \
../source/ti_fee_writeSync.c 

OBJS += \
./source/Device_TMS570LS04.obj \
./source/Fapi_UserDefinedFunctions.obj \
./source/adc.obj \
./source/can.obj \
./source/crc.obj \
./source/dabort.obj \
./source/dcc.obj \
./source/eqep.obj \
./source/esm.obj \
./source/gio.obj \
./source/het.obj \
./source/mibspi.obj \
./source/notification.obj \
./source/os_croutine.obj \
./source/os_heap.obj \
./source/os_list.obj \
./source/os_mpu_wrappers.obj \
./source/os_port.obj \
./source/os_portasm.obj \
./source/os_queue.obj \
./source/os_tasks.obj \
./source/os_timer.obj \
./source/pfabort.obj \
./source/pinmux.obj \
./source/sci.obj \
./source/spi.obj \
./source/sys_core.obj \
./source/sys_intvecs.obj \
./source/sys_main.obj \
./source/sys_mpu.obj \
./source/sys_pcr.obj \
./source/sys_phantom.obj \
./source/sys_pmu.obj \
./source/sys_selftest.obj \
./source/sys_startup.obj \
./source/sys_vim.obj \
./source/system.obj \
./source/ti_fee_Cfg.obj \
./source/ti_fee_Info.obj \
./source/ti_fee_cancel.obj \
./source/ti_fee_eraseimmediateblock.obj \
./source/ti_fee_format.obj \
./source/ti_fee_ini.obj \
./source/ti_fee_invalidateblock.obj \
./source/ti_fee_main.obj \
./source/ti_fee_read.obj \
./source/ti_fee_readSync.obj \
./source/ti_fee_shutdown.obj \
./source/ti_fee_util.obj \
./source/ti_fee_writeAsync.obj \
./source/ti_fee_writeSync.obj 

ASM_DEPS += \
./source/dabort.pp \
./source/os_portasm.pp \
./source/pfabort.pp \
./source/sys_core.pp \
./source/sys_intvecs.pp \
./source/sys_mpu.pp \
./source/sys_pmu.pp 

C_DEPS += \
./source/Device_TMS570LS04.pp \
./source/Fapi_UserDefinedFunctions.pp \
./source/adc.pp \
./source/can.pp \
./source/crc.pp \
./source/dcc.pp \
./source/eqep.pp \
./source/esm.pp \
./source/gio.pp \
./source/het.pp \
./source/mibspi.pp \
./source/notification.pp \
./source/os_croutine.pp \
./source/os_heap.pp \
./source/os_list.pp \
./source/os_mpu_wrappers.pp \
./source/os_port.pp \
./source/os_queue.pp \
./source/os_tasks.pp \
./source/os_timer.pp \
./source/pinmux.pp \
./source/sci.pp \
./source/spi.pp \
./source/sys_main.pp \
./source/sys_pcr.pp \
./source/sys_phantom.pp \
./source/sys_selftest.pp \
./source/sys_startup.pp \
./source/sys_vim.pp \
./source/system.pp \
./source/ti_fee_Cfg.pp \
./source/ti_fee_Info.pp \
./source/ti_fee_cancel.pp \
./source/ti_fee_eraseimmediateblock.pp \
./source/ti_fee_format.pp \
./source/ti_fee_ini.pp \
./source/ti_fee_invalidateblock.pp \
./source/ti_fee_main.pp \
./source/ti_fee_read.pp \
./source/ti_fee_readSync.pp \
./source/ti_fee_shutdown.pp \
./source/ti_fee_util.pp \
./source/ti_fee_writeAsync.pp \
./source/ti_fee_writeSync.pp 

C_DEPS__QUOTED += \
"source\Device_TMS570LS04.pp" \
"source\Fapi_UserDefinedFunctions.pp" \
"source\adc.pp" \
"source\can.pp" \
"source\crc.pp" \
"source\dcc.pp" \
"source\eqep.pp" \
"source\esm.pp" \
"source\gio.pp" \
"source\het.pp" \
"source\mibspi.pp" \
"source\notification.pp" \
"source\os_croutine.pp" \
"source\os_heap.pp" \
"source\os_list.pp" \
"source\os_mpu_wrappers.pp" \
"source\os_port.pp" \
"source\os_queue.pp" \
"source\os_tasks.pp" \
"source\os_timer.pp" \
"source\pinmux.pp" \
"source\sci.pp" \
"source\spi.pp" \
"source\sys_main.pp" \
"source\sys_pcr.pp" \
"source\sys_phantom.pp" \
"source\sys_selftest.pp" \
"source\sys_startup.pp" \
"source\sys_vim.pp" \
"source\system.pp" \
"source\ti_fee_Cfg.pp" \
"source\ti_fee_Info.pp" \
"source\ti_fee_cancel.pp" \
"source\ti_fee_eraseimmediateblock.pp" \
"source\ti_fee_format.pp" \
"source\ti_fee_ini.pp" \
"source\ti_fee_invalidateblock.pp" \
"source\ti_fee_main.pp" \
"source\ti_fee_read.pp" \
"source\ti_fee_readSync.pp" \
"source\ti_fee_shutdown.pp" \
"source\ti_fee_util.pp" \
"source\ti_fee_writeAsync.pp" \
"source\ti_fee_writeSync.pp" 

OBJS__QUOTED += \
"source\Device_TMS570LS04.obj" \
"source\Fapi_UserDefinedFunctions.obj" \
"source\adc.obj" \
"source\can.obj" \
"source\crc.obj" \
"source\dabort.obj" \
"source\dcc.obj" \
"source\eqep.obj" \
"source\esm.obj" \
"source\gio.obj" \
"source\het.obj" \
"source\mibspi.obj" \
"source\notification.obj" \
"source\os_croutine.obj" \
"source\os_heap.obj" \
"source\os_list.obj" \
"source\os_mpu_wrappers.obj" \
"source\os_port.obj" \
"source\os_portasm.obj" \
"source\os_queue.obj" \
"source\os_tasks.obj" \
"source\os_timer.obj" \
"source\pfabort.obj" \
"source\pinmux.obj" \
"source\sci.obj" \
"source\spi.obj" \
"source\sys_core.obj" \
"source\sys_intvecs.obj" \
"source\sys_main.obj" \
"source\sys_mpu.obj" \
"source\sys_pcr.obj" \
"source\sys_phantom.obj" \
"source\sys_pmu.obj" \
"source\sys_selftest.obj" \
"source\sys_startup.obj" \
"source\sys_vim.obj" \
"source\system.obj" \
"source\ti_fee_Cfg.obj" \
"source\ti_fee_Info.obj" \
"source\ti_fee_cancel.obj" \
"source\ti_fee_eraseimmediateblock.obj" \
"source\ti_fee_format.obj" \
"source\ti_fee_ini.obj" \
"source\ti_fee_invalidateblock.obj" \
"source\ti_fee_main.obj" \
"source\ti_fee_read.obj" \
"source\ti_fee_readSync.obj" \
"source\ti_fee_shutdown.obj" \
"source\ti_fee_util.obj" \
"source\ti_fee_writeAsync.obj" \
"source\ti_fee_writeSync.obj" 

ASM_DEPS__QUOTED += \
"source\dabort.pp" \
"source\os_portasm.pp" \
"source\pfabort.pp" \
"source\sys_core.pp" \
"source\sys_intvecs.pp" \
"source\sys_mpu.pp" \
"source\sys_pmu.pp" 

C_SRCS__QUOTED += \
"../source/Device_TMS570LS04.c" \
"../source/Fapi_UserDefinedFunctions.c" \
"../source/adc.c" \
"../source/can.c" \
"../source/crc.c" \
"../source/dcc.c" \
"../source/eqep.c" \
"../source/esm.c" \
"../source/gio.c" \
"../source/het.c" \
"../source/mibspi.c" \
"../source/notification.c" \
"../source/os_croutine.c" \
"../source/os_heap.c" \
"../source/os_list.c" \
"../source/os_mpu_wrappers.c" \
"../source/os_port.c" \
"../source/os_queue.c" \
"../source/os_tasks.c" \
"../source/os_timer.c" \
"../source/pinmux.c" \
"../source/sci.c" \
"../source/spi.c" \
"../source/sys_main.c" \
"../source/sys_pcr.c" \
"../source/sys_phantom.c" \
"../source/sys_selftest.c" \
"../source/sys_startup.c" \
"../source/sys_vim.c" \
"../source/system.c" \
"../source/ti_fee_Cfg.c" \
"../source/ti_fee_Info.c" \
"../source/ti_fee_cancel.c" \
"../source/ti_fee_eraseimmediateblock.c" \
"../source/ti_fee_format.c" \
"../source/ti_fee_ini.c" \
"../source/ti_fee_invalidateblock.c" \
"../source/ti_fee_main.c" \
"../source/ti_fee_read.c" \
"../source/ti_fee_readSync.c" \
"../source/ti_fee_shutdown.c" \
"../source/ti_fee_util.c" \
"../source/ti_fee_writeAsync.c" \
"../source/ti_fee_writeSync.c" 

ASM_SRCS__QUOTED += \
"../source/dabort.asm" \
"../source/os_portasm.asm" \
"../source/pfabort.asm" \
"../source/sys_core.asm" \
"../source/sys_intvecs.asm" \
"../source/sys_mpu.asm" \
"../source/sys_pmu.asm" 


