#include <iir_buffer.h>
#include <stdlib.h>

IIRBuffer * iir_buffer_new(int size) {
   IIRBuffer *iirBuffer = (IIRBuffer *)malloc(sizeof(IIRBuffer));
   //TODO: Still have to solve potential nullpointer issues.

   iirBuffer->size = size;
   iirBuffer->buffer = malloc(sizeof(Int16) * size);
   iirBuffer->outputBuffer = malloc(sizeof(Int32) * size);

   int i;
   for(i = 0; i < size; i++) {
       iirBuffer->buffer[i] = 1;
       iirBuffer->outputBuffer[i] = 1;
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
    Int32 leftStage = 0;
    int k;
    for(k = 0; k < buffer->size; k++){
        int bufferIndex = buffer->currentBufferIndex - k;
        if(bufferIndex < 0){
            bufferIndex += buffer->size;
        }

        leftStage += (Int32)numerator[bufferIndex] * (Int32)buffer->buffer[bufferIndex];
    }

    Int32 rightStage = 0;
    int i;
    for(i = 1; i < buffer->size; i++) {
        int bufferIndex = buffer->currentBufferIndex - i;
        if(bufferIndex < 0){
            bufferIndex += buffer->size;
        }

        rightStage += (Int32)denominator[bufferIndex] * (Int32)buffer->outputBuffer[bufferIndex];
    }

    Int32 output = leftStage - rightStage;
    buffer->outputBuffer[buffer->currentBufferIndex] = output;
    return((Int16)(output >> 15));
}
