#include "str_buf.h"

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

int strbuf_set(StrBuf *sb, const char c, const size_t i) {
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

int strbuf_push_str(StrBuf *sb, const char *s) {
    if (!sb || !s || strlen(s) > STR_BUF_MAX_CAP) {
        return 1;
    }

    for (size_t i = 0; s[i] != '\0'; ++i) {
        strbuf_push(sb, s[i]);
    }

    return 0;
}
