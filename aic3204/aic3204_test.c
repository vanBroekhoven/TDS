//////////////////////////////////////////////////////////////////////////////
// * File name: aic3204_test.c
// *                                                                          
// * Description:  AIC3204 Test.
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

#define AIC3204_I2C_ADDR 0x18
#include "usbstk5505.h"
#include "usbstk5505_gpio.h"
#include "usbstk5505_i2c.h"
#include "stdio.h"

extern Int16 aic3204_tone_headphone( );
extern Int16 aic3204_loop_linein( );

/*
 *
 *  AIC3204_rget( regnum, *regval )
 *
 *      Return value of codec register regnum
 *
 */
Int16 AIC3204_rget(  Uint16 regnum, Uint16* regval )
{
    Int16  retcode = 0;
    Uint16 cmd[2];

    cmd[0] = regnum & 0x007F;       // 7-bit Device Register
    cmd[1] = 0;

    retcode |= USBSTK5505_I2C_write( AIC3204_I2C_ADDR, cmd, 1 );
    retcode |= USBSTK5505_I2C_read( AIC3204_I2C_ADDR, cmd, 1 );

    *regval = cmd[0];
    USBSTK5505_wait( 10 );
    return retcode;
}

/*
 *
 *  AIC3204_rset( regnum, regval )
 *
 *      Set codec register regnum to value regval
 *
 */
Int16 AIC3204_rset( Uint16 regnum, Uint16 regval )
{
    Uint16 cmd[2];
    cmd[0] = regnum & 0x007F;       // 7-bit Device Register
    cmd[1] = regval;                // 8-bit Register Data

    USBSTK5505_waitusec( 300 );

    return USBSTK5505_I2C_write( AIC3204_I2C_ADDR, cmd, 2 );
}

/*
 * 
 *  aic3204_test( )
 *
 *      Test different configurations of the AIC3204
 */
Int16 aic3204_test( )
{
     /* Set A20_MODE for GPIO mode */
    CSL_FINST(CSL_SYSCTRL_REGS->EBSR, SYS_EBSR_A20_MODE, MODE1); 
    
    /* Use GPIO to enable AIC3204 chip */
    USBSTK5505_GPIO_init();
    USBSTK5505_GPIO_setDirection(GPIO26, GPIO_OUT);
    USBSTK5505_GPIO_setOutput( GPIO26, 1 );    // Take AIC3201 chip out of reset
    
    /* Initialize I2C */
    USBSTK5505_I2C_init( );
    
    /* Codec tests */
    printf( " -> 1 KHz Tone on Headphone.\n" );
    if ( aic3204_tone_headphone( ) )           // Output test
        return 1;
        
    USBSTK5505_wait( 100 );  // Wait    
    printf( "<-> Audio Loopback from Stereo IN --> to HP OUT\n" );
    if ( aic3204_loop_linein( ) )              // Loop test
        return 3;
        
    USBSTK5505_GPIO_setOutput( GPIO26, 0 );    // Disable AIC3204
    return 0;
}
