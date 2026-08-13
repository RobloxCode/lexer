#include "../../utils/str_buf/str_buf.h"
#include "../../utils/token/token.h"
#include "../exp/exp.h"
#include "../str_buf/str_buf.h"
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_TOK_TYPE         "STRING"
#define NUM_TOK_TYPE         "NUMBER"
#define INVALID_NUM_TOK_TYPE "INVALID NUMBER"

static void handle_str(Lexer *l) {
    advance(l);

    while (l->cur != EOF && l->cur != '"') {
        strbuf_push(&l->cur_word, (char)l->cur);
        advance(l);
    }
}

static int handle_number(Lexer *l) {
    int count_dot = 0;

    while (is_digit((char)l->peek) || l->peek == '.') {
        advance(l);

        if (l->cur == '.') {
            count_dot++;
        }

        strbuf_push(&l->cur_word, (char)l->cur);
    }

    if (l->peek == 'F' || l->peek == 'f' || l->peek == 'L' || l->peek == 'l'
        || l->peek == 'U' || l->peek == 'u' || l->peek == 'D'
        || l->peek == 'd') {
        advance(l);
        strbuf_push(&l->cur_word, (char)l->cur);
    }

    return count_dot > 1;
}

static void handle_one_line_comment(Lexer *l) {
    while (l->cur != EOF && l->cur != '\n') {
        advance(l);
    }
    l->line++;
}

static void handle_multiline_comment(Lexer *l) {
    while (l->cur != EOF) {
        if (l->cur == '\n') {
            l->line++;
        }

        if (l->cur == '*' && l->peek == '/') {
            advance(l);
            break;
        }

        advance(l);
    }
}

static void emit_token(Lexer *l, Token *token) {
    token_arr_append(l->tokens, token);
}

void scan_str(Lexer *l) {
    Token t;

    handle_str(l);
    token_init_type(&t, token_type_str(TOK_STRING), &l->cur_word, l->line,
                    l->col);
    emit_token(l, &t);
    strbuf_clear(&l->cur_word);
}

void scan_comment_or_op(Lexer *l) {
    Token t;

    if (l->peek == '/') {
        handle_one_line_comment(l);
        strbuf_clear(&l->cur_word);
        return;
    }

    if (l->peek == '*') {
        handle_multiline_comment(l);
        strbuf_clear(&l->cur_word);
        return;
    } else {
        strbuf_push(&l->cur_word, '/');
        token_init_type(&t, "SLASH", &l->cur_word, l->line, l->col);
        emit_token(l, &t);
        strbuf_clear(&l->cur_word);
        return;
    }
}

void scan_double_char_ops(Lexer *l) {
    Token t;
    size_t idx = 0;

    strbuf_push(&l->cur_word, (char)l->peek);

    memset(l->peek_buf, 0, sizeof l->peek_buf);

    advance(l);

    is_operator(l->cur_word.items, &idx);
    token_init_type(&t, exp_operators[idx].tok_type_str, &l->cur_word, l->line,
                    l->col);
    emit_token(l, &t);
    strbuf_clear(&l->cur_word);
}

void scan_number(Lexer *l) {
    Token t;

    if (handle_number(l) == 0) {
        token_init_type(&t, token_type_str(TOK_NUMBER), &l->cur_word, l->line,
                        l->col);
        emit_token(l, &t);
        strbuf_clear(&l->cur_word);
        return;
    } else {
        token_init_type(&t, token_type_str(TOK_INVALID_NUMBER), &l->cur_word,
                        l->line, l->col);
        emit_token(l, &t);
        strbuf_clear(&l->cur_word);
        return;
    }
}

void scan_sintax_element(Lexer *l) {
    Token t;

    token_init(&t, &l->cur_word, l->line, l->col);
    emit_token(l, &t);
    strbuf_clear(&l->cur_word);
}

static void handle_identifier(Lexer *l) {
    while (is_digit((char)l->cur) || is_letter((char)l->cur)
           || (char)l->cur == '_') {
        strbuf_push(&l->cur_word, (char)l->cur);
        advance(l);
    }
}

static void scan_identifier(Lexer *l) {
    Token t;

    handle_identifier(l);

    token_init(&t, &l->cur_word, l->line, l->col);

    emit_token(l, &t);
    strbuf_clear(&l->cur_word);
}

void scan_token(Lexer *l) {
    switch (l->cur) {
        case ' ':
            return;

        case '\n':
            l->line++;
            l->col = 0;
            return;

        case '"':
            scan_str(l);
            return;

        case '/':
            scan_comment_or_op(l);
            return;

        default:
            if (is_letter((char)l->cur) || (char)l->cur == '_') {
                scan_identifier(l);
                return;
            }

            break;
    }

    strbuf_push(&l->cur_word, (char)l->cur);
    l->peek_buf[0] = (char)l->peek;

    if (is_operator(l->cur_word.items, NULL)
        && is_operator(l->peek_buf, NULL)) {
        scan_double_char_ops(l);
        return;
    }

    if (is_digit((char)l->cur)) {
        scan_number(l);
        return;
    }

    if (is_sintax_element(l->cur_word.items)) {
        scan_sintax_element(l);
        return;
    }

    if (l->peek == ' ') {
        scan_sintax_element(l);
        return;
    }
}
