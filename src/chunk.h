#ifndef ordina_chunk_h
#define ordina_chunk_h

#include "common.h"
#include "value.h"
#include "lineinfo.h"

typedef enum {
    OP_CONSTANT,
    // OP_CONSTANT_LONG, // (not implemented) support for 24-bit constants

    OP_NIL,
    OP_TRUE,
    OP_FALSE,

    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,

    OP_NOT,

    OP_NEGATIVE,
    OP_RETURN,
} OpCode;

typedef struct {
    int         count;
    int         capacity;
    uint8_t*    code;
    LineInfo    lines;      // line number
    ValueArray  constants;

} Chunk;

void    initChunk   (Chunk* chunk);
void    freeChunk   (Chunk* chunk);
void    writeChunk  (Chunk* chunk, uint8_t byte, int line);
int     addConstant (Chunk* chunk, Value value);
void    encodeLines (Chunk* chunk);

#endif