#ifndef TOKEN_H
#define TOKEN_H

typedef struct {
    char *type;
    char *value;
} Token;

void Token_print(Token t);

#endif
