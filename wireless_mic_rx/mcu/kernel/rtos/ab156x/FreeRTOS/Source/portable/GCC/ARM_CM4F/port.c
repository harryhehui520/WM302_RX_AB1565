/*
 * FreeRTOS Kernel V10.1.1
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the ARM CM4F port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "memory_attribute.h"
#include "hal.h"
#include "hal_dwt.h"
#ifdef MTK_SWLA_ENABLE
#include "swla.h"
#endif /* MTK_SWLA_ENABLE */
#ifdef MTK_SYSTEM_HANG_TRACER_ENABLE
#include "systemhang_tracer.h"
#endif /* MTK_SYSTEM_HANG_TRACER_ENABLE */
#ifdef MTK_MEMORY_MONITOR_ENABLE
#include "memory_monitor.h"
#endif /* MTK_MEMORY_MONITOR_ENABLE */

#ifdef SYSTEM_DAEMON_TASK_ENABLE
#include "system_daemon.h"
#endif /* SYSTEM_DAEMON_TASK_ENABLE */

#ifdef HAL_ESC_MODULE_ENABLED
#include "hal_esc_internal.h"
#endif

#include "syslog.h"
log_create_module(os, PRINT_LEVEL_INFO);
#ifndef __VFP_FP__
	#error This port can only be used when the project options are configured to enable hardware floating point support.
#endif

#ifndef configSYSTICK_CLOCK_HZ
	#define configSYSTICK_CLOCK_HZ configCPU_CLOCK_HZ
	/* Ensure the SysTick is clocked at the same frequency as the core. */
	#define portNVIC_SYSTICK_CLK_BIT	( 1UL << 2UL )
#else
	/* The way the SysTick is clocked is not modified in case it is not the same
	as the core. */
	#define portNVIC_SYSTICK_CLK_BIT	( 0 )
#endif

/* Constants required to manipulate the core.  Registers first... */
#define portNVIC_SYSTICK_CTRL_REG			( * ( ( volatile uint32_t * ) 0xe000e010 ) )
#define portNVIC_SYSTICK_LOAD_REG			( * ( ( volatile uint32_t * ) 0xe000e014 ) )
#define portNVIC_SYSTICK_CURRENT_VALUE_REG	( * ( ( volatile uint32_t * ) 0xe000e018 ) )
#define portNVIC_SYSPRI2_REG				( * ( ( volatile uint32_t * ) 0xe000ed20 ) )
/* ...then bits in the registers. */
#define portNVIC_SYSTICK_INT_BIT			( 1UL << 1UL )
#define portNVIC_SYSTICK_ENABLE_BIT			( 1UL << 0UL )
#define portNVIC_SYSTICK_COUNT_FLAG_BIT		( 1UL << 16UL )
#define portNVIC_PENDSVCLEAR_BIT 			( 1UL << 27UL )
#define portNVIC_PEND_SYSTICK_CLEAR_BIT		( 1UL << 25UL )

/* Constants used to detect a Cortex-M7 r0p1 core, which should use the ARM_CM7
r0p1 port. */
#define portCPUID							( * ( ( volatile uint32_t * ) 0xE000ed00 ) )
#define portCORTEX_M7_r0p1_ID				( 0x410FC271UL )
#define portCORTEX_M7_r0p0_ID				( 0x410FC270UL )

#define portNVIC_PENDSV_PRI					( ( ( uint32_t ) configKERNEL_INTERRUPT_PRIORITY ) << 16UL )
#define portNVIC_SYSTICK_PRI				( ( ( uint32_t ) configMAX_SYSCALL_INTERRUPT_PRIORITY ) << 24UL )

/* Constants required to check the validity of an interrupt priority. */
#define portFIRST_USER_INTERRUPT_NUMBER		( 16 )
#define portNVIC_IP_REGISTERS_OFFSET_16 	( 0xE000E3F0 )
#define portAIRCR_REG						( * ( ( volatile uint32_t * ) 0xE000ED0C ) )
#define portMAX_8_BIT_VALUE					( ( uint8_t ) 0xff )
#define portTOP_BIT_OF_BYTE					( ( uint8_t ) 0x80 )
#define portMAX_PRIGROUP_BITS				( ( uint8_t ) 7 )
#define portPRIORITY_GROUP_MASK				( 0x07UL << 8UL )
#define portPRIGROUP_SHIFT					( 8UL )

/* Masks off all bits but the VECTACTIVE bits in the ICSR register. */
#define portVECTACTIVE_MASK					( 0xFFUL )

/* Constants required to manipulate the VFP. */
#define portFPCCR							( ( volatile uint32_t * ) 0xe000ef34 ) /* Floating point context control register. */
#define portASPEN_AND_LSPEN_BITS			( 0x3UL << 30UL )

/* Constants required to set up the initial stack. */
#define portINITIAL_XPSR					( 0x01000000 )
#define portINITIAL_EXC_RETURN				( 0xfffffffd )

/* The systick is a 24-bit counter. */
#define portMAX_24_BIT_NUMBER				( 0xffffffUL )

/* For strict compliance with the Cortex-M spec the task start address should
have bit-0 clear, as it is loaded into the PC on exit from an ISR. */
#define portSTART_ADDRESS_MASK		( ( StackType_t ) 0xfffffffeUL )

/* A fiddle factor to estimate the number of SysTick counts that would have
occurred while the SysTick counter is stopped during tickless idle
calculations. */
#define portMISSED_COUNTS_FACTOR			( 45UL )

/* Let the user override the pre-loading of the initial LR with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger. */
#ifdef configTASK_RETURN_ADDRESS
	#define portTASK_RETURN_ADDRESS	configTASK_RETURN_ADDRESS
#else
	#define portTASK_RETURN_ADDRESS	prvTaskExitError
#endif

/*
 * Setup the timer to generate the tick interrupts.  The implementation in this
 * file is weak to allow application writers to change the timer used to
 * generate the tick interrupt.
 */
void vPortSetupTimerInterrupt( void );

/*
 * Exception handlers.
 */
void xPortPendSVHandler( void ) __attribute__ (( naked ));
void xPortSysTickHandler( void );
void vPortSVCHandler( void ) __attribute__ (( naked ));

/*
 * Start first task is a separate function so it can be tested in isolation.
 */
static void prvPortStartFirstTask( void ) __attribute__ (( naked ));

