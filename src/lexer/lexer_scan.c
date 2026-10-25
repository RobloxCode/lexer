#include "lexer_scan.h"

#include "lexer/token.h"
#include "lexer_internal.h"
#include "str_buf/str_buf.h"
#include "token/token_internal.h"
#include "token_def/token_def.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_LENGTH(a)      (sizeof(a) / sizeof((a)[0]))
#define STR_TOK_TYPE         "STRING"
#define NUM_TOK_TYPE         "NUMBER"
#define INVALID_NUM_TOK_TYPE "INVALID NUMBER"
#define C_LONGEST_OP_LEN     3
#define SUFFIX_MAX_LEN       8

typedef enum {
    HNS_INTEGER,
    HNS_FLOAT,
    HNS_INCORRECT_FLOAT_NUMBER,
    HNS_INCORRECT_INTEGER_SUFFIX,
    HNS_WRONG_NUMBER,
} HandleNumberStatus;

static const char *int_suffixes[] = {
    "U",   "u",  "L",  "l",  "UL",  "Ul",  "uL",  "ul",  "LU",  "Lu",  "lU",
    "ull", "lu", "LL", "ll", "ULL", "uLL", "Ull", "LLU", "LLu", "llU", "llu"};

static const char *float_suffixes[] = {"f", "F", "l", "L"};

static void _push(Lexer *l, int c) {
    if (strbuf_push(&l->cur_word, c) != 0) {
        l->overflow = true;
    }
}

static void _emit_token(Lexer *l, const Token *token) {
    TokenArrStatus status = TOKENARR_OK;

    if ((status = token_arr_append(l->tokens, token)) != TOKENARR_OK) {
        fprintf(stderr, "Failed to append token, status: %d\n", status);
    }
}

static void _emit_word(Lexer *l, TokenType type) {
    Token t;

    if (l->overflow) {
        fprintf(stderr, "%d:%d: token too long, truncated\n", l->tok_start_line,
                l->tok_start_col);
        type = TOK_INVALID;
    }

    token_init_type(&t, type, &l->cur_word, l->tok_start_line,
                    l->tok_start_col);
    _emit_token(l, &t);

    strbuf_clear(&l->cur_word);
    l->overflow = false;
}

static int _handle_str(Lexer *l) {
    lexer_advance(l);

    while (l->cur != EOF && l->cur != '"') {
        if (l->cur == '\\') {
            _push(l, l->cur);
            lexer_advance(l);
        }

        if (l->cur == EOF) {
            return 1;
        }

        _push(l, l->cur);
        lexer_advance(l);
    }

    if (l->cur == EOF) {
        return 1;
    }

    return 0;
}

static bool _is_ident_char(int c) {
    return is_letter(c) || is_digit(c) || c == '_';
}

static bool _in_list(const char *s, const char **list, const size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (strcmp(s, list[i]) == 0) {
            return true;
        }
    }

    return false;
}

static HandleNumberStatus _handle_number(Lexer *l) {
    int dots = 0;

    while (is_digit(l->peek) || l->peek == '.') {
        lexer_advance(l);

        if (l->cur == '.') {
            dots++;
        }

        _push(l, l->cur);
    }

    char suffix[SUFFIX_MAX_LEN] = {0};
    size_t suff_len = 0;

    while (_is_ident_char(l->peek)) {
        lexer_advance(l);
        _push(l, l->cur);
        if (suff_len < sizeof suffix - 1) {
            suffix[suff_len++] = (char)l->cur;
        }
    }

    if (dots > 1) {
        return HNS_INCORRECT_FLOAT_NUMBER;
    }

    if (suff_len == 0) {
        if (dots) {
            return HNS_FLOAT;
        } else {
            return HNS_INTEGER;
        }
    }

    bool suffix_in_list = false;

    if (dots == 0) {
        suffix_in_list =
            _in_list(suffix, int_suffixes, ARRAY_LENGTH(int_suffixes));
    } else {
        suffix_in_list =
            _in_list(suffix, float_suffixes, ARRAY_LENGTH(float_suffixes));
    }

    if (!suffix_in_list) {
        return HNS_INCORRECT_INTEGER_SUFFIX;
    }

    return dots ? HNS_FLOAT : HNS_INTEGER;
}

