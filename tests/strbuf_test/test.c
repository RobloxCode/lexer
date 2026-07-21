#include "../../utils/str_buf/str_buf.h"

#include <stdio.h>

int main(void) {
    StrBuf sb;
    strbuf_init(&sb);

    strbuf_push(&sb, 'h');
    strbuf_push(&sb, 'e');
    strbuf_push(&sb, 'l');
    strbuf_push(&sb, 'l');
    strbuf_push(&sb, 'o');

    printf("items: %s\n", sb.items);

    return 0;
}
