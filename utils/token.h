#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_VALUE_MAX_CAP 255
#define TOKEN_TYPE_MAX_CAP  255

typedef enum {
    // delimeters
    TOK_LPAR,
    TOK_RPAR,
    TOK_LCURL,
    TOK_RCURL,
    TOK_LBRAC,
    TOK_RBRAC,
    TOK_COMMA,
    TOK_DOT,
    TOK_COLON,
    TOK_SEMICOLON,

    // operators
    TOK_PLUS,
    TOK_SUBSBTRACT,
    TOK_MULTIPLICATION,
    TOK_DIVISION,
    TOK_MODULE,
    TOK_ASSIGN,
    TOK_ADD_ASSIGNMENT,
    TOK_SUB_ASSIGNMENT,
    TOK_MUL_ASSIGNMENT,
    TOK_DIV_ASSIGNMENT,
    TOK_MOD_ASSIGNMENT,
    TOK_BITWISE_AND_ASSIGNMENT,
    TOK_BITWISE_OR_ASSIGNMENT,
    TOK_BITWISE_NOT_ASSIGNMENT,
    TOK_BITWISE_XOR_ASSIGNMENT,
    TOK_LBITSHIFT,
    TOK_RBITSHIFT,
    TOK_BITWISE_AND,
    TOK_BITWISE_OR,
    TOK_BITWISE_NOT,
    TOK_BITWISE_XOR,
    TOK_AND,
    TOK_OR,
    TOK_NOT_EQ,
    TOK_EQ,
    TOK_LESS,
    TOK_GREATER,
    TOK_LESS_EQ,
    TOK_GREATER_EQ,
    TOK_INCREMENT,
    TOK_DECREMENT,
} TokType;

typedef struct {
    char type[TOKEN_TYPE_MAX_CAP];
    char value[TOKEN_VALUE_MAX_CAP];
} Token;

void token_init(Token *t, const char *word);
void token_print(Token t);

int is_number(const char *s);
int is_digit(const char c);
int is_language_feature(const char *word);

#endif
