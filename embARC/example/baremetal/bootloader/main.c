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
 * \defgroup	EMBARC_APP_BAREMETAL_BOOTLOADER		embARC Bootloader Example
 * \ingroup	EMBARC_APPS_TOTAL
 * \ingroup	EMBARC_APPS_BAREMETAL
 * \ingroup	EMBARC_APPS_MID_NTSHELL
 * \brief	embARC example for secondary bootloader
 *
 * \details
 * ### Extra Required Tools
 *
 * ### Extra Required Peripherals
 *     - SDCard with boot binary(boot.bin)
 *
 * ### Design Concept
 *     This example is designed to work as a secondary bootloader for embARC, it will load boot.bin on SDCard and run that program.
 *
 * ### Usage Manual
 *     As shown in the following picture, when the EMSK configuration in SPI flash is loaded into the FPGA,
 *     a simple primary bootloader is also loaded in ICCM. Through the primary bootloader, the application or secondary bootloader can be
 *     loaded into ICCM or external memory (DDR memory), bootloader start address is 0x17F00004, ram address is 0x17F00000.
 *
 *     For EMSK1.x, bootloader core configuration must be arcem6, for EMSK2.x, bootloader core configuration must be arcem7d.
 *
 *     \htmlonly
 *     <div class="imagebox">
 *         <div style="width: 500px">
 *             <img src="pic/bootloader.jpg" alt="Secondary Bootloader"/>
 *             <p>Secondary Bootloader</p>
 *         </div>
 *     </div>
 *     \endhtmlonly
 *
 *     Here are steps for how to program the secondary bootloader application into onboard SPIFlash(Take EMSK2.0 - ARC EM7D as example) and automatically load and run *boot.bin* in SDCard.
 *     - Generate a secondary bootloader binary file
 *        * cd <embARC>/example/emsk/bootloader
 *        * make TOOLCHAIN=gnu BD_VER=20 CUR_CORE=arcem7d bin
 *        * If the binary file is generated successfully, you will output as follows:
 *          \code
 *          "Compiling          : " ../../../arc/arc_exception.c
 *          "Assembling         : " ../../../arc/arc_startup.s
 *          "Assembling         : " ../../../arc/arc_exc_asm.s
 *          "Archiving          : " obj_emsk_20/gnu_arcem7d/libemsk.a
 *          "Archiving          : " obj_emsk_20/gnu_arcem7d/libmidcommon.a
 *          "Archiving          : " obj_emsk_20/gnu_arcem7d/libmidfatfs.a
 *          arc-elf32-ar: creating obj_emsk_20/gnu_arcem7d/libemsk.a
 *          arc-elf32-ar: creating obj_emsk_20/gnu_aarrcc-eem7dl/fli3b2mi-dafatrf:s .ac
 *          reating obj_emsk_20/gnu_arcem7d/libmidcommon.a
 *          "Archiving          : " obj_emsk_20/gnu_arcem7d/libmidntshell.a
 *          arc-elf32-ar: creating obj_emsk_20/gnu_arcem7d/libmidntshell.a
 *          "Archiving          : " obj_emsk_20/gnu_arcem7d/libarc.a
 *          arc-elf32-ar: creating obj_emsk_20/gnu_arcem7d/libarc.a
 *          "Archiving          : " obj_emsk_20/gnu_arcem7d/libembarc.a
 *          arc-elf32-ar: creating obj_emsk_20/gnu_arcem7d/libembarc.a
 *          "Linking            : " obj_emsk_20/gnu_arcem7d/emsk_bootloader_gnu_arcem7d.elf
 *          "Generating Binary obj_emsk_20/gnu_arcem7d/emsk_bootloader_gnu_arcem7d.bin"
 *          \endcode
 *     - Program generated secondary bootloader binary file into SPIFlash
 *        * Insert SDCard to your PC, and copy the binary file *obj_emsk_20/gnu_arcem7d/emsk_bootloader_gnu_arcem7d.bin* to SDCard Root, and rename it to *em7d_2bt.bin*
 *        * Insert the SDCard to EMSK Board, and build and run the *<embARC>/example/ntshell* example, please choose the right core configuration
 *        * Then use ntshell command *spirw* to program the *em7d_2bt.bin* into spiflash.
 *            - Firstly, run *spirw* to show help
 *            - Secondly, run *spirw -i* to check SPIFlash ID, it should be **Device ID = ef4018**
 *            - Thirdly, run *spirw -w em7d_2bt.bin 0x17f00000 0x17f00004* to program spiflash
 *            - Check the output message to see if if was programmed successfully.
 *            - ![ScreenShot of program secondary bootloader to spiflash](pic/images/example/emsk/emsk_bootloader_program2splflash.jpg)
 *        * If programmed successfully, when the board is reset, make sure Bit 4 of the onboard DIP switch is ON to enable secondary bootloader run.
 *        ![ScreenShot of secondary bootloader autoboot when board configuration is reloaded](pic/images/example/emsk/emsk_bootloader_onspiflash.jpg)
 *     - Generate *boot.bin* using any embARC example which ram start address should be 0x10000000 and use bootloader to run it
 *        * Here take *<embARC>/example/freertos/demo* for example
 *        * cd <embARC>/example/freertos/demo
 *        * Build and generate binary file: *make TOOLCHAIN=gnu BD_VER=20 CUR_CORE=arcem7d bin*
 *        * Insert SDCard to PC, and copy generated binary file *obj_emsk_20/gnu_arcem7d/freertos-demo_gnu_arcem7d.bin* to SDCard Root, and rename it to boot.bin
 *        * Insert SDCard back to EMSK, make sure bit 4 of DIP Switch is ON, and press re-configure button above letter **C**, and wait for autoload.
 *        * ![ScreenShot of secondary bootloader auto load boot.bin](pic/images/example/emsk/emsk_bootloader_loadbootbin.jpg)
 *     - Know Issues
 *        * Bootrom of EMSK1.x is not able to load secondary bootloader on SPIFlash, you need a modified EMSK1.x mcs file to enable this function, please send request in forum about this mcs file.
 *
 *  **The secondary bootloader is a complement of the primary bootloader, and provides the following functions:**
 *     - File operations on SD card
 *     - Operations on the EMSK, GPIO, I2C, SPI flash
 *     - Operations on ARC processors
 *     - Automatic boot from SD card, using following instructions:
 *     	  * burn the bin file of bootloader into EMSK spi flash using spirw command <b>spirw -w bootloader.bin 0x17f00000 0x17f00004 </b> with the help of JTAG
 *     	  * the primary bootloader should be able to load the secondary bootloader
 *     	  * put the file you want to boot in the root directory of SD card, name it boot.bin
 *     	  * plug in SD card
 *     - LED Status of loading application(boot.bin)
 *        * Start to load application: LED on board -> 0x0F
 *        * Load application finished: LED on board -> 0xFF, if application is running normally, LED will quickly change to 0x0
 *        * Load application failed: LED on board -> 0xAA
 *        * Skip loading application, and enter to NTShell runtime: LED on board -> 0x0
 *     - You can refer to \ref NTSHELL_COMMAND_LIST "list of NTShell commands".
 *
 *  ![ScreenShot of bootloader under baremetal](pic/images/example/emsk/emsk_bootloader.jpg)
 *
 * ### Extra Comments
 *     Bootrom of EMSK1.x is not able to load secondary bootloader on SPIFlash,
 *     you need a modified EMSK1.x mcs file to enable this function,
 *     please send request in forum about this mcs file.
 */

