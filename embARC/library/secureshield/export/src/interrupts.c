/*------------------------------------------
 * Copyright (c) 2015, Synopsys, Inc. All rights reserved.

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
 * \date 2016-02-03
 * \author Wayne Ren(Wei.Ren@synopsys.com)
--------------------------------------------- */
#undef LIB_SECURESHIELD_OVERRIDES
#include "arc_exception.h"
#include "secureshield_lib.h"


void secureshield_int_disable(uint32_t intno)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		int_disable(intno);
	} else {
		SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_DISABLE, intno);
	}
}

void secureshield_int_enable(uint32_t intno)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		int_enable(intno);
	} else {
		SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_ENABLE, intno);
	}
}

uint32_t secureshield_int_enabled(uint32_t intno)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		return int_enabled(intno);
	} else {
		return SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_ENABLED, intno);
	}
}

void secureshield_int_pri_set(uint32_t intno, int intpri)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		int_pri_set(intno,intpri);
	} else {
		SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_PRI_SET, intno, intpri);
	}
}

int32_t secureshield_int_pri_get(uint32_t intno)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		return int_pri_get(intno);
	} else {
		return SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_PRI_GET, intno);
	}
}

int32_t secureshield_int_handler_install(uint32_t intno, void* handler)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		return int_handler_install(intno, handler);
	} else {
		return SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_INSTALL, intno, handler);
	}
}

void* secureshield_int_handler_get(uint32_t intno)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		return int_handler_get(intno);
	} else {
		return (INT_HANDLER)SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_GET, intno);
	}
}

void secureshield_int_sw_trigger(uint32_t intno)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		int_sw_trigger(intno);
	} else {
		SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_SW_TRIG, intno);
	}
}

uint32_t secureshield_int_probe(uint32_t intno)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		return int_probe(intno);
	} else {
		return SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_PROBE, intno);
	}
}

void secureshield_int_level_config(uint32_t intno, uint32_t level)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		int_level_config(intno, level);
	} else {
		SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_LEVEL_CONFIG, intno, level);
	}
}

void secureshield_cpu_lock(void)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		cpu_lock();
	} else {
		SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_CPU_LOCK);
	}
}

void secureshield_cpu_unlock(void)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		cpu_lock();
	} else {
		SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_CPU_UNLOCK);
	}
}

uint32_t secureshield_cpu_lock_save(void)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		return cpu_lock_save();
	} else {
		return SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_CPU_LOCK);
	}
}

void secureshield_cpu_unlock_restore(uint32_t status)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		cpu_unlock_restore(status);
	} else {
		SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_INT_EXC, "", SECURESHIELD_INT_EXC_CPU_UNLOCK);
	}
}