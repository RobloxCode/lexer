#include "str_slice.h"

#include <stddef.h>
#include <string.h>

void str_slice_init(StrSlice *sl) {
    memset(sl->items, 0, sizeof sl->items);
    sl->count = 0;
}

int str_slice_push(StrSlice *sl, char c) {
    if (sl->count >= ITEMS_MAX_CAP) {
        return 1;
    }

    sl->items[sl->count++] = c;

    return 0;
}

void str_slice_push_i(StrSlice *sl, char c, size_t i) {
    if (i >= ITEMS_MAX_CAP) {
        return;
    }

    sl->items[i] = c;
}

void str_slice_clear(StrSlice *sl) {
    for (size_t i = 0; i < ITEMS_MAX_CAP; ++i) {
        sl->items[i] = 0;
    }

    sl->count = 0;
}
