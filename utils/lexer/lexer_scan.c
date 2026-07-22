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

int handle_number(FILE *file, int *cur_char, StrBuf *cur_word, int *col) {
    int ret = 0;
    int count_dot = 0;

    int digits_count = 0;
    *cur_char = fgetc(file);

    while (is_digit((char)*cur_char) || *cur_char == '.') {
        if (*cur_char == '.') {
            count_dot++;
        }

        strbuf_push(cur_word, (char)*cur_char);

        *cur_char = fgetc(file);
        digits_count++;
    }

    if (*cur_char != EOF) {
        ungetc(*cur_char, file);
    }

    *col += digits_count;

    if (count_dot > 1) {
        ret = 1;
    } else {
        ret = 0;
    }

    return ret;
}

void handle_one_line_comment(FILE *file, int *cur_char) {
    while ((*cur_char = fgetc(file)) != EOF && *cur_char != '\n') {
        *cur_char = fgetc(file);
    }

    if (*cur_char != EOF) {
        ungetc(*cur_char, file);
    }
}

void handle_multiline_comment(FILE *file, int *cur_char, int *ahead) {
    while ((*cur_char = fgetc(file)) != EOF) {
        *ahead = fgetc(file);

        if (*ahead != EOF) {
            ungetc(*ahead, file);
        }

        if (*cur_char == '*' && *ahead == '/') {
            *cur_char = fgetc(file);
            break;
        }
    }
}
