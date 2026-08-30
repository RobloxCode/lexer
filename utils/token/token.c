#include "token.h"

#include "../../utils/exp/exp.h"
#include "../../utils/str_buf/str_buf.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
    }

    else if (is_operator(word->items, &found)) {
        t->tok_type = exp_operators[found].tok_type;
    }

    else if (_is_identifier(word->items)) {
        t->tok_type = TOK_IDENTIFIER;
    }

    else if (_is_delimeter(word->items, &found)) {
        t->tok_type = exp_delimeters[found].tok_type;
    }

    else {
        t->tok_type = TOK_INVALID;
    }

    strcpy(t->value, word->items);
}

void token_init_type(Token *t, TokType tok_type, const StrBuf *word,
                     const int line, const int col) {
    t->tok_type = tok_type;
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

static const char *token_type_names[] = {
    // delimiters
    [TOK_LPAREN] = "LPAREN",
    [TOK_RPAREN] = "RPAREN",
    [TOK_LBRACE] = "LBRACE",
    [TOK_RBRACE] = "RBRACE",
    [TOK_LBRACKET] = "LBRACKET",
    [TOK_RBRACKET] = "RBRACKET",
    [TOK_COMMA] = "COMMA",
    [TOK_DOT] = "DOT",
    [TOK_COLON] = "COLON",
    [TOK_SEMICOLON] = "SEMICOLON",

    // operators
    [TOK_PLUS] = "PLUS",
    [TOK_MINUS] = "MINUS",
    [TOK_STAR] = "STAR",
    [TOK_SLASH] = "SLASH",
    [TOK_MODULO] = "MODULO",

    [TOK_ASSIGN] = "ASSIGN",

    [TOK_ADD_ASSIGN] = "ADD_ASSIGN",
    [TOK_SUB_ASSIGN] = "SUB_ASSIGN",
    [TOK_MUL_ASSIGN] = "MUL_ASSIGN",
    [TOK_DIV_ASSIGN] = "DIV_ASSIGN",
    [TOK_MOD_ASSIGN] = "MOD_ASSIGN",

    [TOK_BIT_AND_ASSIGN] = "BIT_AND_ASSIGN",
    [TOK_BIT_OR_ASSIGN] = "BIT_OR_ASSIGN",
    [TOK_BIT_XOR_ASSIGN] = "BIT_XOR_ASSIGN",
    [TOK_LSHIFT_ASSIGN] = "LSHIFT_ASSIGN",
    [TOK_RSHIFT_ASSIGN] = "RSHIFT_ASSIGN",

    [TOK_LSHIFT] = "LSHIFT",
    [TOK_RSHIFT] = "RSHIFT",

    [TOK_BIT_AND] = "BIT_AND",
    [TOK_BIT_OR] = "BIT_OR",
    [TOK_BIT_NOT] = "BIT_NOT",
    [TOK_BIT_XOR] = "BIT_XOR",

    [TOK_AND] = "AND",
    [TOK_OR] = "OR",
    [TOK_NOT] = "NOT",

    [TOK_EQ] = "EQ",
    [TOK_NOT_EQ] = "NOT_EQ",

    [TOK_LESS] = "LESS",
    [TOK_GREATER] = "GREATER",
    [TOK_LESS_EQ] = "LESS_EQ",
    [TOK_GREATER_EQ] = "GREATER_EQ",

    [TOK_INCREMENT] = "INCREMENT",
    [TOK_DECREMENT] = "DECREMENT",

    // literals
    [TOK_IDENTIFIER] = "IDENTIFIER",
    [TOK_INTEGER] = "INTEGER",
    [TOK_FLOAT] = "FLOAT",
    [TOK_CHAR] = "CHAR",
    [TOK_STRING] = "STRING",

    // keywords
    [TOK_KW_AUTO] = "KW_AUTO",
    [TOK_KW_BREAK] = "KW_BREAK",
    [TOK_KW_CASE] = "KW_CASE",
    [TOK_KW_CHAR] = "KW_CHAR",
    [TOK_KW_CONST] = "KW_CONST",
    [TOK_KW_CONTINUE] = "KW_CONTINUE",
    [TOK_KW_DEFAULT] = "KW_DEFAULT",
    [TOK_KW_DO] = "KW_DO",
    [TOK_KW_DOUBLE] = "KW_DOUBLE",
    [TOK_KW_ELSE] = "KW_ELSE",
    [TOK_KW_ENUM] = "KW_ENUM",
    [TOK_KW_EXTERN] = "KW_EXTERN",
    [TOK_KW_FLOAT] = "KW_FLOAT",
    [TOK_KW_FOR] = "KW_FOR",
    [TOK_KW_GOTO] = "KW_GOTO",
    [TOK_KW_IF] = "KW_IF",
    [TOK_KW_INLINE] = "KW_INLINE",
    [TOK_KW_INT] = "KW_INT",
    [TOK_KW_LONG] = "KW_LONG",
    [TOK_KW_REGISTER] = "KW_REGISTER",
    [TOK_KW_RESTRICT] = "KW_RESTRICT",
    [TOK_KW_RETURN] = "KW_RETURN",
    [TOK_KW_SHORT] = "KW_SHORT",
    [TOK_KW_SIGNED] = "KW_SIGNED",
    [TOK_KW_SIZEOF] = "KW_SIZEOF",
    [TOK_KW_STATIC] = "KW_STATIC",
    [TOK_KW_STRUCT] = "KW_STRUCT",
    [TOK_KW_SWITCH] = "KW_SWITCH",
    [TOK_KW_TYPEDEF] = "KW_TYPEDEF",
    [TOK_KW_UNION] = "KW_UNION",
    [TOK_KW_UNSIGNED] = "KW_UNSIGNED",
    [TOK_KW_VOID] = "KW_VOID",
    [TOK_KW_VOLATILE] = "KW_VOLATILE",
    [TOK_KW_WHILE] = "KW_WHILE",

    // C99/C11 keywords
    [TOK_KW_BOOL] = "KW_BOOL",
    [TOK_KW_COMPLEX] = "KW_COMPLEX",
    [TOK_KW_IMAGINARY] = "KW_IMAGINARY",
    [TOK_KW_ALIGNAS] = "KW_ALIGNAS",
    [TOK_KW_ALIGNOF] = "KW_ALIGNOF",
    [TOK_KW_ATOMIC] = "KW_ATOMIC",
    [TOK_KW_GENERIC] = "KW_GENERIC",
    [TOK_KW_NORETURN] = "KW_NORETURN",
    [TOK_KW_STATIC_ASSERT] = "KW_STATIC_ASSERT",
    [TOK_KW_THREAD_LOCAL] = "KW_THREAD_LOCAL",

    // special tokens
    [TOK_EOF] = "EOF",
    [TOK_INVALID] = "INVALID",
    [TOK_BANG] = "BANG",
    [TOK_NUMBER] = "NUMBER",
    [TOK_INVALID_NUMBER] = "INVALID_NUMBER",
    [TOK_ARROW] = "ARROW",
    [TOK_HASH] = "HASH",
};

const char *token_type_to_str(TokType type) {
    size_t count = sizeof token_type_names / sizeof token_type_names[0];

    if (type < 0 || type > count || token_type_names[type] == NULL) {
        return "UNKNOWN";
    }

    return token_type_names[type];
}

inline void token_println(const Token *t) {
    printf("[ %d:%d ]    %s(%s)\n", t->line, t->col,
           token_type_to_str(t->tok_type), t->value);
}
