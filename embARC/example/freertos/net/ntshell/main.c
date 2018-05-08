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
 * \defgroup	EMBARC_APP_FREERTOS_NET_NTSHELL	embARC Net Example on NT-Shell
 * \ingroup	EMBARC_APPS_TOTAL
 * \ingroup	EMBARC_APPS_OS_FREERTOS
 * \ingroup	EMBARC_APPS_MID_LWIP
 * \ingroup	EMBARC_APPS_MID_NTSHELL
 * \ingroup	EMBARC_APPS_MID_FATFS
 * \brief	embARC Example for NT-Shell on LwIP and FreeRTOS
 *
 * \details
 * ### Extra Required Tools
 *
 * ### Extra Required Peripherals
 *     * [Digilent PMOD WIFI(MRF24WG0MA)](http://www.digilentinc.com/Products/Detail.cfm?NavPath=2,401,884&Prod=PMOD-WIFI)
 *     * [Digilent PMOD TMP2](https://www.digilentinc.com/Products/Detail.cfm?NavPath=2,401,961&Prod=PMOD-TMP2)
 *
 * ### Design Concept
 *     The Pmod modules should be connected to \ref EMBARC_BOARD_CONNECTION "EMSK".
 *     This example is designed to show how to use NT-Shell over network in FreeRTOS.
 *
 * ### Usage Manual
 *     This is an example running NT-Shell command interface ver network, and use telnet to connect to it
 *     - when program is running and connected to the wifi hotspot, then you can connect your laptop to the same wifi hotspot that emsk connected to
 *     - use *telnet* command to connect to the ip address of emsk, and see the output then you can run some ntshell commands, but this is not quite stable to be used
 *
 *     ![ScreenShot of NT-Shell under FreeRTOS](/doc/documents/pic/images/example/emsk/emsk_lwip_freertos_ntshell.jpg)
 *
 * ### Extra Comments
 *
 */

/**
 * \file
 * \ingroup	EMBARC_APP_FREERTOS_NET_NTSHELL
 * \brief	main source of LwIP NT-Shell example
 */

/**
 * \addtogroup	EMBARC_APP_FREERTOS_NET_NTSHELL
 * @{
 */

#include "embARC.h"
#include "embARC_debug.h"

static TaskHandle_t net_ntshell_handle = NULL;
#define TSKPRI_NET_NTSHELL	(configMAX_PRIORITIES-3)	  /**< net ntshell task priority */

int main(void)
{
	NTSHELL_IO *nt_io;

	EMBARC_PRINTF("NT-Shell for FreeRTOS + LwIP + FatFs\r\n");
	EMBARC_PRINTF("Now please telnet to the IPAddr @ Port %d, to run ntshell ver telnet\r\n", 23);
	EMBARC_PRINTF("Command line like this: telnet ipaddr port\r\n");

	nt_io = get_ntshell_io(EMSK_NTSHELL_1_ID);
	if (net_ntshell_handle == NULL) {
		xTaskCreate(ntshell_task, "net_ntshell", 512, (void *)nt_io, TSKPRI_NET_NTSHELL, &net_ntshell_handle);
	}

	return 0;
}
/** @} */