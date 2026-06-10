#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_VALUE_MAX_CAP 255
#define TOKEN_TYPE_MAX_CAP  255

typedef struct {
    char type[TOKEN_TYPE_MAX_CAP];
    char value[TOKEN_VALUE_MAX_CAP];
} Token;

extern char *operators[];
extern char *delimeters[];
extern char *keywords[];

void token_init(Token *t, const char *word);
void token_print(Token t);

int is_number(const char *s);
int is_digit(const char c);
int is_language_feature(const char *word);

#endif