/*
 * Function to enable the VFP.
 */
static void vPortEnableVFP( void ) __attribute__ (( naked ));

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
static void prvTaskExitError( void );

/*-----------------------------------------------------------*/
#ifdef __GNUC__
__attribute__((used)) const int uxTopUsedPriority = configMAX_PRIORITIES - 1;
#endif /* __GNUC__ */

/* Each task maintains its own interrupt status in the critical nesting
variable. */
static UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

/*
 * The number of SysTick increments that make up one tick period.
 */
#if( configUSE_TICKLESS_IDLE == 1 )
	static uint32_t ulTimerCountsForOneTick = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * The maximum number of tick periods that can be suppressed is limited by the
 * 24 bit resolution of the SysTick timer.
 */
#if( configUSE_TICKLESS_IDLE == 1 )
	static uint32_t xMaximumPossibleSuppressedTicks = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * Compensate for the CPU cycles that pass while the SysTick is stopped (low
 * power functionality only.
 */
#if( configUSE_TICKLESS_IDLE == 1 )
	static uint32_t ulStoppedTimerCompensation = 0;
#endif /* configUSE_TICKLESS_IDLE */

/*
 * Used by the portASSERT_IF_INTERRUPT_PRIORITY_INVALID() macro to ensure
 * FreeRTOS API functions are not called from interrupts that have been assigned
 * a priority above configMAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#if( configASSERT_DEFINED == 1 )
	 static uint8_t ucMaxSysCallPriority = 0;
	 static uint32_t ulMaxPRIGROUPValue = 0;
	 static const volatile uint8_t * const pcInterruptPriorityRegisters = ( const volatile uint8_t * const ) portNVIC_IP_REGISTERS_OFFSET_16;
#endif /* configASSERT_DEFINED */

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
	/* Simulate the stack frame as it would be created by a context switch
	interrupt. */

	/* Offset added to account for the way the MCU uses the stack on entry/exit
	of interrupts, and to ensure alignment. */
	pxTopOfStack--;

	*pxTopOfStack = portINITIAL_XPSR;	/* xPSR */
	pxTopOfStack--;
	*pxTopOfStack = ( ( StackType_t ) pxCode ) & portSTART_ADDRESS_MASK;	/* PC */
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) portTASK_RETURN_ADDRESS;	/* LR */

	/* Save code space by skipping register initialisation. */
	pxTopOfStack -= 5;	/* R12, R3, R2 and R1. */
	*pxTopOfStack = ( StackType_t ) pvParameters;	/* R0 */

	/* A save method is being used that requires each task to maintain its
	own exec return value. */
	pxTopOfStack--;
	*pxTopOfStack = portINITIAL_EXC_RETURN;

	pxTopOfStack -= 8;	/* R11, R10, R9, R8, R7, R6, R5 and R4. */

	return pxTopOfStack;
}
/*-----------------------------------------------------------*/

static void prvTaskExitError( void )
{
volatile uint32_t ulDummy = 0;

	/* A function that implements a task must not exit or attempt to return to
	its caller as there is nothing to return to.  If a task wants to exit it
	should instead call vTaskDelete( NULL ).

	Artificially force an assert() to be triggered if configASSERT() is
	defined, then stop here so application writers can catch the error. */
	configASSERT( uxCriticalNesting == ~0UL );
	portDISABLE_INTERRUPTS();
	while( ulDummy == 0 )
	{
		/* This file calls prvTaskExitError() after the scheduler has been
		started to remove a compiler warning about the function being defined
		but never called.  ulDummy is used purely to quieten other warnings
		about code appearing after this function is called - making ulDummy
		volatile makes the compiler think the function could return and
		therefore not output an 'unreachable code' warning for code that appears
		after it. */
	}
}
/*-----------------------------------------------------------*/

#if (configCHECK_FOR_STACK_OVERFLOW > 0)
#ifdef HAL_DWT_MODULE_ENABLED
#include "core_cm4.h"
void vPortCurrentTaskStackOverflowCheck(void)
{
	uint32_t stack_start_address;
	int32_t ret;

	stack_start_address = uxTaskGetBottomOfStack(NULL);

	/* enable debug monitor mode    */
	if (!(CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)) {
		if (!(CoreDebug->DEMCR & (CoreDebug_DEMCR_MON_EN_Msk | CoreDebug_DEMCR_TRCENA_Msk))) {
			CoreDebug->DEMCR |= (CoreDebug_DEMCR_MON_EN_Msk | CoreDebug_DEMCR_TRCENA_Msk) ;
		}
	}

	/* check the last 2words */
	ret = hal_dwt_request_watchpoint(HAL_DWT_3, stack_start_address, 0x3, WDE_DATA_WO);
	//printf("comparator:%d, check address: 0x%x\r\n",HAL_DWT_3,stack_end_address);

	/* Just to avoid compiler warnings. */
	( void ) ret;
}
#else
	#error please enable HAL_DWT_MODULE_ENABLED in project inc/hal_feature_config.h for task stack overflow check.
#endif /* HAL_DWT_MODULE_ENABLED */
#endif /* (configCHECK_FOR_STACK_OVERFLOW > 0) */

void vPortSVCHandler( void )
{
	__asm volatile (
					"	cpsid i							\n"
					"	blx Flash_ReturnReady			\n" /* must suspend flash before fetch code from flash */
					#if defined(HAL_ESC_MODULE_ENABLED) && defined(ESC_FLASH_ENABLE)
					"	blx esc_flash_return_ready		\n"
					#endif
					"	cpsie i 						\n"
					#if (configCHECK_FOR_STACK_OVERFLOW > 0)/* Enable the stack overflow check by DWT */
					#ifdef HAL_DWT_MODULE_ENABLED
					"	bl hal_dwt_init                 \n"
					"	bl vPortCurrentTaskStackOverflowCheck \n"
					#endif /* HAL_DWT_MODULE_ENABLED */
					#endif /* (configCHECK_FOR_STACK_OVERFLOW > 0)  */
					#ifdef MTK_SWLA_ENABLE
					"	bl vTraceTaskSwitchIn           \n"
					#endif /* MTK_SWLA_ENABLE */
					"	ldr	r3, pxCurrentTCBConst2		\n" /* Restore the context. */
					"	ldr r1, [r3]					\n" /* Use pxCurrentTCBConst to get the pxCurrentTCB address. */
					"	ldr r0, [r1]					\n" /* The first item in pxCurrentTCB is the task top of stack. */
					"	ldmia r0!, {r4-r11, r14}		\n" /* Pop the registers that are not automatically saved on exception entry and the critical nesting count. */
					"	msr psp, r0						\n" /* Restore the task stack pointer. */
					"	isb								\n"
					"	mov r0, #0 						\n"
					"	msr	basepri, r0					\n"
					"	bx r14							\n"
					"									\n"
					"	.align 4						\n"
					"pxCurrentTCBConst2: .word pxCurrentTCB				\n"
				);
}
/*-----------------------------------------------------------*/

