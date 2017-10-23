#ifndef __IIR_BUFFER__
#define __IIR_BUFFER__

#include <csl_intc.h>

typedef struct {
    int size;
    int sections;
    Int16 *buffer;
    Int32 *outputBuffer;
    int currentBufferIndex;
} IIRBuffer;

IIRBuffer * iir_buffer_new(int size, int sections);
void iir_buffer_store_sample(IIRBuffer *buffer, Int16 sample);
Int16 iir_buffer_output_sample(IIRBuffer *buffer, const Int16 *denominator, const Int16 *numerator);

#endif//__IIR_BUFFER__
