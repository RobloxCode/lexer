#include "../../utils/str_buf/str_buf.h"
#include "../../utils/token/token.h"
#include "lexer.h"

#include <stdio.h>

void handle_str(Lexer *l) {
    int chars_count = 0;

    advance(l);

    while (l->cur != EOF && l->cur != '"') {
        strbuf_push(&l->cur_word, (char)l->cur);
        advance(l);
        chars_count++;
    }

    advance(l);

    l->col = chars_count;
}

int handle_number(Lexer *l) {
    int count_dot = 0;

    while (is_digit((char)l->peek) || l->peek == '.') {
        advance(l);

        if (l->cur == '.') {
            count_dot++;
        }

        strbuf_push(&l->cur_word, (char)l->cur);
    }

    return count_dot > 1;
}

void handle_one_line_comment(Lexer *l) {
    while (l->cur != EOF && l->cur != '\n') {
        advance(l);
    }
}

void handle_multiline_comment(Lexer *l) {
    while (l->cur != EOF) {
        if (l->cur == '\n') {
            l->line++;
        }

        if (l->cur == '*' && l->peek == '/') {
            advance(l);
            l->line++;
            break;
        }

        advance(l);
    }
}
