#ifndef ordin_debug_h
#define ordin_debug_h

#include "chunk.h"

void        disassembleChunk        (Chunk* chunk, const char* name);
int         disassembleInstruction  (Chunk* chunk, int offset);
static int  simpleInstruction       (const char* name, int offset);
static int  one_constantInstruction (const char* name, Chunk* chunk, int offset);
#endif