;/*
;    FreeRTOS V7.4.0 - Copyright (C) 2013 Real Time Engineers Ltd.
;	
;
;    ***************************************************************************
;     *                                                                       *
;     *    FreeRTOS tutorial books are available in pdf and paperback.        *
;     *    Complete, revised, and edited pdf reference manuals are also       *
;     *    available.                                                         *
;     *                                                                       *
;     *    Purchasing FreeRTOS documentation will not only help you, by       *
;     *    ensuring you get running as quickly as possible and with an        *
;     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
;     *    the FreeRTOS project to continue with its mission of providing     *
;     *    professional grade, cross platform, de facto standard solutions    *
;     *    for microcontrollers - completely free of charge!                  *
;     *                                                                       *
;     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
;     *                                                                       *
;     *    Thank you for using FreeRTOS, and thank you for your support!      *
;     *                                                                       *
;    ***************************************************************************
;
;
;    This file is part of the FreeRTOS distribution.
;
;    FreeRTOS is free software; you can redistribute it and/or modify it under
;    the terms of the GNU General Public License (version 2) as published by the
;    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
;    >>>NOTE<<< The modification to the GPL is included to allow you to
;    distribute a combined work that includes FreeRTOS without being obliged to
;    provide the source code for proprietary components outside of the FreeRTOS
;    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
;    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
;    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
;    more details. You should have received a copy of the GNU General Public
;    License and the FreeRTOS license exception along with FreeRTOS; if not it
;    can be viewed here: http://www.freertos.org/a00114.html and also obtained
;    by writing to Richard Barry, contact details for whom are available on the
;    FreeRTOS WEB site.
;
;    1 tab == 4 spaces!
;
;    http://www.FreeRTOS.org - Documentation, latest information, license and
;    contact details.
;
;    http://www.SafeRTOS.com - A version that is certified for use in safety
;    critical systems.
;
;    http://www.OpenRTOS.com - Commercial support, development, porting,
;    licensing and training services.
;*/

		.sect ".kernelTEXT"
		.arm
        .ref   vTaskSwitchContext
        .ref   vTaskIncrementTick
        .ref   ulTaskHasFPUContext
		.ref   pxCurrentTCB
		.ref   ulCriticalNesting;

;/*-----------------------------------------------------------*/
;
; Save Task Context 
;
portSAVE_CONTEXT .macro

		DSB

		; Push R0 as we are going to use it
		STMDB	SP!, {R0}

		; Set R0 to point to the task stack pointer.
		STMDB	SP,{SP}^
		SUB	SP, SP, #4
		LDMIA	SP!,{R0}

		; Push the return address onto the stack.
		STMDB	R0!, {LR}

		; Now LR has been saved, it can be used instead of R0.
		MOV	LR, R0

		; Pop R0 so it can be saved onto the task stack.
		LDMIA	SP!, {R0}

		; Push all the system mode registers onto the task stack.
		STMDB	LR,{R0-LR}^
		SUB	LR, LR, #60

		; Push the SPSR onto the task stack.
		MRS	R0, SPSR
		STMDB	LR!, {R0}


		; Store the new top of stack for the task.
		LDR	R0, pxCurrentTCBConst
		LDR	R0, [R0]
		STR	LR, [R0]

        .endm

