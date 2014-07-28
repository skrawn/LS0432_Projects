/*
    FreeRTOS V7.4.0 - Copyright (C) 2013 Real Time Engineers Ltd.

    FEATURES AND PORTS ARE ADDED TO FREERTOS ALL THE TIME.  PLEASE VISIT
    http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.

    >>>>>>NOTE<<<<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
    details. You should have received a copy of the GNU General Public License
    and the FreeRTOS license exception along with FreeRTOS; if not itcan be
    viewed here: http://www.freertos.org/a00114.html and also obtained by
    writing to Real Time Engineers Ltd., contact details for whom are available
    on the FreeRTOS WEB site.

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, books, training, latest versions, 
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, and our new
    fully thread aware and reentrant UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High 
    Integrity Systems, who sell the code with commercial support, 
    indemnification and middleware, under the OpenRTOS brand.
    
    http://www.SafeRTOS.com - High Integrity Systems also provide a safety 
    engineered and independently SIL3 certified version for use in safety and 
    mission critical applications that require provable dependability.
*/

#ifndef __PORTMACRO_H__
#define __PORTMACRO_H__

/*-----------------------------------------------------------
 * Port specific definitions.
 *
 * The settings in this file configure FreeRTOS correctly for the
 * given hardware and compiler.
 *
 * These settings should not be altered.
 *-----------------------------------------------------------
 */

/* Type definitions. */
#define portCHAR        char
#define portFLOAT       float
#define portDOUBLE      double
#define portLONG        long
#define portSHORT       short
#define portSTACK_TYPE  unsigned long
#define portBASE_TYPE   long

#if (configUSE_16_BIT_TICKS == 1)
    typedef unsigned portSHORT portTickType;
    #define portMAX_DELAY (portTickType) 0xFFFF
#else
    typedef unsigned portLONG portTickType;
    #define portMAX_DELAY (portTickType) 0xFFFFFFFFF
#endif


/* Architecture specifics. */
#define portSTACK_GROWTH    (-1)
#define portTICK_RATE_MS    ((portTickType) 1000 / configTICK_RATE_HZ)		
#define portBYTE_ALIGNMENT  8

/* Critical section handling. */
#pragma SWI_ALIAS(vPortEnterCritical, 2)
extern void vPortEnterCritical( void );

#pragma SWI_ALIAS(vPortExitCritical, 3)
extern void vPortExitCritical( void );

#pragma SWI_ALIAS(vPortDisableInterrupts, 5)
extern void vPortDisableInterrupts( void );

#pragma SWI_ALIAS(vPortEnableInterrupts, 6)
extern void vPortEnableInterrupts( void );

#define portENTER_CRITICAL()        vPortEnterCritical()
#define portEXIT_CRITICAL()         vPortExitCritical()
#define portDISABLE_INTERRUPTS()    vPortDisableInterrupts()
#define portENABLE_INTERRUPTS()		vPortEnableInterrupts()

/* Scheduler utilities. */
#pragma SWI_ALIAS(vPortYield, 0)
extern void vPortYield( void );

#define portYIELD()             	vPortYield()
#define portSYS_SSIR1_REG			( * ( ( volatile unsigned long * ) 0xFFFFFFB0 ) )
#define portSYS_SSIR1_SSKEY			( 0x7500UL )
#define portYIELD_WITHIN_API()		{ portSYS_SSIR1_REG = portSYS_SSIR1_SSKEY;  ( void ) portSYS_SSIR1_REG; }
#define portYIELD_FROM_ISR( x )		if( x != pdFALSE ){ portSYS_SSIR1_REG = portSYS_SSIR1_SSKEY;  ( void ) portSYS_SSIR1_REG; }

/* Floating Point Support */
#pragma SWI_ALIAS(vPortTaskUsesFPU, 4)
extern void vPortTaskUsesFPU(void);

/* Architecture specific optimisations. */
#if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

	/* Generic helper function. */
	unsigned long ulPortCountLeadingZeros( unsigned long ulBitmap );

	/* Check the configuration. */
	#if( configMAX_PRIORITIES > 32 )
		#error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice.
	#endif

	/* Store/clear the ready priorities in a bit map. */
	#define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
	#define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )

	/*-----------------------------------------------------------*/

	#define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31 - ulPortCountLeadingZeros( ( uxReadyPriorities ) ) )

#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */


/* Task function macros as described on the FreeRTOS.org WEB site. */
#define portTASK_FUNCTION(vFunction, pvParameters)       void vFunction(void *pvParameters)
#define portTASK_FUNCTION_PROTO(vFunction, pvParameters) void vFunction(void *pvParameters)


/* MPU specific constants.  */
#define portUSING_MPU_WRAPPERS		            1
#define portPRIVILEGE_BIT                       ( 0x80000000UL )

