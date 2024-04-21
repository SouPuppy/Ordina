#include <stdlib.h>

#include "chunk.h"
#include "lineinfo.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk* chunk) {
    chunk->count      = 0;
    chunk->capacity   = 0;
    chunk->code       = NULL;
    initLineInfo(&chunk->lines);
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeLineInfo(&chunk->lines);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        // not enough capacity for new data
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code     = GROW_ARRAY(
            uint8_t, 
            chunk->code,
            oldCapacity, 
            chunk->capacity);
    }
    // append byte to chunk
    chunk->code[chunk->count] = byte;
    writeLineInfo(&chunk->lines, line);
    chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void encodeLines(Chunk *chunk) {

}