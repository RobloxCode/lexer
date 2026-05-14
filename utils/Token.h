#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_VALUE_MAX_CAP 255
#define TOKEN_TYPE_MAX_CAP  255

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_DELIMETER,
    TOKEN_STRING,
    TOKEN_CHARACTER,
    TOKEN_COMMENT,
    TOKEN_ENDOFFILE,
} TokenType;

typedef struct {
    char type[TOKEN_TYPE_MAX_CAP];
    char value[TOKEN_VALUE_MAX_CAP];
} Token;

void Token_print(Token t);
#endif