#define portMPU_REGION_READ_WRITE				( 0x03UL << 8UL )
#define portMPU_REGION_PRIVILEGED_READ_ONLY		( 0x05UL << 8UL )
#define portMPU_REGION_READ_ONLY				( 0x06UL << 8UL )
#define portMPU_REGION_PRIVILEGED_READ_WRITE	( 0x01UL << 8UL )

#define portMPU_REGION_STRONGLY_ORDERED         ( 0x00UL )
#define portMPU_REGION_DEVICE                   ( 0x01UL )
#define portMPU_REGION_CACHEABLE_BUFFERABLE		( 0x03UL )
#define portMPU_REGION_EXECUTE_NEVER			( 0x01UL << 12UL )

#define portMPU_REGION_ENABLE					( 0x01UL )

#define portMPU_TOTAL_REGIONS				    ( 8UL )

/* MPU region sizes */
#define portMPU_SIZE_32B						( 0x04UL << 1UL )
#define portMPU_SIZE_64B						( 0x05UL << 1UL )
#define portMPU_SIZE_128B						( 0x06UL << 1UL )
#define portMPU_SIZE_256B						( 0x07UL << 1UL )
#define portMPU_SIZE_512B						( 0x08UL << 1UL )
#define portMPU_SIZE_1KB						( 0x09UL << 1UL )
#define portMPU_SIZE_2KB						( 0x0AUL << 1UL )
#define portMPU_SIZE_4KB						( 0x0BUL << 1UL )
#define portMPU_SIZE_8KB						( 0x0CUL << 1UL )
#define portMPU_SIZE_16KB                       ( 0x0DUL << 1UL )
#define portMPU_SIZE_32KB                       ( 0x0EUL << 1UL )
#define portMPU_SIZE_64KB                       ( 0x0FUL << 1UL )
#define portMPU_SIZE_128KB                      ( 0x10UL << 1UL )
#define portMPU_SIZE_256KB                      ( 0x11UL << 1UL )
#define portMPU_SIZE_512KB                      ( 0x12UL << 1UL )
#define portMPU_SIZE_1MB					    ( 0x13UL << 1UL )
#define portMPU_SIZE_2MB					    ( 0x14UL << 1UL )
#define portMPU_SIZE_4MB					    ( 0x15UL << 1UL )
#define portMPU_SIZE_8MB					    ( 0x16UL << 1UL )
#define portMPU_SIZE_16MB						( 0x17UL << 1UL )
#define portMPU_SIZE_32MB						( 0x18UL << 1UL )
#define portMPU_SIZE_64MB					    ( 0x19UL << 1UL )
#define portMPU_SIZE_128MB					    ( 0x1AUL << 1UL )
#define portMPU_SIZE_256MB					    ( 0x1BUL << 1UL )
#define portMPU_SIZE_512MB					    ( 0x1CUL << 1UL )
#define portMPU_SIZE_1GB					    ( 0x1DUL << 1UL )
#define portMPU_SIZE_2GB					    ( 0x1EUL << 1UL )
#define portMPU_SIZE_4GB					    ( 0x1FUL << 1UL )

/* Default MPU regions */
#define portUNPRIVILEGED_FLASH_REGION		    ( 0UL )
#define portPRIVILEGED_FLASH_REGION			    ( 1UL )
#define portPRIVILEGED_RAM_REGION			    ( 2UL )
#define portGENERAL_PERIPHERALS_REGION		    ( 3UL )
#define portSTACK_REGION					    ( 4UL )
#define portFIRST_CONFIGURABLE_REGION	        ( 5UL )
#define portLAST_CONFIGURABLE_REGION		    ( portMPU_TOTAL_REGIONS - 2 )
#define portPRIVILEGED_SYSTEM_REGION            ( portMPU_TOTAL_REGIONS - 1 )
#define portNUM_CONFIGURABLE_REGIONS		    ( ( portLAST_CONFIGURABLE_REGION - portFIRST_CONFIGURABLE_REGION ) + 1 )
#define portTOTAL_NUM_REGIONS				    ( portNUM_CONFIGURABLE_REGIONS + 1 ) /* Plus one to make space for the stack region. */

#define portSWITCH_TO_USER_MODE() \
{ \
   asm( " CPS #0x10"); \
}


typedef struct MPU_REGION_REGISTERS
{
	unsigned ulRegionBaseAddress;
	unsigned ulRegionSize;
	unsigned ulRegionAttribute;
} xMPU_REGION_REGISTERS;


/* Plus 1 to create space for the stack region. */
typedef struct MPU_SETTINGS
{
	xMPU_REGION_REGISTERS xRegion[ portTOTAL_NUM_REGIONS ];
} xMPU_SETTINGS;

#endif /* __PORTMACRO_H__ */

