#include "token.h"

#include <stdio.h>
#include <string.h>

#define ARRLEN(a) (sizeof a / sizeof a[0])

typedef struct {
    char *val;
    char *tok_type_str;
    TokType tok_type;
} Exp;

Exp exp_operators[] = {
    {"+", "PLUS", TOK_PLUS},
    {"-", "SUBSTRACT", TOK_SUBSBTRACT},
    {"*", "MULTIPLICATION", TOK_MULTIPLICATION},
    {"/", "DIVISION", TOK_DIVISION},
    {"%", "MODULE", TOK_MODULE},
    {"=", "ASSIGN", TOK_ASSIGN},
    {"+=", "ADD ASSIGNMENT", TOK_ADD_ASSIGNMENT},
    {"-=", "SUB ASSIGNMENT", TOK_SUB_ASSIGNMENT},
    {"*=", "MUL ASSIGNMENT", TOK_MUL_ASSIGNMENT},
    {"/=", "DIV ASSIGNMENT", TOK_DIV_ASSIGNMENT},
    {"%=", "MOD ASSIGNMENT", TOK_MOD_ASSIGNMENT},
    {"&=", "AND ASSIGNMENT", TOK_BITWISE_AND_ASSIGNMENT},
    {"|=", "OR ASSIGNMENT", TOK_BITWISE_OR_ASSIGNMENT},
    {"~=", "NOT ASSIGNMENT", TOK_BITWISE_NOT_ASSIGNMENT},
    {"^=", "XOR ASSIGNMENT", TOK_BITWISE_XOR_ASSIGNMENT},
    {"<<", "LBITSHIFT", TOK_LBITSHIFT},
    {">>", "RBITSHIFT", TOK_RBITSHIFT},
    {"&", "BITWISE AND", TOK_BITWISE_AND},
    {"|", "BITWISE OR", TOK_BITWISE_OR},
    {"~", "BITWISE NOT", TOK_BITWISE_NOT},
    {"^", "BITWISE XOR", TOK_BITWISE_XOR},
    {"&&", "AND", TOK_AND},
    {"||", "OR", TOK_OR},
    {"!=", "NOT EQUAL", TOK_NOT_EQ},
    {"==", "EQUAL", TOK_EQ},
    {"<", "LESS", TOK_LESS},
    {">", "GREATER", TOK_GREATER},
    {"<=", "LESS_EQ", TOK_LESS_EQ},
    {">=", "GREATER_EQ", TOK_GREATER_EQ},
    {"++", "INCREMENT", TOK_INCREMENT},
    {"--", "DECREMENT", TOK_DECREMENT},
};

Exp exp_delimeters[] = {
    {"(", "LPAR", TOK_LPAR},   {")", "RPAR", TOK_RPAR},
    {"{", "LCURL", TOK_LCURL}, {"}", "RCURL", TOK_RCURL},
    {"[", "LBRAC", TOK_LBRAC}, {"]", "RBRAC", TOK_RBRAC},
    {",", "COMMA", TOK_COMMA}, {".", "DOT", TOK_DOT},
    {":", "COLON", TOK_COLON}, {";", "SEMICOLON", TOK_SEMICOLON},
};

char *keywords[] = {"if",       "else",    "switch", "case",     "default",
                    "for",      "while",   "do",     "break",    "continue",
                    "goto",     "return",  "int",    "char",     "float",
                    "double",   "void",    "short",  "long",     "signed",
                    "unsigned", "_Bool",   "auto",   "register", "static",
                    "extern",   "typedef", "const",  "volatile", "restrict",
                    "struct",   "union",   "enum"};

void token_print(Token t) {
    printf("%s(%s)\n", t.type, t.value);
}

static int _is_hash(const char *s) {
    if (strcmp(s, "#") == 0) {
        return 1;
    }

    return 0;
}

static int _is_keyword(const char *s) {
    for (size_t i = 0; i < ARRLEN(keywords); ++i) {
        if (strcmp(s, keywords[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

static int _is_operator(const char *s) {
    for (size_t i = 0; i < ARRLEN(exp_operators); ++i) {
        if (strcmp(s, exp_operators[i].val) == 0) {
            return 1;
        }
    }

    return 0;
}

static int _is_delimeter(const char *s) {
    for (size_t i = 0; i < ARRLEN(exp_delimeters); ++i) {
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

void token_init(Token *t, const char *word) {
    if (_is_hash(word)) {
        strcpy(t->type, "HASH");
        strcpy(t->value, word);
    }

    else if (_is_keyword(word)) {
        strcpy(t->type, "KEYWORD");
        strcpy(t->value, word);
    }

    else if (_is_operator(word)) {
        for (size_t i = 0; i < ARRLEN(exp_operators); ++i) {
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
        for (size_t i = 0; i < ARRLEN(exp_delimeters); ++i) {
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

int is_language_feature(const char *word) {
    if (_is_hash(word) || _is_keyword(word) || _is_operator(word)
        || _is_delimeter(word)) {
        return 1;
    }

    return 0;
}
