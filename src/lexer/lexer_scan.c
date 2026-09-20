#include "lexer/lexer/lexer.h"
#include "lexer/str_buf/str_buf.h"
#include "lexer/token/token.h"
#include "lexer/token_def/token_def.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_TOK_TYPE         "STRING"
#define NUM_TOK_TYPE         "NUMBER"
#define INVALID_NUM_TOK_TYPE "INVALID NUMBER"
#define C_LONGEST_OP_LEN     3

static void _handle_str(Lexer *l) {
    advance(l);

    while (l->cur != EOF && l->cur != '"') {
        if (l->cur == '\\') {
            strbuf_push(&l->cur_word, l->cur);
            advance(l);
        }

        strbuf_push(&l->cur_word, l->cur);
        advance(l);
    }
}

static int _handle_number(Lexer *l) {
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

    return count_dot;
}

static void _handle_one_line_comment(Lexer *l) {
    while (l->cur != EOF && l->cur != '\n') {
        advance(l);
    }
}

static void _handle_multiline_comment(Lexer *l) {
    advance(l);
    advance(l);

    while (l->cur != EOF) {
        if (l->cur == '*' && l->peek == '/') {
            advance(l);
            break;
        }

        advance(l);
    }
}

static void _handle_identifier(Lexer *l) {
    while (is_digit(l->peek) || is_letter(l->peek) || l->peek == '_') {
        strbuf_push(&l->cur_word, l->cur);
        advance(l);
    }

    strbuf_push(&l->cur_word, l->cur);
}

static void _emit_token(Lexer *l, const Token *token) {
    TokenArr_status status = TOKENARR_OK;
    if ((status = token_arr_append(l->tokens, token)) != TOKENARR_OK) {
        fprintf(stderr, "Failed to append token, status: %d", status);
    }
}

static void _scan_str(Lexer *l) {
    Token t;

    _handle_str(l);
    token_init_type(&t, TOK_STRING, &l->cur_word, l->line, l->col);
    _emit_token(l, &t);
    strbuf_clear(&l->cur_word);

    advance(l);
}

static size_t _get_len_match_operator(const char *p, size_t *idx) {
    for (size_t len = C_LONGEST_OP_LEN; len > 0; --len) {
        char buf[C_LONGEST_OP_LEN + 1] = {0};
        size_t i = 0;

        while (i < len && p[i]) {
            buf[i] = p[i];
            i++;
        }

        if (i == len && is_operator(buf, idx)) {
            return len;
        }
    }

    return 0;
}

static bool _try_scan_operator(Lexer *l) {
    int look[C_LONGEST_OP_LEN] = {l->cur, l->peek, l->peek2};
    char window[C_LONGEST_OP_LEN + 1] = {0};

    for (size_t i = 0; i < C_LONGEST_OP_LEN && look[i] != EOF; ++i) {
        window[i] = (char)look[i];
    }

    size_t idx = 0;
    size_t len = _get_len_match_operator(window, &idx);

    if (len == 0) {
        return false;
    }

    int line = l->line;
    int col = l->col;

    StrBuf tok_val;
    strbuf_init(&tok_val);

    for (size_t i = 0; i < len; ++i) {
        strbuf_push(&tok_val, l->cur);

        if (i + 1 < len) {
            advance(l);
        }
    }

    Token t;
    token_init_type(&t, tok_definitions[idx].tok_type, &tok_val, line, col);
    _emit_token(l, &t);

    return true;
}

static void _scan_comment_or_op(Lexer *l) {
    if (l->peek == '/') {
        _handle_one_line_comment(l);
        return;
    }

    if (l->peek == '*') {
        _handle_multiline_comment(l);
        return;
    }

    _try_scan_operator(l);
}

static void _scan_number(Lexer *l) {
    Token t;
    TokenType type;

    int dots = _handle_number(l);

    if (dots == 0) {
        type = TOK_INTEGER;
    } else if (dots == 1) {
        type = TOK_FLOAT;
    } else {
        type = TOK_INVALID_NUMBER;
    }

    token_init_type(&t, type, &l->cur_word, l->line, l->col);
    _emit_token(l, &t);
    strbuf_clear(&l->cur_word);
}

static void _scan_identifier(Lexer *l) {
    Token t;

    _handle_identifier(l);

    size_t found = 0;
    if (is_keyword(l->cur_word.items, &found)) {
        token_init_type(&t, tok_definitions[found].tok_type, &l->cur_word,
                        l->line, l->col);
    } else {
        token_init(&t, &l->cur_word, l->line, l->col);
    }

    _emit_token(l, &t);
    strbuf_clear(&l->cur_word);
}

static void _scan_invalid_char(Lexer *l) {
    Token t;
    StrBuf word;

    strbuf_init(&word);
    strbuf_push(&word, l->cur);

    token_init_type(&t, TOK_INVALID, &word, l->line, l->col);
    _emit_token(l, &t);
}

static void _handle_char(Lexer *l) {
    advance(l);

    while (l->cur != EOF && l->cur != '\'') {
        if (l->cur == '\\') {
            strbuf_push(&l->cur_word, l->cur);
            advance(l);
        }

        strbuf_push(&l->cur_word, l->cur);
        advance(l);
    }
}

static void _scan_char(Lexer *l) {
    Token t;

    _handle_char(l);
    token_init_type(&t, TOK_CHAR, &l->cur_word, l->line, l->col);
    _emit_token(l, &t);
    strbuf_clear(&l->cur_word);

    advance(l);
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

        case '\'':
            _scan_char(l);
            return;

        case '"':
            _scan_str(l);
            return;

        // TODO: add a case for \ (\n, \"
        case '/':
            _scan_comment_or_op(l);
            return;

        default:
            if (is_letter(l->cur) || l->cur == '_') {
                _scan_identifier(l);
                return;
            }

            break;
    }

    if (_try_scan_operator(l)) {
        return;
    }

    if (is_digit(l->cur)) {
        strbuf_push(&l->cur_word, l->cur);
        _scan_number(l);
        return;
    }

    _scan_invalid_char(l);
}
