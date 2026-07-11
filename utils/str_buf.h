#ifndef STR_BUF_H
#define STR_BUF_H

#include <stddef.h>

#define STR_BUF_MAX_CAP 255

typedef struct {
    char items[STR_BUF_MAX_CAP];
    size_t count;
} StrBuf;

void strbuf_init(StrBuf *sl);
int strbuf_push(StrBuf *sl, char c);
int strbuf_set(StrBuf *sl, char c, size_t i);
void strbuf_clear(StrBuf *sl);

#endif
