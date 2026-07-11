#include "token.h"

#include "../../utils/exp/exp.h"

#include <stdio.h>
#include <string.h>

void token_println(const Token *t) {
    printf("[ %d:%d ]    %s(%s)\n", t->line, t->col, t->type, t->value);
}

static int _is_hash(const char *s) {
    if (strcmp(s, "#") == 0) {
        return 1;
    }

    return 0;
}

static int _is_keyword(const char *s) {
    for (size_t i = 0; i < exp_keywords_len; ++i) {
        if (strcmp(s, exp_keywords[i].val) == 0) {
            return 1;
        }
    }

    return 0;
}

static int _is_operator(const char *s) {
    for (size_t i = 0; i < exp_operators_len; ++i) {
        if (strcmp(s, exp_operators[i].val) == 0) {
            return 1;
        }
    }

    return 0;
}

static int _is_delimeter(const char *s) {
    for (size_t i = 0; i < exp_delimeters_len; ++i) {
        if (strcmp(s, exp_delimeters[i].val) == 0) {
            return 1;
        }
    }

    return 0;
}

int is_digit(const char c) {
    if (c >= '0' && c <= '9') {
        return 1;
    }

    return 0;
}

int is_number(const char *s) {
    size_t i = 0;
    int dots_counter = 0;

    if (!strlen(s)) {
        return 0;
    }

    if (s[0] == '+' || s[0] == '-') {
        i = 1;
    }

    for (; s[i] != '\0'; ++i) {
        if (s[i] == '.') {
            dots_counter++;
            continue;
        }

        if (!is_digit(s[i])) {
            return 0;
        }
    }

    if (dots_counter > 1) {
        return 0;
    }

    return 1;
}

static int _is_letter(const char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return 1;
    }

    return 0;
}

static int _is_identifier(const char *s) {
    if (is_digit(s[0])) {
        return 0;
    }

    for (size_t i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '_') {
            continue;
        }

        if (is_digit(s[i])) {
            continue;
        }

        if (!_is_letter(s[i])) {
            return 0;
        }
    }

    return 1;
}

void token_init(Token *t, const char *word, const int line, const int col) {
    t->line = line;
    t->col = col;

    if (_is_hash(word)) {
        strcpy(t->type, "HASH");
        strcpy(t->value, word);
    }

    else if (_is_keyword(word)) {
        for (size_t i = 0; i < exp_keywords_len; ++i) {
            if (strcmp(word, exp_keywords[i].val) == 0) {
                strcpy(t->type, exp_keywords[i].tok_type_str);
                break;
            }
        }
        strcpy(t->value, word);
    }

    else if (_is_operator(word)) {
        for (size_t i = 0; i < exp_operators_len; ++i) {
            if (strcmp(word, exp_operators[i].val) == 0) {
                strcpy(t->type, exp_operators[i].tok_type_str);
                break;
            }
        }
        strcpy(t->value, word);
    }

    else if (_is_identifier(word)) {
        strcpy(t->type, "IDENTIFIER");
        strcpy(t->value, word);
    }

    else if (_is_delimeter(word)) {
        for (size_t i = 0; i < exp_delimeters_len; ++i) {
            if (strcmp(word, exp_delimeters[i].val) == 0) {
                strcpy(t->type, exp_delimeters[i].tok_type_str);
                break;
            }
        }
        strcpy(t->value, word);
    }

    else {
        strcpy(t->type, "INVALID");
        strcpy(t->value, word);
    }
}

void token_init_type(Token *t, const char *type, const char *word,
                     const int line, const int col) {
    strcpy(t->type, type);
    strcpy(t->value, word);
    t->line = line;
    t->col = col;
}

int is_language_feature(const char *word) {
    if (_is_hash(word) || _is_keyword(word) || _is_operator(word)
        || _is_delimeter(word)) {
        return 1;
    }

    return 0;
}
