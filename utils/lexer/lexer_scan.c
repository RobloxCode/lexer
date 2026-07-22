#include "../../utils/str_buf/str_buf.h"
#include "../../utils/token/token.h"
#include "lexer.h"

#include <stdio.h>

void handle_str(Lexer *l) {
    int chars_count = 0;

    while ((l->cur_char = fgetc(l->file)) != EOF && l->cur_char != '"') {
        strbuf_push(&l->cur_word, (char)l->cur_char);
        l->cur_char = fgetc(l->file);
        chars_count++;
    }

    strbuf_push(&l->cur_word, '"');
    l->col = chars_count;
}

int handle_number(Lexer *l) {
    int ret = 0;
    int count_dot = 0;

    int digits_count = 0;
    l->cur_char = fgetc(l->file);

    while (is_digit((char)l->cur_char) || l->cur_char == '.') {
        if (l->cur_char == '.') {
            count_dot++;
        }

        strbuf_push(&l->cur_word, (char)l->cur_char);

        l->cur_char = fgetc(l->file);
        digits_count++;
    }

    if (l->cur_char != EOF) {
        ungetc(l->cur_char, l->file);
    }

    l->col += digits_count;

    if (count_dot > 1) {
        ret = 1;
    } else {
        ret = 0;
    }

    return ret;
}

void handle_one_line_comment(Lexer *l) {
    while ((l->cur_char = fgetc(l->file)) != EOF && l->cur_char != '\n') {
        l->cur_char = fgetc(l->file);
    }

    if (l->cur_char != EOF) {
        ungetc(l->cur_char, l->file);
    }
}

void handle_multiline_comment(Lexer *l) {
    while ((l->cur_char = fgetc(l->file)) != EOF) {
        l->ahead_char = fgetc(l->file);

        if (l->cur_char == '\n') {
            l->line++;
        }

        if (l->ahead_char != EOF) {
            ungetc(l->ahead_char, l->file);
        }

        if (l->cur_char == '*' && l->ahead_char == '/') {
            l->cur_char = fgetc(l->file);
            l->line++;
            break;
        }
    }
}
