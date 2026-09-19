#include "lexer/token/token.h"

#include "lexer/str_buf/str_buf.h"
#include "lexer/token_def/token_def.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool is_keyword(const char *s, size_t *idx) {
    for (size_t i = 0; i < tok_definitions_len; ++i) {
        if (tok_definitions[i].lexeme == NULL) {
            continue;
        }

        if (strcmp(s, tok_definitions[i].lexeme) == 0) {
            if (idx) {
                *idx = i;
            }
            return true;
        }
    }

    return false;
}

bool is_operator(const char *s, size_t *idx) {
    for (size_t i = 0; i < tok_definitions_len; ++i) {
        if (tok_definitions[i].lexeme == NULL) {
            continue;
        }

        if (strcmp(s, tok_definitions[i].lexeme) == 0) {
            if (idx) {
                *idx = i;
            }
            return true;
        }
    }

    return false;
}

static bool _is_delimiter(const char *s, size_t *idx) {
    for (size_t i = 0; i < tok_definitions_len; ++i) {
        if (tok_definitions[i].lexeme == NULL) {
            continue;
        }

        if (strcmp(s, tok_definitions[i].lexeme) == 0) {
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
        t->type = TOK_HASH;
    }

    else if (is_operator(word->items, &found)) {
        t->type = tok_definitions[found].tok_type;
    }

    else if (_is_identifier(word->items)) {
        t->type = TOK_IDENTIFIER;
    }

    else if (_is_delimiter(word->items, &found)) {
        t->type = tok_definitions[found].tok_type;
    }

    else {
        t->type = TOK_INVALID;
    }

    strcpy(t->value, word->items);
}

void token_init_type(Token *t, TokenType tok_type, const StrBuf *word,
                     const int line, const int col) {
    t->type = tok_type;
    strcpy(t->value, word->items);
    t->line = line;
    t->col = col;
}

bool is_reserved_token(const char *word) {
    if (is_operator(word, NULL) || _is_delimiter(word, NULL)) {
        return true;
    }

    return false;
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
           t->value);
}