;/*-----------------------------------------------------------*/
;
; Restore Task Context
;
portRESTORE_CONTEXT .macro

		LDR		R0, pxCurrentTCBConst
		LDR		R0, [R0]

		; task stack MPU region
        mov		r4,  #4						; Task Stack Region
        add		r12, r0, #4				    ; poin to regions in TCB
        ldmia   r12!, {r1-r3}
        mcr     p15, #0, r4, c6, c2, #0     ; Select region
        mcr     p15, #0, r1, c6, c1, #0		; Base Address
        mcr     p15, #0, r3, c6, c1, #4		; Access Attributes
        mcr     p15, #0, r2, c6, c1, #2		; Size and Enable

		ldr		r5, portMax_MPU_Region
		mov		r4,  #5
		; dynamic MPU per task
		ldmia   r12!, {r1-r3}
        mcr     p15, #0, r4, c6, c2, #0     ; Select region
        mcr     p15, #0, r1, c6, c1, #0		; Base Address
        mcr     p15, #0, r3, c6, c1, #4		; Access Attributes
        mcr     p15, #0, r2, c6, c1, #2		; Size and Enable
		add     r4, r4, #1
	    cmp     r4, r5
		bne     $ - 0x1C

		LDR		LR, [R0]


		; Get the SPSR from the stack.
		LDMFD	LR!, {R0}
		MSR		SPSR_CSXF, R0

		; Restore all system mode registers for the task.
		LDMFD	LR, {R0-R14}^

		; Restore the return address.
		LDR		LR, [LR, #+60]
		DSB

		; And return - correcting the offset in the LR to obtain the
		; correct address.
		SUBS	PC, LR, #4

        .endm

portMax_MPU_Region	     .word   8 - 1

;/*-----------------------------------------------------------*/
; Start the first task by restoring its context.

        .def vPortStartFirstTask
        .asmfunc
vPortStartFirstTask
        cps #0x13
        portRESTORE_CONTEXT
        .endasmfunc
;/*-----------------------------------------------------------*/
; Yield to another task.

        .def vPortYieldProcessor
        .asmfunc
swiPortYield
		;  Restore stack and LR before calling vPortYieldProcessor
		ldmfd	sp!, {r12,lr}

vPortYieldProcessor
		; Within an IRQ ISR the link register has an offset from the true return
		; address.  SWI doesn't do this. Add the offset manually so the ISR
		; return code can be used.
        ADD     LR, LR, #4

        ; First save the context of the current task.
        portSAVE_CONTEXT

        ; Select the next task to execute. */
        BL      vTaskSwitchContext

        ; Restore the context of the task selected to execute.
        portRESTORE_CONTEXT
        .endasmfunc
		
;/*-----------------------------------------------------------*/
; Yield to another task from within the FreeRTOS API

		.def vPortYeildWithinAPI
        .asmfunc
vPortYeildWithinAPI
		; Save the context of the current task.

        portSAVE_CONTEXT
		; Clear SSI flag.
		MOVW    R0, #0xFFF4
		MOVT 	R0, #0xFFFF
		LDR     R0, [R0]

		; Select the next task to execute. */
        BL      vTaskSwitchContext

        ; Restore the context of the task selected to execute.
        portRESTORE_CONTEXT
        .endasmfunc
		
;/*-----------------------------------------------------------*/
; Preemptive Tick

        .def vPortPreemptiveTick
        .asmfunc
vPortPreemptiveTick

		; Save the context of the current task.
        portSAVE_CONTEXT

        ; Clear interrupt flag
        MOVW    R0, #0xFC88
        MOVT    R0, #0xFFFF
        MOV     R1, #1
        STR     R1, [R0]

        ; Increment the tick count, making any adjustments to the blocked lists
        ; that may be necessary.
        BL      vTaskIncrementTick

        ; Select the next task to execute.
        BL      vTaskSwitchContext

        ; Restore the context of the task selected to execute.
        portRESTORE_CONTEXT
        .endasmfunc
;-------------------------------------------------------------------------------

		.def ulPortCountLeadingZeros
        .asmfunc
ulPortCountLeadingZeros

		CLZ		R0, R0
		BX		LR
        .endasmfunc
;-------------------------------------------------------------------------------
; SWI Handler, interface to Protected Mode Functions

		.def    vPortSWI
        .asmfunc
vPortSWI
		stmfd   sp!, {r12,lr}
		ldrb	r12, [lr, #-1]
		ldr		r14,  table
		ldr     r12, [r14, r12, lsl #2]
		blx     r12
		ldmfd   sp!, {r12,pc}^

table
		.word	jumpTable

jumpTable
		.word	swiPortYield				 ; 0 - vPortYieldProcessor
		.word   swiRaisePrivilege   		 ; 1 - Raise Priviledge
		.word   swiPortEnterCritical         ; 2 - vPortEnterCritical
		.word   swiPortExitCritical          ; 3 - vPortExitCritical
		.word   swiPortTaskUsesFPU			 ; 4 - vPortTaskUsesFPU
		.word	swiPortDisableInterrupts	 ; 5 - vPortDisableInterrupts
		.word	swiPortEnableInterrupts 	 ; 6 - vPortEnableInterrupts
        .endasmfunc
;-------------------------------------------------------------------------------
; swiPortDisableInterrupts
        .asmfunc
swiPortDisableInterrupts
		mrs     r0, SPSR
		orr     r0, r0, #0x80
		msr     SPSR_c, r0
		bx		r14
        .endasmfunc
;-------------------------------------------------------------------------------
; swiPortEnableInterrupts
        .asmfunc
swiPortEnableInterrupts
       	mrs     r0, SPSR
        bic     r0, r0, #0x80
        msr     SPSR_c, r0
		bx		r14
        .endasmfunc
;-------------------------------------------------------------------------------
; swiPortTaskUsesFPU
        .asmfunc
swiPortTaskUsesFPU
		bx		r14
	
        .endasmfunc
;-------------------------------------------------------------------------------
; swiRaisePrivilege

; Must return zero in R0 if caller was in user mode
        .asmfunc
swiRaisePrivilege
		mrs		r12, spsr
		ands	r0, r12, #0x0F		; return value
		orreq	r12, r12, #0x1F
		msreq	spsr_c, r12
		bx		r14
        .endasmfunc
;-------------------------------------------------------------------------------
; swiPortEnterCritical
        .asmfunc
swiPortEnterCritical
		mrs     r0, SPSR
		orr     r0, r0, #0x80
		msr     SPSR_c, r0
		ldr		r0, ulCriticalNestingConst
		ldr		r12, [r0]
		add		r12, r12, #1
		str		r12, [r0]
		bx		r14
        .endasmfunc
;-------------------------------------------------------------------------------
; swiPortExitCritical
        .asmfunc
swiPortExitCritical
		ldr		r0, ulCriticalNestingConst
		ldr		r12, [r0]
		cmp		r12, #0
		bxeq	r14
		subs	r12, r12, #1
		str		r12, [r0]
		bxne	r14
       	mrs     r0, SPSR
        bic     r0, r0, #0x80
        msr     SPSR_c, r0
		bx		r14
        .endasmfunc
;-------------------------------------------------------------------------------
; SetRegion

		.def  prvMpuSetRegion
        .asmfunc
; void _mpuSetRegion(unsigned region, unsigned base, unsigned size, unsigned access);

prvMpuSetRegion
        and   r0,  r0, #15                  ; select region
        mcr   p15, #0, r0, c6, c2, #0
        mcr   p15, #0, r1, c6, c1, #0		; Base Address
        mcr   p15, #0, r3, c6, c1, #4		; Access Attributes
        mcr   p15, #0, r2, c6, c1, #2		; Size and Enable
		bx	  lr
        .endasmfunc
;-------------------------------------------------------------------------------
; Enable Mpu

    	.def  prvMpuEnable
        .asmfunc
prvMpuEnable
        mrc   p15, #0, r0, c1, c0, #0
        orr   r0,  r0, #1
        dsb
        mcr   p15, #0, r0, c1, c0, #0
        isb
        bx    lr
        .endasmfunc
;-------------------------------------------------------------------------------
; Disable Mpu

		.def  prvMpuDisable
        .asmfunc
prvMpuDisable
        mrc   p15, #0, r0, c1, c0, #0
        bic   r0,  r0, #1
        dsb
        mcr   p15, #0, r0, c1, c0, #0
        isb
		bx	  lr
        .endasmfunc
;-------------------------------------------------------------------------------

pxCurrentTCBConst	     .word   pxCurrentTCB
ulFPUContextConst 	     .word   ulTaskHasFPUContext
ulCriticalNestingConst   .word   ulCriticalNesting
ulTaskHasFPUContextConst .word   ulTaskHasFPUContext

;-------------------------------------------------------------------------------

    