static void prvPortStartFirstTask( void )
{
	/* Start the first task.  This also clears the bit that indicates the FPU is
	in use in case the FPU was used before the scheduler was started - which
	would otherwise result in the unnecessary leaving of space in the SVC stack
	for lazy saving of FPU registers. */
	__asm volatile(
					#ifdef MTK_SWLA_ENABLE
					" bl SLA_Enable         \n"
					#endif /* MTK_SWLA_ENABLE */
					" ldr r0, =0xE000ED08 	\n" /* Use the NVIC offset register to locate the stack. */
					" ldr r0, [r0] 			\n"
					" ldr r0, [r0] 			\n"
					" msr msp, r0			\n" /* Set the msp back to the start of the stack. */
					" mov r0, #0			\n" /* Clear the bit that indicates the FPU is in use, see comment above. */
					" msr control, r0		\n"
					" cpsie i				\n" /* Globally enable interrupts. */
					" cpsie f				\n"
					" dsb					\n"
					" isb					\n"
					" svc 0					\n" /* System call to start first task. */
					" nop					\n"
				);
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( void )
{
	/* configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to 0.
	See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html */
	configASSERT( configMAX_SYSCALL_INTERRUPT_PRIORITY );

	/* This port can be used on all revisions of the Cortex-M7 core other than
	the r0p1 parts.  r0p1 parts should use the port from the
	/source/portable/GCC/ARM_CM7/r0p1 directory. */
	configASSERT( portCPUID != portCORTEX_M7_r0p1_ID );
	configASSERT( portCPUID != portCORTEX_M7_r0p0_ID );

	#if( configASSERT_DEFINED == 1 )
	{
		volatile uint32_t ulOriginalPriority;
		volatile uint8_t * const pucFirstUserPriorityRegister = ( volatile uint8_t * const ) ( portNVIC_IP_REGISTERS_OFFSET_16 + portFIRST_USER_INTERRUPT_NUMBER );
		volatile uint8_t ucMaxPriorityValue;

		/* Determine the maximum priority from which ISR safe FreeRTOS API
		functions can be called.  ISR safe functions are those that end in
		"FromISR".  FreeRTOS maintains separate thread and ISR API functions to
		ensure interrupt entry is as fast and simple as possible.

		Save the interrupt priority value that is about to be clobbered. */
		ulOriginalPriority = *pucFirstUserPriorityRegister;

		/* Determine the number of priority bits available.  First write to all
		possible bits. */
		*pucFirstUserPriorityRegister = portMAX_8_BIT_VALUE;

		/* Read the value back to see how many bits stuck. */
		ucMaxPriorityValue = *pucFirstUserPriorityRegister;

		/* Use the same mask on the maximum system call priority. */
		ucMaxSysCallPriority = configMAX_SYSCALL_INTERRUPT_PRIORITY & ucMaxPriorityValue;

		/* Calculate the maximum acceptable priority group value for the number
		of bits read back. */
		ulMaxPRIGROUPValue = portMAX_PRIGROUP_BITS;
		while( ( ucMaxPriorityValue & portTOP_BIT_OF_BYTE ) == portTOP_BIT_OF_BYTE )
		{
			ulMaxPRIGROUPValue--;
			ucMaxPriorityValue <<= ( uint8_t ) 0x01;
		}

		#ifdef __NVIC_PRIO_BITS
		{
			/* Check the CMSIS configuration that defines the number of
			priority bits matches the number of priority bits actually queried
			from the hardware. */
			configASSERT( ( portMAX_PRIGROUP_BITS - ulMaxPRIGROUPValue ) == __NVIC_PRIO_BITS );
		}
		#endif

		#ifdef configPRIO_BITS
		{
			/* Check the FreeRTOS configuration that defines the number of
			priority bits matches the number of priority bits actually queried
			from the hardware. */
			configASSERT( ( portMAX_PRIGROUP_BITS - ulMaxPRIGROUPValue ) == configPRIO_BITS );
		}
		#endif

		/* Shift the priority group value back to its position within the AIRCR
		register. */
		ulMaxPRIGROUPValue <<= portPRIGROUP_SHIFT;
		ulMaxPRIGROUPValue &= portPRIORITY_GROUP_MASK;

		/* Restore the clobbered interrupt priority register to its original
		value. */
		*pucFirstUserPriorityRegister = ulOriginalPriority;
	}
	#endif /* conifgASSERT_DEFINED */

	/* Make PendSV the lowest priority interrupts. */
	portNVIC_SYSPRI2_REG |= portNVIC_PENDSV_PRI;
	/* Make SysTick the highest priority interrupts(configMAX_SYSCALL_INTERRUPT_PRIORITY), to ensure systick accurancy*/
	portNVIC_SYSPRI2_REG |= portNVIC_SYSTICK_PRI;

	/* Start the timer that generates the tick ISR.  Interrupts are disabled
	here already. */
	vPortSetupTimerInterrupt();

	/* Ensure the VFP is enabled - it should be anyway. */
	vPortEnableVFP();

	/* Lazy save always. */
	*( portFPCCR ) |= portASPEN_AND_LSPEN_BITS;

	#ifdef SYSTEM_DAEMON_TASK_ENABLE
	extern TaskHandle_t system_daemon_task_handle;
	configASSERT( xTaskCreate( system_daemon_task, "SYSDEA", SYSTEM_DAEMON_STACK_SIZE/sizeof(StackType_t), ( void * ) NULL, ( (tskIDLE_PRIORITY + 1) | portPRIVILEGE_BIT ), &system_daemon_task_handle ) );
	system_daemon_task_init();
	#endif /* SYSTEM_DAEMON_TASK_ENABLE */

	/* Initialise the critical nesting count ready for the first task. */
	uxCriticalNesting = 0;

	/* Call this function to indicate the system initialize done. */
    hal_core_status_write(HAL_CORE_MCU, HAL_CORE_ACTIVE);
	
	/* Start the first task. */
	prvPortStartFirstTask();

	/* Should never get here as the tasks will now be executing!  Call the task
	exit error function to prevent compiler warnings about a static function
	not being called in the case that the application writer overrides this
	functionality by defining configTASK_RETURN_ADDRESS.  Call
	vTaskSwitchContext() so link time optimisation does not remove the
	symbol. */
	vTaskSwitchContext();
	prvTaskExitError();

	/* Should not get here! */
	return 0;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
	/* Not implemented in ports where there is nothing to return to.
	Artificially force an assert. */
	configASSERT( uxCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/
#ifdef configCheck_CRITICAL_SECTION_LENGTH
ATTR_ZIDATA_IN_TCM static uint32_t mask_int_start = 0;
ATTR_ZIDATA_IN_TCM static uint32_t mask_int_end = 0;
ATTR_ZIDATA_IN_TCM static uint32_t mask_int_time = 0;
ATTR_ZIDATA_IN_TCM static uint32_t mask_int_lr;

typedef struct {
    uint32_t mask_int_lr;
    uint32_t mask_int_time;
    uint32_t cur_time;
} mask_int_debug_t;

#define MASK_INT_DEBUG_NUM (20)
ATTR_ZIDATA_IN_NONCACHED_SYSRAM mask_int_debug_t mask_int_debug[MASK_INT_DEBUG_NUM];
ATTR_ZIDATA_IN_TCM uint32_t mask_int_index = 0;

ATTR_TEXT_IN_SYSRAM void mask_int_debug_log_save(uint32_t mask_int_lr, uint32_t time, uint32_t index)
{
    configASSERT(index < MASK_INT_DEBUG_NUM);
    mask_int_debug[index].mask_int_lr = mask_int_lr;
    mask_int_debug[index].mask_int_time = time;
    hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &(mask_int_debug[index].cur_time));
}

#endif /* configCheck_CRITICAL_SECTION_LENGTH */

ATTR_TEXT_IN_SYSRAM void vPortEnterCritical( void )
{
	/* The interrupt should not be masked when this API is 1st called.
	in order to check the error usage, typical case is:
		hal_nvic_save_and_set_interrupt_mask()
		xQueueGenericSend() // Calling an FreeRTOS API function from within a critical section
		hal_nvic_restore_interrupt_mask()
	*/
	configASSERT(uxCriticalNesting || !__get_BASEPRI());

	portDISABLE_INTERRUPTS();
	uxCriticalNesting++;

	/* This is not the interrupt safe version of the enter critical function so
	assert() if it is being called from an interrupt context.  Only API
	functions that end in "FromISR" can be used in an interrupt.  Only assert if
	the critical nesting count is 1 to protect against recursive calls if the
	assert function also uses a critical section. */
	if( uxCriticalNesting == 1 )
	{
		#ifdef configCheck_CRITICAL_SECTION_LENGTH
		mask_int_lr = (uint32_t)__builtin_return_address(0);
		hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &mask_int_start);
		#endif /* configCheck_CRITICAL_SECTION_LENGTH */

		configASSERT( ( portNVIC_INT_CTRL_REG & portVECTACTIVE_MASK ) == 0 );
	}
}
/*-----------------------------------------------------------*/

ATTR_TEXT_IN_SYSRAM void vPortExitCritical( void )
{
	#ifdef configCheck_CRITICAL_SECTION_LENGTH
	uint32_t mask_int_check_fail = 0x0;
	uint32_t mask_int_too_long_time = 0x0;
	uint32_t mask_int_too_long_lr = 0x0;
	uint32_t index = 0x0;
	#endif /* configCheck_CRITICAL_SECTION_LENGTH */

	configASSERT( uxCriticalNesting );
	uxCriticalNesting--;
	if( uxCriticalNesting == 0 )
	{
		#ifdef configCheck_CRITICAL_SECTION_LENGTH
		#define CLK_CM4_FREQ_26M      ((uint32_t) 26000000)
		hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_1M, &mask_int_end);
		hal_gpt_get_duration_count(mask_int_start, mask_int_end, &mask_int_time);

		if (mask_int_time > configMASK_IRQ_DURATION_TIME) {
			extern uint32_t SystemCoreClock;
			if(SystemCoreClock > CLK_CM4_FREQ_26M) {
				/* skip 26M clock */
				//configASSERT(0);
				mask_int_check_fail = 1;
				mask_int_too_long_time = mask_int_time;
				mask_int_too_long_lr = mask_int_lr;
				index = mask_int_index;
				mask_int_index ++;
				mask_int_index = (mask_int_index < MASK_INT_DEBUG_NUM) ? mask_int_index : 0;
			}
		}

		mask_int_start = 0;
		mask_int_end = 0;
		mask_int_time = 0;
		#endif /* configCheck_CRITICAL_SECTION_LENGTH */

		portENABLE_INTERRUPTS();

		#ifdef configCheck_CRITICAL_SECTION_LENGTH
		if(mask_int_check_fail){
			mask_int_debug_log_save(mask_int_too_long_lr, mask_int_too_long_time, index);
		}
		#endif /* configCheck_CRITICAL_SECTION_LENGTH */
	}
}
/*-----------------------------------------------------------*/

