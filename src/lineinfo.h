#ifndef ordina_lineinfo_h
#define ordina_lineinfo_h

#include "common.h"

// Run-length encoding
typedef struct {
    int start_line;
    int repeates;
} RL_element;

typedef struct {
    int count;
    int capacity;
    RL_element *data;
} LineInfo;

void    initLineInfo    (LineInfo *lines);
void    writeLineInfo   (LineInfo *lines, int line);
void    freeLineInfo    (LineInfo *lines);
int     getLine         (LineInfo *lines, int offset);

#endif