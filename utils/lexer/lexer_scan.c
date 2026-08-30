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
        strbuf_push(&l->cur_word, l->cur);
        advance(l);
    }
}

static int handle_number(Lexer *l) {
    int count_dot = 0;

    while (is_digit(l->peek) || l->peek == '.') {
        advance(l);

        if (l->cur == '.') {
            count_dot++;
        }

        strbuf_push(&l->cur_word, l->cur);
    }

    if (l->peek == 'F' || l->peek == 'f' || l->peek == 'L' || l->peek == 'l'
        || l->peek == 'U' || l->peek == 'u' || l->peek == 'D'
        || l->peek == 'd') {
        advance(l);
        strbuf_push(&l->cur_word, l->cur);
    }

    return count_dot > 1;
}

static void handle_one_line_comment(Lexer *l) {
    while (l->cur != EOF && l->cur != '\n') {
        advance(l);
    }
}

static void handle_multiline_comment(Lexer *l) {
    while (l->cur != EOF) {
        if (l->cur == '*' && l->peek == '/') {
            advance(l);
            break;
        }

        advance(l);
    }
}

static void handle_identifier(Lexer *l) {
    while (is_digit(l->peek) || is_letter(l->peek) || l->peek == '_') {
        strbuf_push(&l->cur_word, l->cur);
        advance(l);
    }

    strbuf_push(&l->cur_word, l->cur);
}

static void emit_token(Lexer *l, Token *token) {
    TokenArr_status status = TOKENARR_OK;
    if ((status = token_arr_append(l->tokens, token)) != TOKENARR_OK) {
        fprintf(stderr, "Failed to append token, status: %d", status);
    }
}

static void scan_str(Lexer *l) {
    Token t;

    handle_str(l);
    token_init_type(&t, TOK_STRING, token_type_to_str(TOK_STRING), &l->cur_word,
                    l->line, l->col);
    emit_token(l, &t);
    strbuf_clear(&l->cur_word);

    advance(l);
}

static void scan_comment_or_op(Lexer *l) {
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
        token_init_type(&t, TOK_SLASH, "SLASH", &l->cur_word, l->line, l->col);
        emit_token(l, &t);
        strbuf_clear(&l->cur_word);
        return;
    }
}

static void scan_double_char_ops(Lexer *l) {
    Token t;
    size_t found = 0;

    strbuf_push(&l->cur_word, l->peek);

    memset(l->peek_buf, 0, sizeof l->peek_buf);

    advance(l);

    is_operator(l->cur_word.items, &found);
    token_init_type(&t, exp_operators[found].tok_type,
                    exp_operators[found].tok_type_str, &l->cur_word, l->line,
                    l->col);
    emit_token(l, &t);
    strbuf_clear(&l->cur_word);
}

static void scan_number(Lexer *l) {
    Token t;

    if (handle_number(l) == 0) {
        token_init_type(&t, TOK_NUMBER, token_type_to_str(TOK_NUMBER),
                        &l->cur_word, l->line, l->col);
        emit_token(l, &t);
        strbuf_clear(&l->cur_word);
        return;
    } else {
        token_init_type(&t, TOK_INVALID_NUMBER,
                        token_type_to_str(TOK_INVALID_NUMBER), &l->cur_word,
                        l->line, l->col);
        emit_token(l, &t);
        strbuf_clear(&l->cur_word);
        return;
    }
}

static void scan_sintax_element(Lexer *l) {
    Token t;

    token_init(&t, &l->cur_word, l->line, l->col);
    emit_token(l, &t);
    strbuf_clear(&l->cur_word);
}

static void scan_identifier(Lexer *l) {
    Token t;

    handle_identifier(l);

    size_t found = 0;
    if (is_keyword(l->cur_word.items, &found)) {
        token_init_type(&t, exp_keywords[found].tok_type,
                        exp_keywords[found].tok_type_str, &l->cur_word, l->line,
                        l->col);
    } else {
        token_init(&t, &l->cur_word, l->line, l->col);
    }

    emit_token(l, &t);
    strbuf_clear(&l->cur_word);
}

void scan_token(Lexer *l) {
    switch (l->cur) {
        case ' ':
            return;

        case '\n':
            return;

        case '\t':
            return;

        case '\r':
            return;

        case '"':
            scan_str(l);
            return;

        case '/':
            scan_comment_or_op(l);
            return;

        default:
            if (is_letter(l->cur) || l->cur == '_') {
                scan_identifier(l);
                return;
            }

            break;
    }

    strbuf_push(&l->cur_word, l->cur);
    l->peek_buf[0] = (char)l->peek;

    if (is_operator(l->cur_word.items, NULL)
        && is_operator(l->peek_buf, NULL)) {
        scan_double_char_ops(l);
        return;
    }

    if (is_digit(l->cur)) {
        scan_number(l);
        return;
    }

    if (is_reserved_token(l->cur_word.items)) {
        scan_sintax_element(l);
        return;
    }
}