/*for context switch feed wdt*/
#ifdef MTK_SYSTEM_HANG_CHECK_ENABLE
void xportWdtFeed(void)
{
 	static uint32_t time_start_count = 0;
 	uint32_t time_end_count = 0;
 	uint32_t time_count = 0;

 	hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &time_end_count);
 	hal_gpt_get_duration_count(time_start_count, time_end_count, &time_count);
	if(time_count > 10) {
		*((volatile uint32_t*)WDT_RESTART_ADDRESS) = WDT_RESTART_KEY;
		hal_gpt_get_free_run_count(HAL_GPT_CLOCK_SOURCE_32K, &time_start_count);
	}
}
#endif /* MTK_SYSTEM_HANG_CHECK_ENABLE */

#if defined(MTK_SWLA_ENABLE) && defined(MTK_SWLA_ENABLE_O1)
static void pendsv_swla_start(void){

	SLA_CustomLogging("psv",SA_START);

}

static void pendsv_swla_stop(void){

	SLA_CustomLogging("psv",SA_STOP);

}
#endif

#ifdef AIR_CONFIGGDB_HELPER
/* prototypes to avoid compiler warnings */
__attribute__ ((naked, used)) void vPortPendSVHandler_native(void);
__attribute__ ((naked, used)) void PendSV_Handler_jumper(void);

