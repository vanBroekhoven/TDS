/* Demo program for TDS02
 * Copyright (C) 2015 Hogeschool Rotterdam - Harry Broeders
 * Based on a program from TI (copyright can be found at the end of this file.
 */

#include <stdio.h>
#include <usbstk5505.h>
#include <usbstk5505_led.h>
#include <csl_intc.h>

#include "aic3204.h"

#define SAMPLES_PER_SECOND 8000 // possible values: 48000, 24000, 16000, 12000, 9600, and 8000
#define ADC_GAIN 0 // range: 0dB to 48 dB
#define DAC_GAIN 0 // range: -6dB to 29dB

extern void VECSTART(void);




interrupt void I2S0transmit() {

    static size_t n = 0;
    static Int16 data = 30000;
    AIC3204_writeLeft(data >> 1);
    AIC3204_writeRight(-data);
    n++;
    if (n == 24) {
        data = -data;
        n = 0;
    }
}

int main(void) {
    USBSTK5505_init();
    AIC3204_init(SAMPLES_PER_SECOND, ADC_GAIN, DAC_GAIN);

    IRQ_setVecs((Uint32)(&VECSTART));
    IRQ_plug(PROG0_EVENT,&I2S0transmit);
    IRQ_enable(PROG0_EVENT);
    IRQ_globalEnable();

    while(1);
}

//////////////////////////////////////////////////////////////////////////////
// *
// * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2010 Spectrum Digital, Incorporated
// *
// *
// *  Redistribution and use in source and binary forms, with or without
// *  modification, are permitted provided that the following conditions
// *  are met:
// *
// *    Redistributions of source code must retain the above copyright
// *    notice, this list of conditions and the following disclaimer.
// *
// *    Redistributions in binary form must reproduce the above copyright
// *    notice, this list of conditions and the following disclaimer in the
// *    documentation and/or other materials provided with the
// *    distribution.
// *
// *    Neither the name of Texas Instruments Incorporated nor the names of
// *    its contributors may be used to endorse or promote products derived
// *    from this software without specific prior written permission.
// *
// *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
//////////////////////////////////////////////////////////////////////////////
