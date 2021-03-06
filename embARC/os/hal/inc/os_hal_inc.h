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
 * \date 2014-08-13
 * \author Huaqi Fang(Huaqi.Fang@synopsys.com)
--------------------------------------------- */

/**
 * \defgroup	OS_HAL_INC 		OS Header File required by embARC
 * \ingroup 	OS_HAL
 * \brief 		include all os related header file, and define common interface for different os
 * @{
 *
 * \file        os_hal_inc.h
 * \brief       os hal header file
 *
 */
/**
 * @todo add comments and documents to describe the macros
 * @note the following macros must use the same name, because
 *       they are used by middleware and other applications
 */
#ifdef ENABLE_OS

/** OS_FREERTOS   */
#ifdef OS_FREERTOS
/** header files need to include */
#include "../../freertos/include/FreeRTOS.h"
#include "../../freertos/include/croutine.h"
#include "../../freertos/include/event_groups.h"
#include "../../freertos/include/list.h"
#include "../../freertos/include/mpu_wrappers.h"
#include "../../freertos/include/portable.h"
#include "../../freertos/include/projdefs.h"
#include "../../freertos/include/queue.h"
#include "../../freertos/include/semphr.h"
#include "../../freertos/include/StackMacros.h"
#include "../../freertos/include/task.h"
#include "../../freertos/include/timers.h"

#include "../../freertos/portable/Synopsys/ARC_EM/arc_freertos_exceptions.h"

/** global macros that may need */
#define os_hal_exc_init		freertos_exc_init

#endif	/* OS_FREERTOS */

/** OS_CONTIKI   */
#ifdef OS_CONTIKI
/** header files need to include */
#include "../../contiki/core/contiki.h"

/** global macros that may need */
#define os_hal_exc_init()
#endif	/* OS_CONTIKI */

#else /* NO OS */

/** global macros that may need */
#define os_hal_exc_init()

#endif 	/* ENABLE_OS */

/** @} */ /* OS_HAL_INC */