__attribute__ ((naked, used)) void vPortPendSVHandler_native(void) {
#else
ATTR_TEXT_IN_TCM void xPortPendSVHandler( void ){
#endif
	/* This is a naked function. */

	__asm volatile
	(
	"	cpsid i								\n"
	"	push {lr}							\n"
	"	blx Flash_ReturnReady				\n" /* must suspend flash before fetch code from flash. */
#if defined(HAL_ESC_MODULE_ENABLED) && defined(ESC_FLASH_ENABLE)
	"	blx esc_flash_return_ready			\n"
#endif
#if defined(MTK_SWLA_ENABLE) && defined(MTK_SWLA_ENABLE_O1)
	"   bl pendsv_swla_start				\n"
#endif
	"	pop  {lr}							\n"
	"	cpsie i 							\n"
	"	mrs r0, psp							\n"
	"	isb									\n"
	"										\n"
	"	ldr	r3, pxCurrentTCBConst			\n" /* Get the location of the current TCB. */
	"	ldr	r2, [r3]						\n"
	"										\n"
	"	tst r14, #0x10						\n" /* Is the task using the FPU context?  If so, push high vfp registers. */
	"	it eq								\n"
	"	vstmdbeq r0!, {s16-s31}				\n"
	"										\n"
	"	stmdb r0!, {r4-r11, r14}			\n" /* Save the core registers. */
	"	str r0, [r2]						\n" /* Save the new top of stack into the first member of the TCB. */
	"										\n"
	"	stmdb sp!, {r0, r3}					\n"
	"	mov r0, %0 							\n"
	"	msr basepri, r0						\n"
	"	dsb									\n"
	"   isb									\n"
#if defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2)
	"	mrs r0, psp							\n"
	"	bl systemhang_task_exit_trace	    \n"
#endif /* defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2)*/
#ifdef MTK_MEMORY_MONITOR_ENABLE
	"	bl memorymonitor_task_exit_trace	\n"
#endif /* MTK_MEMORY_MONITOR_ENABLE */
	"	bl vTaskSwitchContext				\n"
#ifdef MTK_MEMORY_MONITOR_ENABLE
	"	bl memorymonitor_task_enter_trace	\n"
#endif /* MTK_MEMORY_MONITOR_ENABLE */
#if defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2)
	"	bl systemhang_task_enter_trace	    \n"
#endif /* defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2)*/
#if MTK_SYSTEM_HANG_TRACER_ENABLE
	"	bl systemhang_wdt_feed_in_task_switch\n"
#endif /* MTK_SYSTEM_HANG_TRACER_ENABLE */
	#ifdef MTK_SYSTEM_HANG_CHECK_ENABLE
	"	bl xportWdtFeed						\n"
	#endif
	#if (configCHECK_FOR_STACK_OVERFLOW > 0)
	#ifdef HAL_DWT_MODULE_ENABLED
	"	bl vPortCurrentTaskStackOverflowCheck\n" /* Enable the stack overflow check by DWT. */
	#endif /* HAL_DWT_MODULE_ENABLED */
	#endif /* (configCHECK_FOR_STACK_OVERFLOW > 0) */
#if defined(MTK_SWLA_ENABLE) && defined(MTK_SWLA_ENABLE_O1)
	"   bl pendsv_swla_stop					\n"
#endif
	"	mov r0, #0							\n"
	"	msr basepri, r0						\n"
	"	ldmia sp!, {r0, r3}					\n"
	"										\n"
	"	ldr r1, [r3]						\n" /* The first item in pxCurrentTCB is the task top of stack. */
	"	ldr r0, [r1]						\n"
	"										\n"
	"	ldmia r0!, {r4-r11, r14}			\n" /* Pop the core registers. */
	"										\n"
	"	tst r14, #0x10						\n" /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
	"	it eq								\n"
	"	vldmiaeq r0!, {s16-s31}				\n"
	"										\n"
	"	msr psp, r0							\n"
	"	isb									\n"
	"										\n"
	#ifdef WORKAROUND_PMU_CM001 /* XMC4000 specific errata workaround. */
		#if WORKAROUND_PMU_CM001 == 1
	"			push { r14 }				\n"
	"			pop { pc }					\n"
		#endif
	#endif
	"										\n"
	"	bx r14								\n"
	"										\n"
	"	.align 4							\n"
	"pxCurrentTCBConst: .word pxCurrentTCB	\n"
	::"i"(configMAX_SYSCALL_INTERRUPT_PRIORITY)
	);
}


#ifdef AIR_CONFIGGDB_HELPER /* if GDB debug helper is enabled */
/* Credits to:
 * - Artem Pisarneko for his initial contribution
 * - Prasana for the PendSVHandler updates
 * - Geoffrey Wossum for the Cortex-M4 contribution
 */

/* Switch control variable:
 * 0 - no hook installed (normal execution),
 * 1 - hook installation performed,
 * 2 - following hooked switches
 */
#ifdef __GNUC__
__attribute__((used))  /* needed for -flto and highest optimizations */
#endif
int volatile dbgPendSVHookState = 0;
/* Requested target task handle variable */
#ifdef __GNUC__
__attribute__((used))  /* needed for -flto and highest optimizations */
#endif
void *volatile dbgPendingTaskHandle;

#ifdef __GNUC__
__attribute__((used))  /* needed for -flto and highest optimizations */
#endif
const int volatile dbgFreeRTOSConfig_suspend_value = INCLUDE_vTaskSuspend;
#ifdef __GNUC__
__attribute__((used))  /* needed for -flto and highest optimizations */
#endif
const int volatile dbgFreeRTOSConfig_delete_value = INCLUDE_vTaskDelete;

__attribute__ ((naked, used)) void PendSV_Handler_jumper(void) {
  __asm volatile("b vPortPendSVHandler_native \n");
}

ATTR_TEXT_IN_TCM void xPortPendSVHandler( void ){
	/* This is a naked function. */
	__asm volatile
	(
	#ifdef AIR_CONFIGGDB_HELPER
    " ldr r1, _dbgPendSVHookState    \n" /* Check hook installed */
    " ldr r0, [r1]                   \n"
    " cmp r0, #0                     \n"
    " beq PendSV_Handler_jumper      \n" /* if no hook installed then jump to native handler, else proceed... */
    " cmp r0, #1                     \n" /* check whether hook triggered for the first time...  */
    " bne dbg_switch_to_pending_task \n" /* if not so, then jump to switching right now, otherwise current task context must be saved first...  */
    " mov r0, #2                     \n" /* mark hook after triggered for the first time */
    " str r0, [r1]                   \n"
	#endif /* AIR_CONFIGGDB_HELPER */
	"	cpsid i								\n"
	"	push {lr}							\n"
	"	blx Flash_ReturnReady				\n" /* must suspend flash before fetch code from flash. */
#if defined(HAL_ESC_MODULE_ENABLED) && defined(ESC_FLASH_ENABLE)
	"	blx esc_flash_return_ready			\n"
#endif
#if defined(MTK_SWLA_ENABLE) && defined(MTK_SWLA_ENABLE_O1)
	"   bl pendsv_swla_start				\n"
#endif
	"	pop  {lr}							\n"
	"	cpsie i 							\n"
	"	mrs r0, psp							\n"
	"	isb									\n"
	"										\n"
	"	ldr	r3, pxCurrentTCBConstG			\n" /* Get the location of the current TCB. */
	"	ldr	r2, [r3]						\n"
	"										\n"
	"	tst r14, #0x10						\n" /* Is the task using the FPU context?  If so, push high vfp registers. */
	"	it eq								\n"
	"	vstmdbeq r0!, {s16-s31}				\n"
	"										\n"
	"	stmdb r0!, {r4-r11, r14}			\n" /* Save the core registers. */
	"	str r0, [r2]						\n" /* Save the new top of stack into the first member of the TCB. */
	"										\n"
	"	stmdb sp!, {r0, r3}					\n"
	"	mov r0, %0 							\n"
	"	msr basepri, r0						\n"
	"	dsb									\n"
	"   isb									\n"
#if defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2)
	"	mrs r0, psp							\n"
	"	bl systemhang_task_exit_trace	    \n"
#endif /* defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2)*/
#ifdef MTK_MEMORY_MONITOR_ENABLE
	"	bl memorymonitor_task_exit_trace	\n"
#endif /* MTK_MEMORY_MONITOR_ENABLE */
	"	bl vTaskSwitchContext				\n"
#ifdef MTK_MEMORY_MONITOR_ENABLE
	"	bl memorymonitor_task_enter_trace	\n"
#endif /* MTK_MEMORY_MONITOR_ENABLE */
#if defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2)
	"	bl systemhang_task_enter_trace	    \n"
#endif /* defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O1) || defined(MTK_SYSTEM_HANG_TRACER_ENABLE_O2)*/
#if MTK_SYSTEM_HANG_TRACER_ENABLE
	"	bl systemhang_wdt_feed_in_task_switch\n"
#endif /* MTK_SYSTEM_HANG_TRACER_ENABLE */
	#ifdef MTK_SYSTEM_HANG_CHECK_ENABLE
	"	bl xportWdtFeed						\n"
	#endif
	#if (configCHECK_FOR_STACK_OVERFLOW > 0)
	#ifdef HAL_DWT_MODULE_ENABLED
	"	bl vPortCurrentTaskStackOverflowCheck\n" /* Enable the stack overflow check by DWT. */
	#endif /* HAL_DWT_MODULE_ENABLED */
	#endif /* (configCHECK_FOR_STACK_OVERFLOW > 0) */
#if defined(MTK_SWLA_ENABLE) && defined(MTK_SWLA_ENABLE_O1)
	"   bl pendsv_swla_stop					\n"
#endif
	"	mov r0, #0							\n"
	"	msr basepri, r0						\n"
	"	ldmia sp!, {r0, r3}					\n"
	"										\n"
	#ifdef AIR_CONFIGGDB_HELPER
    "dbg_switch_to_pending_task:     \n"
    " ldr r3, _dbgPendingTaskHandle  \n" /* --> Load task handle going to switch to <-- */
	#endif /* AIR_CONFIGGDB_HELPER */
	"	ldr r1, [r3]						\n" /* The first item in pxCurrentTCB is the task top of stack. */
	"	ldr r0, [r1]						\n"
	"										\n"
	"	ldmia r0!, {r4-r11, r14}			\n" /* Pop the core registers. */
	"										\n"
	"	tst r14, #0x10						\n" /* Is the task using the FPU context?  If so, pop the high vfp registers too. */
	"	it eq								\n"
	"	vldmiaeq r0!, {s16-s31}				\n"
	"										\n"
	"	msr psp, r0							\n"
	"	isb									\n"
	"										\n"
	#ifdef AIR_CONFIGGDB_HELPER
    " bkpt                       \n" /* <-- here debugger stops and steps out to target task context */
	#endif /* AIR_CONFIGGDB_HELPER */
	#ifdef WORKAROUND_PMU_CM001 /* XMC4000 specific errata workaround. */
		#if WORKAROUND_PMU_CM001 == 1
	"			push { r14 }				\n"
	"			pop { pc }					\n"
		#endif
	#endif
	"										\n"
	"	bx r14								\n"
	"										\n"
	"	.align 4							\n"
	"pxCurrentTCBConstG: .word pxCurrentTCB	\n"
	#ifdef AIR_CONFIGGDB_HELPER
    "_dbgPendSVHookState: .word dbgPendSVHookState     \n"
    "_dbgPendingTaskHandle: .word dbgPendingTaskHandle \n"
    ".word dbgFreeRTOSConfig_suspend_value             \n" /* force keep these symbols from cutting away by linker garbage collector */
    ".word dbgFreeRTOSConfig_delete_value              \n"
	#endif
	::"i"(configMAX_SYSCALL_INTERRUPT_PRIORITY)
	);
}
#endif
/*-----------------------------------------------------------*/

ATTR_TEXT_IN_RAM void xPortSysTickHandler( void )
{
	/* The SysTick runs at the lowest interrupt priority, so when this interrupt
	executes all interrupts must be unmasked.  There is therefore no need to
	save and then restore the interrupt mask value as its value is already
	known. */

	//( void ) portSET_INTERRUPT_MASK_FROM_ISR();
	UBaseType_t uxSavedInterruptStatus;

	uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();
	{
		/* must suspend flash before fetch code from flash */
		extern void Flash_ReturnReady(void);
		Flash_ReturnReady();

#if defined(HAL_ESC_MODULE_ENABLED) && defined(ESC_FLASH_ENABLE)
		esc_flash_return_ready();
#endif

#if defined(MTK_SWLA_ENABLE) && defined(MTK_SWLA_ENABLE_O1)
		SLA_CustomLogging("tik",SA_START);
#endif /* MTK_SWLA_ENABLE */

		/* Increment the RTOS tick. */
		if( xTaskIncrementTick() != pdFALSE )
		{
			/* A context switch is required.  Context switching is performed in
			the PendSV interrupt.  Pend the PendSV interrupt. */
			portNVIC_INT_CTRL_REG = portNVIC_PENDSVSET_BIT;
		}
	}

	#if defined(MTK_SWLA_ENABLE) && defined(MTK_SWLA_ENABLE_O1)
		SLA_CustomLogging("tik",SA_STOP);
	#endif
	portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus );
	//portCLEAR_INTERRUPT_MASK_FROM_ISR( 0 );
}
/*-----------------------------------------------------------*/

