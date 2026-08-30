#include "token.h"

#include "../../utils/exp/exp.h"
#include "../../utils/str_buf/str_buf.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

inline void token_println(const Token *t) {
    // TODO: remove the TOKTYPE
    printf("[ %d:%d ]    %s(%s) TOKTYPE: %d\n", t->line, t->col, t->type_name,
           t->value, t->tok_type);
}

bool is_keyword(const char *s, size_t *idx) {
    for (size_t i = 0; i < exp_keywords_len; ++i) {
        if (strcmp(s, exp_keywords[i].val) == 0) {
            if (idx) {
                *idx = i;
            }
            return true;
        }
    }

    return false;
}

bool is_operator(const char *s, size_t *idx) {
    for (size_t i = 0; i < exp_operators_len; ++i) {
        if (strcmp(s, exp_operators[i].val) == 0) {
            if (idx) {
                *idx = i;
            }
            return true;
        }
    }

    return false;
}

static bool _is_delimeter(const char *s, size_t *idx) {
    for (size_t i = 0; i < exp_delimeters_len; ++i) {
        if (strcmp(s, exp_delimeters[i].val) == 0) {
            if (idx) {
                *idx = i;
            }
            return true;
        }
    }

    return false;
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

static bool _is_identifier(const char *s) {
    if (s[0] == '\0') {
        return false;
    }

    if (is_digit(s[0])) {
        return false;
    }

    for (size_t i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '_') {
            continue;
        }

        if (is_digit(s[i])) {
            continue;
        }

        if (!is_letter(s[i])) {
            return false;
        }
    }

    return true;
}

void token_init(Token *t, const StrBuf *word, const int line, const int col) {
    t->line = line;
    t->col = col;

    size_t found = 0;

    if (strcmp(word->items, "#") == 0) {
        t->tok_type = TOK_HASH;
        strcpy(t->type_name, "HASH");
    }

    else if (is_operator(word->items, &found)) {
        t->tok_type = exp_operators[found].tok_type;
        strcpy(t->type_name, exp_operators[found].tok_type_str);
    }

    else if (_is_identifier(word->items)) {
        t->tok_type = TOK_IDENTIFIER;
        strcpy(t->type_name, "IDENTIFIER");
    }

    else if (_is_delimeter(word->items, &found)) {
        t->tok_type = exp_delimeters[found].tok_type;
        strcpy(t->type_name, exp_delimeters[found].tok_type_str);
    }

    else {
        t->tok_type = TOK_INVALID;
        strcpy(t->type_name, "INVALID");
    }

    strcpy(t->value, word->items);
}

void token_init_type(Token *t, TokType tok_type, const char *type,
                     const StrBuf *word, const int line, const int col) {
    t->tok_type = tok_type;
    strcpy(t->type_name, type);
    strcpy(t->value, word->items);
    t->line = line;
    t->col = col;
}

bool is_reserved_token(const char *word) {
    if (strcmp(word, "#") == 0 || is_operator(word, NULL)
        || _is_delimeter(word, NULL)) {
        return true;
    }

    return false;
}

const char *token_type_str(TokType t) {
    switch (t) {
        case TOK_STRING:
            return "STRING";

        case TOK_NUMBER:
            return "NUMBER";

        case TOK_INVALID_NUMBER:
            return "INVALID NUMBER";

        default:
            return "UNKNOWN";
    }
}
