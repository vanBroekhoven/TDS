/*
 * aic3204.h
 *
 *  Created on: 18 jun. 2015
 *      Author: BroJZ
 */

#ifndef AIC3204_H_
#define AIC3204_H_

void AIC3204_init(Uint32 samplingFreq, Uint16 ADCgain, Int16 DACgain);
// possible values for samplingFreq: 48000, 24000, 16000, 12000, 9600, and 8000
// range for ADCgain: 0 dB to 48 dB
// range for DACgain: -6 dB to 29 dB

void AIC3204_reset(void);

void AIC3204_waitUntilReadyToRead(void);
Int16 AIC3204_readLeft(void);
Int16 AIC3204_readRight(void);
void AIC3204_waitUntilReadyToWrite(void);
void AIC3204_writeLeft(Int16 data);
void AIC3204_writeRight(Int16 data);

#endif /* AIC3204_H_ */
