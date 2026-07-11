#include "str_buf.h"

#include <stddef.h>
#include <string.h>

void strbuf_init(StrBuf *sl) {
    memset(sl->items, 0, sizeof sl->items);
    sl->count = 0;
}

int strbuf_push(StrBuf *sl, char c) {
    if (sl->count >= STR_BUF_MAX_CAP) {
        return 1;
    }

    sl->items[sl->count++] = c;

    return 0;
}

int strbuf_set(StrBuf *sl, char c, size_t i) {
    if (i >= STR_BUF_MAX_CAP) {
        return 1;
    }

    sl->items[i] = c;
    return 0;
}

void strbuf_clear(StrBuf *sl) {
    for (size_t i = 0; i < STR_BUF_MAX_CAP; ++i) {
        sl->items[i] = 0;
    }

    sl->count = 0;
}
