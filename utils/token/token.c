#include "token.h"

#include "../../utils/exp/exp.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

inline void token_println(const Token *t) {
    printf("[ %d:%d ]    %s(%s)\n", t->line, t->col, t->type, t->value);
}

static bool _is_hash(const char *s) {
    if (strcmp(s, "#") == 0) {
        return true;
    }

    return false;
}

static bool _is_keyword(const char *s, size_t *found_idx) {
    for (size_t i = 0; i < exp_keywords_len; ++i) {
        if (strcmp(s, exp_keywords[i].val) == 0) {
            *found_idx = i;
            return true;
        }
    }

    return false;
}

static bool _is_operator(const char *s, size_t *found_idx) {
    for (size_t i = 0; i < exp_operators_len; ++i) {
        if (strcmp(s, exp_operators[i].val) == 0) {
            *found_idx = i;
            return true;
        }
    }

    return false;
}

static bool _is_delimeter(const char *s, size_t *found_idx) {
    for (size_t i = 0; i < exp_delimeters_len; ++i) {
        if (strcmp(s, exp_delimeters[i].val) == 0) {
            *found_idx = i;
            return true;
        }
    }

    return false;
}

bool is_digit(const char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }

    return false;
}

bool is_number(const char *s) {
    size_t i = 0;
    int dots_counter = 0;

    if (!strlen(s)) {
        return false;
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
            return false;
        }
    }

    if (dots_counter > 1) {
        return false;
    }

    return true;
}

static bool _is_letter(const char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return true;
    }

    return false;
}

static bool _is_identifier(const char *s) {
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

        if (!_is_letter(s[i])) {
            return false;
        }
    }

    return true;
}

void token_init(Token *t, const char *word, const int line, const int col) {
    t->line = line;
    t->col = col;

    size_t found_idx = 0;

    if (_is_hash(word)) {
        strcpy(t->type, "HASH");
        strcpy(t->value, word);
    }

    else if (_is_keyword(word, &found_idx)) {
        strcpy(t->type, exp_keywords[found_idx].tok_type_str);
        strcpy(t->value, word);
    }

    else if (_is_operator(word, &found_idx)) {
        strcpy(t->type, exp_operators[found_idx].tok_type_str);
        strcpy(t->value, word);
    }

    else if (_is_identifier(word)) {
        strcpy(t->type, "IDENTIFIER");
        strcpy(t->value, word);
    }

    else if (_is_delimeter(word, &found_idx)) {
        strcpy(t->type, exp_delimeters[found_idx].tok_type_str);
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

bool is_language_feature(const char *word) {
    size_t found_idx = 0;
    if (_is_hash(word) || _is_keyword(word, &found_idx)
        || _is_operator(word, &found_idx) || _is_delimeter(word, &found_idx)) {
        return true;
    }

    return false;
}
