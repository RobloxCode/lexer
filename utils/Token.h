#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_VALUE_MAX_CAP 255
#define TOKEN_TYPE_MAX_CAP  255

typedef struct {
    char type[TOKEN_TYPE_MAX_CAP];
    char value[TOKEN_VALUE_MAX_CAP];
} Token;

void Token_print(Token t);
#endif
