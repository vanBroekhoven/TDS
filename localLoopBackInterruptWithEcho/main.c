/* Demo program for TDS02
 * Copyright (C) 2015 Hogeschool Rotterdam - Harry Broeders
 * Based on a program from TI (copyright can be found at the end of this file.
 */

#include <stdio.h>
#include <usbstk5505.h>
#include <usbstk5505_led.h>
#include <csl_intc.h>

#include "aic3204.h"

#define SAMPLES_PER_SECOND 48000 // possible values: 48000, 24000, 16000, 12000, 9600, and 8000
#define ADC_GAIN  10// range: 0dB to 48 dB
#define DAC_GAIN 0 // range: -6dB to 29dB
#define ECHO_DELAY 24000
#define ECHO_DAMPENING 0.5
extern void VECSTART(void);


int n = 0;
int samplesLeft[ECHO_DELAY] = {0};
int samplesRight[ECHO_DELAY] = {0};

interrupt void I2S0transmit() {

    AIC3204_writeLeft(samplesLeft[n]);
    AIC3204_writeRight(samplesLeft[n]);
}

interrupt void I2S0receive() {
    int left = AIC3204_readLeft();
    int right = AIC3204_readRight();

    samplesLeft[n] = samplesLeft[n] * ECHO_DAMPENING + left;
    samplesRight[n] = samplesRight[n] * ECHO_DAMPENING + right;

    n = ++n % ECHO_DELAY;

}

int main(void) {
    USBSTK5505_init();
    AIC3204_init(SAMPLES_PER_SECOND, ADC_GAIN, DAC_GAIN);

    IRQ_setVecs((Uint32)(&VECSTART));
    IRQ_plug(PROG0_EVENT,&I2S0transmit);
    IRQ_enable(PROG0_EVENT);
    IRQ_plug(PROG1_EVENT,&I2S0receive);
    IRQ_enable(PROG1_EVENT);
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
