#include "lexer/str_buf/str_buf.h"

#include <string.h>

void strbuf_init(StrBuf *sb) {
    if (!sb) {
        return;
    }

    memset(sb->items, 0, sizeof sb->items);
    sb->count = 0;
}

int strbuf_push(StrBuf *sb, const int c) {
    if (sb->count >= STR_BUF_MAX_CAP - 1) {
        return 1;
    }

    sb->items[sb->count++] = (char)c;

    return 0;
}

int strbuf_set(StrBuf *sb, char c, size_t i) {
    if (i >= STR_BUF_MAX_CAP - 1) {
        return 1;
    }

    sb->items[i] = c;
    return 0;
}

void strbuf_clear(StrBuf *sb) {
    memset(sb->items, 0, sizeof sb->items);
    sb->count = 0;
}
