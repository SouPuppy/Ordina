
#include "lineinfo.h"

#include "memory.h"

void initLineInfo(LineInfo *lines) {
    lines->count    = 0;
    lines->capacity = 0;
    lines->data     = NULL;
}

void freeLineInfo(LineInfo *lines) {
    FREE_ARRAY(RL_element, lines->data, lines->capacity);
    initLineInfo(lines);
}

void writeLineInfo(LineInfo *lines, int line) {
    // expand capacity
    if (lines->data == NULL || lines->capacity < lines->count + 1) {
        int oldCapacity = lines->capacity;
        lines->capacity = GROW_CAPACITY(oldCapacity);
        lines->data = GROW_ARRAY(
            RL_element, 
            lines->data, 
            oldCapacity, 
            lines->capacity);
    }
    if (line == lines->data[lines->count].start_line) {
        // same line
        lines->data[lines->count].repeates++;
        return ;
    }
    // not the same line
    // add new line
    lines->data[lines->count].start_line = line;
    lines->data[lines->count].repeates = 1;
    lines->count++;
}

int getLine(LineInfo *lines, int offset) {
    int line = 0;
    for (int i = 0; i < lines->count; i++) {
        if (line + lines->data[i].repeates > offset) {
            return lines->data[i].start_line;
        }
        line += lines->data[i].repeates;
    }
    return -1;
}