#if( configUSE_TICKLESS_IDLE == 1 )

	__attribute__((weak)) void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
	{
	uint32_t ulReloadValue, ulCompleteTickPeriods, ulCompletedSysTickDecrements;
	TickType_t xModifiableIdleTime;

		/* Make sure the SysTick reload value does not overflow the counter. */
		if( xExpectedIdleTime > xMaximumPossibleSuppressedTicks )
		{
			xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
		}

		/* Stop the SysTick momentarily.  The time the SysTick is stopped for
		is accounted for as best it can be, but using the tickless mode will
		inevitably result in some tiny drift of the time maintained by the
		kernel with respect to calendar time. */
		portNVIC_SYSTICK_CTRL_REG &= ~portNVIC_SYSTICK_ENABLE_BIT;

		/* Calculate the reload value required to wait xExpectedIdleTime
		tick periods.  -1 is used because this code will execute part way
		through one of the tick periods. */
		ulReloadValue = portNVIC_SYSTICK_CURRENT_VALUE_REG + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );
		if( ulReloadValue > ulStoppedTimerCompensation )
		{
			ulReloadValue -= ulStoppedTimerCompensation;
		}

		/* Enter a critical section but don't use the taskENTER_CRITICAL()
		method as that will mask interrupts that should exit sleep mode. */
		__asm volatile( "cpsid i" ::: "memory" );
		__asm volatile( "dsb" );
		__asm volatile( "isb" );

		/* If a context switch is pending or a task is waiting for the scheduler
		to be unsuspended then abandon the low power entry. */
		if( eTaskConfirmSleepModeStatus() == eAbortSleep )
		{
			/* Restart from whatever is left in the count register to complete
			this tick period. */
			portNVIC_SYSTICK_LOAD_REG = portNVIC_SYSTICK_CURRENT_VALUE_REG;

			/* Restart SysTick. */
			portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;

			/* Reset the reload register to the value required for normal tick
			periods. */
			portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;

			/* Re-enable interrupts - see comments above the cpsid instruction()
			above. */
			__asm volatile( "cpsie i" ::: "memory" );
		}
		else
		{
			/* Set the new reload value. */
			portNVIC_SYSTICK_LOAD_REG = ulReloadValue;

			/* Clear the SysTick count flag and set the count value back to
			zero. */
			portNVIC_SYSTICK_CURRENT_VALUE_REG = 0UL;

			/* Restart SysTick. */
			portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;

			/* Sleep until something happens.  configPRE_SLEEP_PROCESSING() can
			set its parameter to 0 to indicate that its implementation contains
			its own wait for interrupt or wait for event instruction, and so wfi
			should not be executed again.  However, the original expected idle
			time variable must remain unmodified, so a copy is taken. */
			xModifiableIdleTime = xExpectedIdleTime;
			configPRE_SLEEP_PROCESSING( xModifiableIdleTime );
			if( xModifiableIdleTime > 0 )
			{
				__asm volatile( "dsb" ::: "memory" );
				__asm volatile( "wfi" );
				__asm volatile( "isb" );
			}
			configPOST_SLEEP_PROCESSING( xExpectedIdleTime );

			/* Re-enable interrupts to allow the interrupt that brought the MCU
			out of sleep mode to execute immediately.  see comments above
			__disable_interrupt() call above. */
			__asm volatile( "cpsie i" ::: "memory" );
			__asm volatile( "dsb" );
			__asm volatile( "isb" );

			/* Disable interrupts again because the clock is about to be stopped
			and interrupts that execute while the clock is stopped will increase
			any slippage between the time maintained by the RTOS and calendar
			time. */
			__asm volatile( "cpsid i" ::: "memory" );
			__asm volatile( "dsb" );
			__asm volatile( "isb" );

			/* Disable the SysTick clock without reading the
			portNVIC_SYSTICK_CTRL_REG register to ensure the
			portNVIC_SYSTICK_COUNT_FLAG_BIT is not cleared if it is set.  Again,
			the time the SysTick is stopped for is accounted for as best it can
			be, but using the tickless mode will inevitably result in some tiny
			drift of the time maintained by the kernel with respect to calendar
			time*/
			portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT );

			/* Determine if the SysTick clock has already counted to zero and
			been set back to the current reload value (the reload back being
			correct for the entire expected idle time) or if the SysTick is yet
			to count to zero (in which case an interrupt other than the SysTick
			must have brought the system out of sleep mode). */
			if( ( portNVIC_SYSTICK_CTRL_REG & portNVIC_SYSTICK_COUNT_FLAG_BIT ) != 0 )
			{
				uint32_t ulCalculatedLoadValue;

				/* The tick interrupt is already pending, and the SysTick count
				reloaded with ulReloadValue.  Reset the
				portNVIC_SYSTICK_LOAD_REG with whatever remains of this tick
				period. */
				ulCalculatedLoadValue = ( ulTimerCountsForOneTick - 1UL ) - ( ulReloadValue - portNVIC_SYSTICK_CURRENT_VALUE_REG );

				/* Don't allow a tiny value, or values that have somehow
				underflowed because the post sleep hook did something
				that took too long. */
				if( ( ulCalculatedLoadValue < ulStoppedTimerCompensation ) || ( ulCalculatedLoadValue > ulTimerCountsForOneTick ) )
				{
					ulCalculatedLoadValue = ( ulTimerCountsForOneTick - 1UL );
				}

				portNVIC_SYSTICK_LOAD_REG = ulCalculatedLoadValue;

				/* As the pending tick will be processed as soon as this
				function exits, the tick value maintained by the tick is stepped
				forward by one less than the time spent waiting. */
				ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
			}
			else
			{
				/* Something other than the tick interrupt ended the sleep.
				Work out how long the sleep lasted rounded to complete tick
				periods (not the ulReload value which accounted for part
				ticks). */
				ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - portNVIC_SYSTICK_CURRENT_VALUE_REG;

				/* How many complete tick periods passed while the processor
				was waiting? */
				ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

				/* The reload value is set to whatever fraction of a single tick
				period remains. */
				portNVIC_SYSTICK_LOAD_REG = ( ( ulCompleteTickPeriods + 1UL ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
			}

			/* Restart SysTick so it runs from portNVIC_SYSTICK_LOAD_REG
			again, then set portNVIC_SYSTICK_LOAD_REG back to its standard
			value. */
			portNVIC_SYSTICK_CURRENT_VALUE_REG = 0UL;
			portNVIC_SYSTICK_CTRL_REG |= portNVIC_SYSTICK_ENABLE_BIT;
			vTaskStepTick( ulCompleteTickPeriods );
			portNVIC_SYSTICK_LOAD_REG = ulTimerCountsForOneTick - 1UL;

			/* Exit with interrpts enabled. */
			__asm volatile( "cpsie i" ::: "memory" );
		}
	}

