#ifndef __FIR_BUFFER__
#define __FIR_BUFFER__

#include <csl_intc.h>

typedef struct {
    int size;
    Int16 *buffer;
    int currentBufferIndex;
} FIRBuffer;

FIRBuffer * fir_buffer_new(int size);
void fir_buffer_store_sample(FIRBuffer *buffer, Int16 sample);
Int16 fir_buffer_output_sample(FIRBuffer *buffer, const Int16 *coefficients);

#endif//__FIR_BUFFER__
