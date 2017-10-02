#include <stdio.h>
#include <assert.h>
#include <usbstk5505.h>
#include <usbstk5505_i2c.h>
#include <usbstk5505_i2s.h>
#include <usbstk5505_gpio.h>
#include <csl_i2s.h>

#define AIC3204_I2C_ADDR 0x18

static void AIC3204_rset(Uint16 regnum, Uint16 regval);

void AIC3204_init(Uint32 sampling_frequency, Uint16 ADCgain, Int16 DACgain) {
	/* Set A20_MODE for GPIO mode */
    // The multifunctional pin EM_A[20]/GP[26] is set to be used as general-purpose input/output pin 26 (GP[26])
    // See http://www.ti.com/lit/ug/sprugh5b/sprugh5b.pdf#page=63
    // This pin is connected to the reset input of the AIC3204 Codec
    // See http://support.spectrumdigital.com/boards/usbstk5505/revd/files/usbstk5505_Schematics_RevD.pdf#page=4
	CSL_FINST(CSL_SYSCTRL_REGS->EBSR, SYS_EBSR_A20_MODE, MODE1);

	/* Use GPIO to enable AIC3204 chip */
	assert(USBSTK5505_GPIO_init() == 0);
	assert(USBSTK5505_GPIO_setDirection(GPIO26, GPIO_OUT) == 0);
	assert(USBSTK5505_GPIO_setOutput(GPIO26, 0) == 0); // Reset AIC3204 chip
	USBSTK5505_wait(100);
	assert(USBSTK5505_GPIO_setOutput(GPIO26, 1) == 0); // Take AIC3204 chip out of reset

	/* Initialize I2C */
	assert(USBSTK5505_I2C_init() == 0);

	Uint8 PLLPR, HP_driver_gain, MICPGA_volume_control;

	if (ADCgain >= 48) {
		MICPGA_volume_control = 95; //  Limit gain to 47.5 dB
		ADCgain = 48; // For display using printf()
	} else {
		MICPGA_volume_control = (ADCgain << 1); // Convert 1dB steps to 0.5dB steps
	}

	if (DACgain > 29) {
		DACgain = 29;
	}
	if (DACgain < -6) {
		DACgain = -6;
	}
	HP_driver_gain = DACgain & 0x3f;


	switch (sampling_frequency) {
	case 48000:
		PLLPR = 0x91; // 1001 0001b. PLL on. P = 1, R = 1.
		break;
	case 24000:
		PLLPR = 0xA1; // 1010 0001b. PLL on. P = 2, R = 1.
		break;
	case 16000:
		PLLPR = 0xB1; // 1011 0001b. PLL on. P = 3, R = 1.
		break;
	case 12000:
		PLLPR = 0xC1; //1100 0001b. PLL on. P = 4, R = 1.
		break;
	case 9600:
		PLLPR = 0xD1; //1101 0001b. PLL on. P = 5, R = 1.
		break;
	case 8000:
		PLLPR = 0xE1; //1110 0001b. PLL on. P = 6, R = 1.
		break;
	default:
		sampling_frequency = 48000;
		PLLPR = 0x91; // 1001 0001b. PLL on. P = 1, R = 1.
		break;
	}
	printf("Sampling frequency %lu Hz, DAC gain = %d, ADC Gain = %d dB\n", sampling_frequency, DACgain, ADCgain);

	/* Configure AIC3204 */
	AIC3204_rset(0x00, 0x00); // Select page 0
	AIC3204_rset(0x01, 0x01); // Reset codec
	AIC3204_rset(0x00, 0x01); // Select page 1
	AIC3204_rset(0x01, 0x08); // Disable crude AVDD generation from DVDD
	AIC3204_rset(0x02, 0x01); // Enable Analog Blocks, LDO powered up

	/* PLL and Clocks config and Power Up  */
	// See http://www.ti.com/lit/ml/slaa557/slaa557.pdf#page=78
	// MCLK = 12MHz, fs=48kHz
	// PLLP = 1, PLLR = 1, PLLJ = 7, PLLD = 1680, MADC = 2, NADC = 7, AOSR = 128, MDAC = 7, NDAC = 2, DOSR = 128
	AIC3204_rset(0x00, 0x00); // Select page 0
	AIC3204_rset(0x1b, 0x0d); // BCLK and WCLK is set as output on AIC3204 (which is the bus master), 16 bits audio data
	AIC3204_rset(0x1c, 0x00); // Data offset = 0 BCLKs
	AIC3204_rset(0x04, 0x03); // PLL setting: MCLK pin is input to PLL, PLL Clock is CODEC_CLKIN
	AIC3204_rset(0x06, 0x07); // PLL setting: J = 7
	AIC3204_rset(0x07, 0x06); // PLL setting: HI_BYTE (D=1680)
	AIC3204_rset(0x08, 0x90); // PLL setting: LO_BYTE (D=1680)
	AIC3204_rset(0x1E, 0x88); // BCLK = DAC_CLK/N = (12288000/8) = 1.536MHz = 32*fs
	AIC3204_rset(0x05, PLLPR);// PLL setting: Power up PLL, P=1 and R=1
	AIC3204_rset(0x0d, 0x00); // Hi_Byte(DOSR) for DOSR = 128 decimal or 0x0080 DAC oversamppling
	AIC3204_rset(0x0e, 0x80); // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
	AIC3204_rset(0x14, 0x80); // AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6
	AIC3204_rset(0x0b, 0x82); // Power up NDAC and set NDAC value to 2
	AIC3204_rset(0x0c, 0x87); // Power up MDAC and set MDAC value to 7
	AIC3204_rset(0x12, 0x87); // Power up NADC and set NADC value to 7
	AIC3204_rset(0x13, 0x82); // Power up MADC and set MADC value to 2

	/* DAC ROUTING and Power Up */
	AIC3204_rset(0x00, 0x01); // Select page 1
	AIC3204_rset(0x0c, 0x08); // LDAC AFIR routed to HPL
	AIC3204_rset(0x0d, 0x08); // RDAC AFIR routed to HPR
	AIC3204_rset(0x00, 0x00); // Select page 0
	AIC3204_rset(0x40, 0x02); // Left vol = right vol
	AIC3204_rset(0x41, 0x00); // Left DAC gain to 0dB VOL; Right tracks Left
	AIC3204_rset(0x3f, 0xd4); // Power up left,right data paths and set channel
	AIC3204_rset(0x00, 0x01); // Select page 1
	AIC3204_rset(0x10, HP_driver_gain); // Unmute HPL , HP_driver_gain gain
	AIC3204_rset(0x11, HP_driver_gain); // Unmute HPR , HP_driver_gain gain
	AIC3204_rset(0x09, 0x30); // Power up HPL,HPR
	USBSTK5505_wait(100);

	/* ADC ROUTING and Power Up */
	AIC3204_rset(0x34, 0x30); // IN2_L to LADC_P through 40 kohm
	AIC3204_rset(0x37, 0x30); // IN2_R to RADC_P through 40 kohmm
	AIC3204_rset(0x36, 0x03); // CM_1 (common mode) to LADC_M through 40 kohm
	AIC3204_rset(0x39, 0xc0); // CM_1 (common mode) to RADC_M through 40 kohm
	AIC3204_rset(0x3b, MICPGA_volume_control); // MIC_PGA_L unmute
	AIC3204_rset(0x3c, MICPGA_volume_control); // MIC_PGA_R unmute
	AIC3204_rset(0x00, 0x00); // Select page 0
	AIC3204_rset(0x51, 0xc0); // Powerup Left and Right ADC
	AIC3204_rset(0x52, 0x00); // Unmute Left and Right ADC
	USBSTK5505_wait(100);
	/* Initialize I2S */
	assert(USBSTK5505_I2S_init() == 0);
}

