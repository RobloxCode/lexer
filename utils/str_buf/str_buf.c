#include "str_buf.h"

#include <stddef.h>
#include <string.h>

void strbuf_init(StrBuf *sb) {
    memset(sb->items, 0, sizeof sb->items);
    sb->count = 0;
}

int strbuf_push(StrBuf *sb, char c) {
    if (sb->count >= STR_BUF_MAX_CAP) {
        return 1;
    }

    sb->items[sb->count++] = c;

    return 0;
}

int strbuf_set(StrBuf *sb, char c, size_t i) {
    if (i >= STR_BUF_MAX_CAP) {
        return 1;
    }

    sb->items[i] = c;
    return 0;
}

void strbuf_clear(StrBuf *sb) {
    for (size_t i = 0; i < STR_BUF_MAX_CAP; ++i) {
        sb->items[i] = 0;
    }

    sb->count = 0;
}