#endif /* #if configUSE_TICKLESS_IDLE */
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
__attribute__(( weak )) void vPortSetupTimerInterrupt( void )
{
	/* Calculate the constants required to configure the tick interrupt. */
	#if( configUSE_TICKLESS_IDLE == 1 )
	{
		ulTimerCountsForOneTick = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ );
		xMaximumPossibleSuppressedTicks = portMAX_24_BIT_NUMBER / ulTimerCountsForOneTick;
		ulStoppedTimerCompensation = portMISSED_COUNTS_FACTOR / ( configCPU_CLOCK_HZ / configSYSTICK_CLOCK_HZ );
	}
	#endif /* configUSE_TICKLESS_IDLE */

	/* Stop and clear the SysTick. */
	portNVIC_SYSTICK_CTRL_REG = 0UL;
	portNVIC_SYSTICK_CURRENT_VALUE_REG = 0UL;

	/* Configure SysTick to interrupt at the requested rate. */
	portNVIC_SYSTICK_LOAD_REG = ( configSYSTICK_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
	portNVIC_SYSTICK_CTRL_REG = ( portNVIC_SYSTICK_CLK_BIT | portNVIC_SYSTICK_INT_BIT | portNVIC_SYSTICK_ENABLE_BIT );
}
/*-----------------------------------------------------------*/

