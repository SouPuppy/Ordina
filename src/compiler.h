#ifndef ordina_compiler_h
#define ordina_compiler_h

#include "object.h"
#include "vm.h"

bool compile(const char* souece, Chunk* chunk);

#endif