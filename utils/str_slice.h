#ifndef STR_SLICE_H
#define STR_SLICE_H

#include <stddef.h>

#define ITEMS_MAX_CAP 255

typedef struct {
    char items[ITEMS_MAX_CAP];
    size_t count;
} StrSlice;

void str_slice_init(StrSlice *sl);
int str_slice_push(StrSlice *sl, char c);
void str_slice_push_i(StrSlice *sl, char c, size_t i);
void str_slice_clear(StrSlice *sl);

#endif
