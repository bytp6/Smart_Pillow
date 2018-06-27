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
#include "arc_builtin.h"
#include "arc_exception.h"
#include "secureshield_lib.h"


uint32_t secureshield_arc_lr_reg(uint32_t addr)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		return _arc_lr_reg(addr);
	} else {
		return SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_SYS, "", SECURESHIELD_SYS_LR, addr);
	}
}

void secureshield_arc_sr_reg(uint32_t addr, uint32_t val)
{
	if (__secureshield_mode == SECURESHIELD_DISABLED) {
		_arc_sr_reg(addr, val);
	} else {
		SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_SYS, "", SECURESHIELD_SYS_SR, addr, val);
	}
}

void secureshield_perf_config(void)
{
	SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_SYS, "", SECURESHIELD_SYS_PERF_CFG, 0);
	secureshield_perf_start();
	SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_SYS, "", SECURESHIELD_SYS_PERF_CFG, secureshield_perf_end());
}

void secureshield_perf_start(void)
{
	SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_SYS, "", SECURESHIELD_SYS_PERF_START);
}

uint32_t secureshield_perf_end(void)
{
	return SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_SYS, "", SECURESHIELD_SYS_PERF_END);
}

int32_t secureshield_container_id_self(void)
{
	return SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_SYS, "", SECURESHIELD_SYS_CONTAINER_ID_SELF);
}

int32_t secureshield_container_id_caller(void)
{
	return SECURESHIELD_MONITOR_CALL(SECURESHIELD_MONITOR_CALL_SYS, "", SECURESHIELD_SYS_CONTAINER_ID_CALLER);
}