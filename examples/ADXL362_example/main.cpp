/**
 *   @file     main.cpp
 *   @brief    Main file for the ADXL362-example project
 *   @author   Analog Devices Inc.
 *
 * For support please go to:
 * Github: https://github.com/analogdevicesinc/mbed-adi
 * Support: https://ez.analog.com/community/linux-device-drivers/microcontroller-no-os-drivers
 * Product: www.analog.com/EVAL-ADXL362-ARDZ
 * More: https://wiki.analog.com/resources/tools-software/mbed-drivers-all

 ********************************************************************************
 * Copyright 2016(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ********************************************************************************/

#include "mbed.h"
#include "ADXL362.h"
#include "Lcd.h"
#include "EVAL_ADXL362_ARDZ.h"

Serial pc(USBTX, USBRX); ///< Serial interface to the pc
Lcd lcd;
ADXL362 adxl362(D9);
EVAL_ADXL362_ARDZ adxl362_board(lcd, adxl362);

void flush_serial_buffer(void)
{
    while (pc.readable())
        pc.getc();
    return;
}

int main()
{

    adxl362_board.LCD_setup();
    adxl362_board.ADXL_setup();

    /* Infinite loop */
    while (1) {
        if(adxl362_board.ADXL_get_int()) { // ADXL362 is AWAKE ?

            adxl362_board.LCD_init_display(); // will only turn on if it's off
            wait_ms(100);
            adxl362_board.ADXL_scan_xyzt();
            adxl362_board.LCD_display_values();
            adxl362_board.LCD_display_level();

        } else {

            adxl362_board.LCD_deinit_display(); // will only turn off it it's on

        }
    }
}