void AIC3204_reset(void) {
	AIC3204_rset(0x00, 0x00); // Select page 0
	AIC3204_rset(0x01, 0x01); // Reset codec
}

extern CSL_I2sHandle hI2s;

void AIC3204_waitUntilReadyToRead(void) {
	while((CSL_I2S_I2SINTFL_RCVSTFL_MASK & hI2s->hwRegs->I2SINTFL) == 0); // Wait for receive interrupt flag to be pending
}

Int16 AIC3204_readLeft(void) {
    return hI2s->hwRegs->I2SRXLT1; // 16 bit left channel receive audio data
}

Int16 AIC3204_readRight(void) {
    return hI2s->hwRegs->I2SRXRT1; // 16 bit left channel receive audio data
}

void AIC3204_waitUntilReadyToWrite(void) {
    while((CSL_I2S_I2SINTFL_XMITSTFL_MASK & hI2s->hwRegs->I2SINTFL) == 0); // Wait for transmit interrupt flag to be pending
}

void AIC3204_writeLeft(Int16 data) {
    hI2s->hwRegs->I2STXLT1 = data; // 16 bit left channel transmit audio data
}

void AIC3204_writeRight(Int16 data) {
	hI2s->hwRegs->I2STXRT1 = data; // 16 bit left channel transmit audio data
}

static void AIC3204_rset(Uint16 regnum, Uint16 regval) {
	Uint16 cmd[2];
	cmd[0] = regnum & 0x007F; // 7-bit Device Register
	cmd[1] = regval; // 8-bit Register Data
	USBSTK5505_waitusec(300);
	assert(USBSTK5505_I2C_write(AIC3204_I2C_ADDR, (Uint16*) cmd, 2) == 0);
}
