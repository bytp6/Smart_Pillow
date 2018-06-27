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
#ifndef _SECURESHIELD_BOARD_CONFIG_H_
#define _SECURESHIELD_BOARD_CONFIG_H_

/* normal rom origin and length */
#ifndef ROM_ORIGIN
#define ROM_ORIGIN 0x00000000
#endif

#ifndef ROM_LENGTH
#define ROM_LENGTH 0x20000
#endif

#define ROM_AC	SECURESHIELD_ACDEF_UTEXT

/* rom area for secureshield */
#ifndef SECURESHIELD_ROM_ORIGIN
#define SECURESHIELD_ROM_ORIGIN	0x20000
#endif

#ifndef SECURESHIELD_ROM_LENGTH
#define SECURESHIELD_ROM_LENGTH 0x20000
#endif

/* normal ram origin and length */
#ifndef RAM_ORIGIN
#define RAM_ORIGIN  0x80000000
#endif

#ifndef RAM_LENGTH
#define RAM_LENGTH  0x10000
#endif

#define RAM_AC	SECURESHIELD_ACDEF_URAM

/* ram area for secureshield */
#ifndef SECURESHIELD_RAM_ORIGIN
#define	SECURESHIELD_RAM_ORIGIN 0x80010000
#endif

#ifndef SECURESHIELD_RAM_LENGTH
#define SECURESHIELD_RAM_LENGTH 0x10000
#endif

#endif /* _SECURESHIELD_BOARD_CONFIG_H_ */
