/* ------------------------------------------
 * Copyright (c) 2016, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \version 2016.05
 * \date 2016-04-20
 * \author Qiang Gu(Qiang.Gu@synopsys.com)
--------------------------------------------- */

/**
 * \defgroup	EMBARC_APP_FREERTOS_KERNEL	embARC FreeRTOS Kernel Example
 * \ingroup	EMBARC_APPS_TOTAL
 * \ingroup	EMBARC_APPS_OS_FREERTOS
 * \brief	embARC Example for testing FreeRTOS task switch and interrupt/exception handling
 *
 * \details
 * ### Extra Required Tools
 *
 * ### Extra Required Peripherals
 *
 * ### Design Concept
 *     This example is designed to show the functionality of FreeRTOS.
 *
 * ### Usage Manual
 *     Test case for show how FreeRTOS is working by task switching and interrupt/exception processing.
 *     ![ScreenShot of freertos-demo under freertos](pic/images/example/emsk/emsk_freertos_demo.jpg)
 *
 * ### Extra Comments
 *
 */

/**
 * \file
 * \ingroup	EMBARC_APP_FREERTOS_KERNEL
 * \brief	main source file of the freertos demo
 */

/**
 * \addtogroup	EMBARC_APP_FREERTOS_KERNEL
 * @{
 */

#include "embARC.h"
#include "embARC_debug.h"

static void task1(void * par);
static void task2(void * par);
static void trap_exception(void *p_excinf);
static void soft_interrupt(void *p_excinf);

#ifdef INTNO_I2C0
#define SWI_INTNO		INTNO_I2C0
#else
#define SWI_INTNO		20
#endif

/**
 * \var		task1_handle
 * \brief	handle of task1
 * \details	If task handle is not used, set Null.
 */
static TaskHandle_t task1_handle = NULL;
/**
 * \var		task2_handle
 * \brief	handle of task2
 * \details	If task handle is not used, set Null.
 */
static TaskHandle_t task2_handle = NULL;

static volatile unsigned int start = 0;
static unsigned int perf_id = 0xFF;

static unsigned int t_t2_t1;
static unsigned int t_int_t1;
static unsigned int t_t1_t2;
static unsigned int t_t1_int;
static unsigned int t_int_nest;
static unsigned int t_nest_int;

/** performance timer initialization */
static void perf_init(unsigned int id)
{
	if (timer_start(id, TIMER_CTRL_NH, 0xFFFFFFFF) < 0) {
		EMBARC_PRINTF("perf timer init failed\r\n");
		while(1);
	}
	perf_id = id;
}

/** performance timer start */
static void perf_start(void)
{
	if (timer_current(perf_id, (void *)(&start)) < 0) {
		start = 0;
	}
}

/** performance timer end, and return the time passed */
static unsigned int perf_end(void)
{
	unsigned int end = 0;

	if (timer_current(perf_id, (void *)(&end)) < 0) {
		return 0;
	}

	if (start < end) {
		return (end - start);
	} else {
		return (0xFFFFFFFF - start + end);
	}
}

/**
 * \brief  call FreeRTOS API, create and start tasks
 */
int main(void)
{

	int_handler_install(SWI_INTNO, (EXC_HANDLER)soft_interrupt);
	//int_pri_set(SWI_INTNO, INT_PRI_MIN);
	int_enable(SWI_INTNO);

	exc_handler_install(EXC_NO_TRAP, trap_exception);	/*!< install the exception handler */


	if (xTaskCreate(task1, "task1", 128, (void *)1, configMAX_PRIORITIES-2, &task1_handle)
		!= pdPASS) {	/*!< FreeRTOS xTaskCreate() API function */
		EMBARC_PRINTF("create task1 error\r\n");
		return -1;
	}
	if (xTaskCreate(task2, "task2", 128, (void *)2, configMAX_PRIORITIES-1, &task2_handle)
		!= pdPASS) {	/*!< FreeRTOS xTaskCreate() API function */
		EMBARC_PRINTF("create task2 error\r\n");
		return -1;
	}

	return 0;
}


/**
 * \brief  task1 in FreeRTOS
 * \details Call vTaskDelayUntil() to execute task1 with a fixed period 1 second.
 * \param[in] *par
 */
static void task1(void * par)
{
	TickType_t xLastExecutionTime;
	xLastExecutionTime = xTaskGetTickCount();	/*!< initialize current tick */

	while(1) {
		t_t2_t1 = perf_end();
		perf_start();
		_arc_aux_write(AUX_IRQ_HINT, SWI_INTNO);	/*!< activate soft_interrupt */
		t_int_t1 = perf_end();

		vTaskDelayUntil( &xLastExecutionTime, 1000);	/*!< This task should execute exactly every 1 second. */
		perf_start();
		vTaskResume(task2_handle);
	}

}

/**
 * \brief  task2 in FreeRTOS
 * \details Print information in task2 and suspend task2.
 * \param[in] *par
 */
static void task2(void * par)
{
	perf_init(TIMER_1);
	while(1) {
		perf_start();
		vTaskSuspend(task2_handle);	/*!< suspend task2 */
		t_t1_t2 = perf_end();
		EMBARC_PRINTF("task2->task1:%d cycles\r\n",t_t2_t1);
		EMBARC_PRINTF("task1->int:%d cycles\r\n", t_t1_int);
		EMBARC_PRINTF("int->nest int:%d cycles\r\n", t_int_nest);
		EMBARC_PRINTF("nest int->int:%d cycles\r\n", t_nest_int);
		EMBARC_PRINTF("int->task1:%d cycles\r\n", t_int_t1);
		EMBARC_PRINTF("task1->task2:%d cycles\r\n",t_t1_t2);
		EMBARC_PRINTF("\r\n");
	}
}

/**
 * \brief  trap exception
 * \details Call xTaskResumeFromISR() to resume task2 that can be called from within ISR.
 * If resuming the task2 should result in a context switch, call vPortYieldFromIsr() to generate task switch request.
 * \param[in] *p_excinf
 */
static void trap_exception(void *p_excinf)
{
	// show exception frame
	t_int_nest = perf_end();
	perf_start();
}

/**
 * \brief  soft interrupt
 * \details Call trap_s instruction to raise the exception.
 * \param[in] *p_excinf
 */
static void soft_interrupt(void *p_exinf)
{
	t_t1_int = perf_end();
	perf_start();
	Asm("trap_s 1");
	t_nest_int = perf_end();
	perf_start();
}

/** @} */