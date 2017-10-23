#include <iir_buffer.h>
#include <stdlib.h>

Int32 direct_form_1(IIRBuffer *buffer, Int32 input, const Int16 *denominator, const Int16 *numerator) {
    Int32 output = input;
    int k;
    for(k = 0; k < buffer->size; k++){
        int bufferIndex = buffer->currentBufferIndex - k;
        if(bufferIndex < 0){
            bufferIndex += buffer->size;
        }

        output += (Int32)numerator[k] * (Int32)buffer->buffer[bufferIndex];
    }

    int i;
    for(i = 1; i < buffer->size; i++) {
        int bufferIndex = buffer->currentBufferIndex - i;
        if(bufferIndex < 0){
            bufferIndex += buffer->size;
        }

        output -= (Int32)denominator[i] * (Int32)buffer->outputBuffer[bufferIndex];
    }
    return output;
}

IIRBuffer * iir_buffer_new(int size, int sections) {
   IIRBuffer *iirBuffer = (IIRBuffer *)malloc(sizeof(IIRBuffer));
   //TODO: Still have to solve potential nullpointer issues.

   iirBuffer->size = size;
   iirBuffer->sections = sections;
   iirBuffer->buffer = malloc(sizeof(Int16) * size);
   iirBuffer->outputBuffer = malloc(sizeof(Int32) * size);

   int i;
   for(i = 0; i < size; i++) {
       iirBuffer->buffer[i] = 0;
       iirBuffer->outputBuffer[i] = 0;
   }

   iirBuffer->currentBufferIndex = 0;

   return iirBuffer;
}

void iir_buffer_store_sample(IIRBuffer *buffer, Int16 sample) {
    buffer->currentBufferIndex += 1;

    if(buffer->currentBufferIndex == buffer->size) {
            buffer->currentBufferIndex = 0;
    }

    buffer->buffer[buffer->currentBufferIndex] = sample;
}

Int16 iir_buffer_output_sample(IIRBuffer *buffer, const Int16 *denominator, const Int16 *numerator) {
    Int32 output = 0;

    output += direct_form_1(buffer, output, denominator, numerator);

    buffer->outputBuffer[buffer->currentBufferIndex] = output >> 13;
    return((Int16)(output>>13));
}