/**
 * \file
 * \ingroup	EMBARC_APP_BAREMETAL_BOOTLOADER
 * \brief	example of secondary bootloader after the bootrom of EMSK
 * \todo	The ntshell is OK but boot file open error.
 */

/**
 * \addtogroup	EMBARC_APP_BAREMETAL_BOOTLOADER
 * @{
 */

#include "embARC.h"
#include "embARC_debug.h"

#include "ntshell_common.h"

#define RAM_STARTADDRESS	0x10000000		/*!< default ram start address of boot.bin */
#define BOOT_FILE_NAME		"0:\\boot.bin"          /*!< default autoload full file name */

#define PROMT_DELAY_S		(5)			/*!< default wait time for autoload */

typedef int (*fp_t)(void);

static NTSHELL_IO *nt_io;

static FIL file;

/**
 * \brief	test bootloader
 */
int main(void)
{
	uint8_t res;
	uint32_t cnt;
	void *ram;
	uint8_t load_flag = 1;
	uint32_t cur_ms = 0, cur_cnt = 0;
	uint32_t max_promt_ms = PROMT_DELAY_S * 1000;

	fp_t fp;

	/* No USE_BOARD_MAIN */
	board_init();
	cpu_unlock();	/* unlock cpu to let interrupt work */


	ram = (void *)RAM_STARTADDRESS;
	fp = (fp_t)(RAM_STARTADDRESS+4);
	EMBARC_PRINTF("\r\nPress any button on board to stop auto boot in %d s\r\n", PROMT_DELAY_S);
	cur_ms = OSP_GET_CUR_MS();
	do {
		if ((OSP_GET_CUR_MS() - cur_ms) < max_promt_ms) {
			if (((OSP_GET_CUR_MS()-cur_ms)/1000) == cur_cnt) {
				cur_cnt ++;
				EMBARC_PRINTF(". ");
			}
			/* any button pressed */
			if (button_read(BOARD_BTN_MASK)) {
				load_flag = 0;
			}
		} else {
			EMBARC_PRINTF("\r\nStart loading %s from sdcard to 0x%x and run...\r\n", BOOT_FILE_NAME, RAM_STARTADDRESS);
			led_write(0xF, 0xFF); /* Start to load application */
			res = f_open(&file, BOOT_FILE_NAME, FA_READ | FA_OPEN_EXISTING);
			if (res) {
				EMBARC_PRINTF("boot file open error\r\n");
				break;
			}
			res = f_read(&file, ram, file.fsize, &cnt);
			f_close(&file);
			if (res || ((uint32_t)cnt != file.fsize))
			{
				EMBARC_PRINTF("boot file read error\r\n");
				break;
			}
			led_write(0xF0, 0xFF); /* Load application finished */

			cpu_lock();

			for (int i = NUM_EXC_CPU; i < NUM_EXC_ALL; i++) {
				int_disable(i);
			}
			/* set up an enviroment for application */
			if ((_arc_aux_read(AUX_BCR_I_CACHE) & 0x7) >= 0x2) {
				//icache_invalidate();
			}
			if ((_arc_aux_read(AUX_BCR_D_CACHE) & 0x7) >= 0x2) {
				//dcache_flush();
				dcache_invalidate();
			}
			led_write(0xFF, 0xFF); /* Start application */

			fp();	/* jump to program */
		}
	} while(load_flag);
	if (load_flag == 1) {
		led_write(0xAA, 0xFF); /* Load application failed */
		EMBARC_PRINTF("Auto boot failed\r\n");
	}
	EMBARC_PRINTF("\r\nStart NTShell Runtime...\r\n");

	nt_io = get_ntshell_io(BOARD_ONBOARD_NTSHELL_ID);
	/** enter ntshell command routine no return */
	ntshell_task((void *)nt_io);

	return E_SYS;
}

/** @} */
