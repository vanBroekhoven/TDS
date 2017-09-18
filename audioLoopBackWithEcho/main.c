/* Demo program for TDS02
 * Copyright (C) 2015 Hogeschool Rotterdam - Harry Broeders
 * Based on a program from TI (copyright can be found at the end of this file.
 */

#include <stdio.h>
#include <usbstk5505.h>

#include "aic3204.h"

/* Setup sampling frequency, DAC gain and ADC gain */
#define SAMPLES_PER_SECOND 48000 // possible values: 48000, 24000, 16000, 12000, 9600, and 8000
#define ADC_GAIN 10 // range: 0dB to 48 dB
#define DAC_GAIN 0 // range: -6dB to 29dB
#define ECHO_DELAY 24000 // in samples
#define ECHO_DAMPENING 0.75

int dataLeft = 0;
int dataRight = 0;

int n = 0;
int samplesLeft[ECHO_DELAY] = {0};
int samplesRight[ECHO_DELAY] = {0};

int main(void) {
	// check if error in BSL is removed.
	if (sizeof(Int32) != 2) {
		printf("You forget to modify usbstk5505.h!");
		printf("Int32 is #defined to int in this file which is WRONG! Delete that line and try again.");
	}

    USBSTK5505_init(); // Initialize Board Support Library

	printf("Audio Loopback: STEREO IN ==> HP OUT\n");

	AIC3204_init(SAMPLES_PER_SECOND, ADC_GAIN, DAC_GAIN);

	while(1) {
        AIC3204_waitUntilReadyToRead();
        //sample data
        dataLeft = AIC3204_readLeft();
        dataRight = AIC3204_readRight();
        //apply dampened echo from buffer to sample.
        dataLeft = samplesLeft[n] * ECHO_DAMPENING + dataLeft;
        dataRight = samplesRight[n] * ECHO_DAMPENING + dataRight;
        //store altered sample in buffer.
        samplesLeft[n] = dataLeft;
        samplesRight[n] = dataRight;

        AIC3204_waitUntilReadyToWrite();
        //Write altered sample to dac.
        AIC3204_writeLeft(dataLeft);
        AIC3204_writeRight(dataRight);

        //apply preincrement to n, but keep it in bounds for ECHO_DELAY by applying mod.
        n = ++n % ECHO_DELAY;
	}
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
