#include "lexer/token.h"

#include "str_buf/str_buf.h"
#include "token_def/token_def.h"
#include "token_internal.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool _find(const char *s, TokenCategory cat, size_t *out) {
    for (size_t i = 0; i < tok_definitions_len; ++i) {
        const TokenDef *d = &tok_definitions[i];

        if (d->lexeme && d->category == cat && strcmp(s, d->lexeme) == 0) {
            if (out) {
                *out = i;
            }
            return true;
        }
    }
    return false;
}

bool is_keyword(const char *s, size_t *idx) {
    return _find(s, CAT_KEYWORD, idx);
}

bool is_operator(const char *s, size_t *idx) {
    return _find(s, CAT_OPERATOR, idx) || _find(s, CAT_DELIMITER, idx);
}

bool is_digit(const int c) {
    return c >= '0' && c <= '9';
}

bool is_number(const char *s) {
    size_t i = 0;
    int dots_counter = 0;

    if (!strlen(s)) {
        return false;
    }

    if (s[0] == '.' || s[strlen(s) - 1] == '.') {
        return false;
    }

    if (s[0] == '+' || s[0] == '-') {
        i = 1;

        if (s[i] == '\0') {
            return false;
        }
    }

    for (; s[i] != '\0'; ++i) {
        if (s[i] == '.') {
            dots_counter++;
            continue;
        }

        if (!is_digit(s[i])) {
            return false;
        }
    }

    if (dots_counter > 1) {
        return false;
    }

    return true;
}

bool is_letter(const int c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool all_letters(const char *items, const size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (!is_letter(items[i])) {
            return false;
        }
    }

    return true;
}

void token_init_type(Token *t, TokenType type, const StrBuf *word,
                     const int line, const int col) {
    t->type = type;
    assert(STR_BUF_MAX_CAP <= TOKEN_BUF_MAX_CAP);
    strcpy(t->lexeme, word->items);
    t->line = line;
    t->col = col;
}

const char *token_type_to_str(TokenType type) {
    if (type >= tok_definitions_len
        || tok_definitions[type].display_name == NULL) {
        return "UNKNOWN";
    }

    return tok_definitions[type].display_name;
}

inline void token_println(const Token *t) {
    printf("[ %d:%d ]    %s(%s)\n", t->line, t->col, token_type_to_str(t->type),
           t->lexeme);
}