/* This is a naked function. */
static void vPortEnableVFP( void )
{
	__asm volatile
	(
		"	ldr.w r0, =0xE000ED88		\n" /* The FPU enable bits are in the CPACR. */
		"	ldr r1, [r0]				\n"
		"								\n"
		"	orr r1, r1, #( 0xf << 20 )	\n" /* Enable CP10 and CP11 coprocessors, then save back. */
		"	str r1, [r0]				\n"
		"	bx r14						"
	);
}
/*-----------------------------------------------------------*/

#if( configASSERT_DEFINED == 1 )

	void vPortValidateInterruptPriority( void )
	{
	uint32_t ulCurrentInterrupt;
	uint8_t ucCurrentPriority;

		/* Obtain the number of the currently executing interrupt. */
		__asm volatile( "mrs %0, ipsr" : "=r"( ulCurrentInterrupt ) :: "memory" );

		/* Is the interrupt number a user defined interrupt? */
		if( ulCurrentInterrupt >= portFIRST_USER_INTERRUPT_NUMBER )
		{
			/* Look up the interrupt's priority. */
			ucCurrentPriority = pcInterruptPriorityRegisters[ ulCurrentInterrupt ];

			/* The following assertion will fail if a service routine (ISR) for
			an interrupt that has been assigned a priority above
			configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
			function.  ISR safe FreeRTOS API functions must *only* be called
			from interrupts that have been assigned a priority at or below
			configMAX_SYSCALL_INTERRUPT_PRIORITY.

			Numerically low interrupt priority numbers represent logically high
			interrupt priorities, therefore the priority of the interrupt must
			be set to a value equal to or numerically *higher* than
			configMAX_SYSCALL_INTERRUPT_PRIORITY.

			Interrupts that	use the FreeRTOS API must not be left at their
			default priority of	zero as that is the highest possible priority,
			which is guaranteed to be above configMAX_SYSCALL_INTERRUPT_PRIORITY,
			and	therefore also guaranteed to be invalid.

			FreeRTOS maintains separate thread and ISR API functions to ensure
			interrupt entry is as fast and simple as possible.

			The following links provide detailed information:
			http://www.freertos.org/RTOS-Cortex-M3-M4.html
			http://www.freertos.org/FAQHelp.html */
			configASSERT( ucCurrentPriority >= ucMaxSysCallPriority );
		}

		/* Priority grouping:  The interrupt controller (NVIC) allows the bits
		that define each interrupt's priority to be split between bits that
		define the interrupt's pre-emption priority bits and bits that define
		the interrupt's sub-priority.  For simplicity all bits must be defined
		to be pre-emption priority bits.  The following assertion will fail if
		this is not the case (if some bits represent a sub-priority).

		If the application only uses CMSIS libraries for interrupt
		configuration then the correct setting can be achieved on all Cortex-M
		devices by calling NVIC_SetPriorityGrouping( 0 ); before starting the
		scheduler.  Note however that some vendor specific peripheral libraries
		assume a non-zero priority group setting, in which cases using a value
		of zero will result in unpredictable behaviour. */
		configASSERT( ( portAIRCR_REG & portPRIORITY_GROUP_MASK ) <= ulMaxPRIGROUPValue );
	}

#endif /* configASSERT_DEFINED */

