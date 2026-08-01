#include "../../utils/str_buf/str_buf.h"
#include "../../utils/token/token.h"
#include "lexer.h"

#include <stdio.h>

void handle_str(Lexer *l) {
    int chars_count = 0;

    advance(l);

    while (l->cur_char != EOF && l->cur_char != '"') {
        strbuf_push(&l->cur_word, (char)l->cur_char);
        advance(l);
        chars_count++;
    }

    advance(l);

    l->col = chars_count;
}

int handle_number(Lexer *l) {
    int count_dot = 0;

    while (is_digit(l->peek_char) || l->peek_char == '.') {
        advance(l);

        if (l->cur_char == '.') {
            count_dot++;
        }

        strbuf_push(&l->cur_word, (char)l->cur_char);
    }

    return count_dot > 1;
}

void handle_one_line_comment(Lexer *l) {
    while (l->cur_char != EOF && l->cur_char != '\n') {
        advance(l);
    }
}

void handle_multiline_comment(Lexer *l) {
    while (l->cur_char != EOF) {
        if (l->cur_char == '\n') {
            l->line++;
        }

        if (l->cur_char == '*' && l->peek_char == '/') {
            advance(l);
            l->line++;
            break;
        }

        advance(l);
    }
}
