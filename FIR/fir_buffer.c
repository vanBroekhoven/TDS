#include <stdlib.h>
#include "fir_buffer.h";

FIRBuffer * fir_buffer_new(int size) {
   FIRBuffer *firBuffer = (FIRBuffer *)malloc(sizeof(FIRBuffer));
   //TODO: Still have to solve potential nullpointer issues.

   firBuffer->size = size;
   firBuffer->buffer = malloc(sizeof(Int16) * size);
   firBuffer->currentBufferIndex = 0;

   return firBuffer;
}

void fir_buffer_store_sample(FIRBuffer *buffer, Int16 sample) {
    buffer->currentBufferIndex += 1;

    if(buffer->currentBufferIndex == buffer->size) {
            buffer->currentBufferIndex = 0;
    }

    buffer->buffer[buffer->currentBufferIndex] = sample;
}

Int16 fir_buffer_output_sample(FIRBuffer *buffer, const Int16 *coefficients) {
    Int32 output = 0;
    int k;
    for(k = 0; k < buffer->size; k++){
        int bufferIndex = buffer->currentBufferIndex - k;
        if(bufferIndex < 0){
            bufferIndex += buffer->size;
        }
        output += (Int32)coefficients[k] * (Int32)buffer->buffer[bufferIndex];
    }

    return((Int16)(output >> 15));
}
