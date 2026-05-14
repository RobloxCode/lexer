#include "Token.h"
#include <stdio.h>
#include <string.h>

char *operators[] = {
    "+", "-", "*", "/", "%", "=",
    "+=", "-=", "*=", "/=", "%=", "&=", "|=", "~=", "^=",
    "<<", ">>", "&", "|", "~", "^",
    "&&", "||", "!=", "==", "<", ">", "<=", ">=",
    "++", "--",
};

char delimeters[] = "(){}[],;";

char *keywords[] = {
    "if", "else", "switch", "case", "default",
    "for", "while", "do", "break", "continue",
    "goto", "return",
    "int", "char", "float", "double", "void",
    "short", "long", "signed", "unsigned", "_Bool",
    "auto", "register", "static", "extern", "typedef",
    "const", "volatile", "restrict",
    "struct", "union", "enum"
};

void Token_print(Token t)
{
    printf("%s(%s)\n", t.type, t.value);
}

int is_keyword(const char *s)
{
    for (size_t i = 0; i < sizeof keywords / sizeof keywords[0]; ++i)
        if (strcmp(s, keywords[i]) == 0)
            return 1;

    return 0;
}

int is_operator(const char *s)
{
    for (size_t i = 0; i < sizeof operators / sizeof operators[0]; ++i)
        if (strcmp(s, operators[i]) == 0)
            return 1;

    return 0;
}

static int _is_digit(const char c)
{
    if (c >= '0' && c <= '9')
        return 1;

    return 0;
}

int is_number(const char *s)
{
    size_t i = 0;
    int dots_counter = 0;

    if (s[0] == '+' || s[0] == '-')
        i = 1;

    for (; s[i] != '\0'; ++i) {
        if (s[i] == '.') {
            dots_counter++;
            continue;
        }

        if (!_is_digit(s[i]))
            return 0;
    }

    if (dots_counter > 1)
        return 0;

    return 1;
}

static int _is_letter(const char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return 1;

    return 0;
}

int is_identifier(const char *s)
{
    if (_is_digit(s[0]))
        return 0;

    for (size_t i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '_')
            continue;

        if (_is_digit(s[i]))
            continue;

        if (!_is_letter(s[i]))
            return 0;
    }

    return 1;
}

int is_delimeter(const char *s)
{
    if (strcmp(s, "{") == 0) return 1;
    if (strcmp(s, "}") == 0) return 1;
    if (strcmp(s, "(") == 0) return 1;
    if (strcmp(s, ")") == 0) return 1;
    if (strcmp(s, "[") == 0) return 1;
    if (strcmp(s, "]") == 0) return 1;
    if (strcmp(s, ",") == 0) return 1;
    if (strcmp(s, ".") == 0) return 1;
    if (strcmp(s, ";") == 0) return 1;
    if (strcmp(s, ":") == 0) return 1;

    return 0;
}