static void _handle_one_line_comment(Lexer *l) {
    while (l->cur != EOF && l->cur != '\n') {
        lexer_advance(l);
    }
}

static int _handle_multiline_comment(Lexer *l) {
    lexer_advance(l);
    lexer_advance(l);

    while (l->cur != EOF) {
        if (l->cur == '*' && l->peek == '/') {
            lexer_advance(l);
            break;
        }

        if (l->peek == EOF) {
            return 1;
        }

        lexer_advance(l);
    }

    return 0;
}

static void _handle_identifier(Lexer *l) {
    while (is_digit(l->peek) || is_letter(l->peek) || l->peek == '_') {
        _push(l, l->cur);
        lexer_advance(l);
    }

    _push(l, l->cur);
}

static void _scan_str(Lexer *l) {
    TokenType type = TOK_STRING;

    if (_handle_str(l) != 0) {
        type = TOK_INVALID_STR;
    }

    _emit_word(l, type);
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

    for (size_t i = 0; i < len; ++i) {
        _push(l, l->cur);

        if (i + 1 < len) {
            lexer_advance(l);
        }
    }

    _emit_word(l, tok_definitions[idx].tok_type);

    return true;
}

static void _scan_comment_or_op(Lexer *l) {
    if (l->peek == '/') {
        _handle_one_line_comment(l);
        return;
    }

    if (l->peek == '*') {
        if (_handle_multiline_comment(l) != 0) {
            strbuf_push_str(&l->cur_word, "/**...");
            _emit_word(l, TOK_UNTERMINATED_COMMENT);
        }

        return;
    }

    _try_scan_operator(l);
}

static void _scan_number(Lexer *l) {
    TokenType type = TOK_INVALID_NUMBER;

    HandleNumberStatus status = _handle_number(l);

    switch (status) {
        case HNS_INTEGER:
            type = TOK_INTEGER;
            break;

        case HNS_FLOAT:
            type = TOK_FLOAT;
            break;

        case HNS_INCORRECT_FLOAT_NUMBER:
            type = TOK_INVALID_NUMBER;
            break;

        case HNS_INCORRECT_INTEGER_SUFFIX:
            type = TOK_INVALID_SUFFIX;
            break;

        case HNS_WRONG_NUMBER:
            type = TOK_INVALID_NUMBER;
            break;
    }

    _emit_word(l, type);
}

static void _scan_identifier(Lexer *l) {
    _handle_identifier(l);

    size_t found = 0;
    TokenType type = TOK_IDENTIFIER;

    if (is_keyword(l->cur_word.items, &found)) {
        type = tok_definitions[found].tok_type;
    }

    _emit_word(l, type);
}

static void _scan_invalid_char(Lexer *l) {
    _push(l, l->cur);
    _emit_word(l, TOK_INVALID);
}

static int _handle_char(Lexer *l) {
    lexer_advance(l);
    size_t len = 0;

    while (l->cur != EOF && l->cur != '\'') {
        if (l->cur == '\\') {
            _push(l, l->cur);
            lexer_advance(l);
            continue;
        }

        if (l->cur == EOF) {
            return 1;
        }

        _push(l, l->cur);
        lexer_advance(l);

        len++;
    }

    if (l->cur == EOF) {
        return 1;
    }

    if (len > 1) {
        return 1;
    }

    return 0;
}

static void _scan_char(Lexer *l) {
    TokenType type = TOK_CHAR;

    if (_handle_char(l) != 0) {
        type = TOK_INVALID_CHAR;
    }

    _emit_word(l, type);
}

void scan_token(Lexer *l) {
    l->tok_start_line = l->cur_line;
    l->tok_start_col = l->cur_col;

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
        _push(l, l->cur);
        _scan_number(l);
        return;
    }

    _scan_invalid_char(l);
}
