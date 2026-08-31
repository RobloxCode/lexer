#include "token_def.h"

TokenDef exp_operators[] = {
    {"+", TOK_PLUS},           {"-", TOK_MINUS},
    {"*", TOK_STAR},           {"/", TOK_SLASH},
    {"%", TOK_MODULO},         {"=", TOK_ASSIGN},
    {"+=", TOK_ADD_ASSIGN},    {"-=", TOK_SUB_ASSIGN},
    {"*=", TOK_MUL_ASSIGN},    {"/=", TOK_DIV_ASSIGN},
    {"%=", TOK_MOD_ASSIGN},    {"&=", TOK_BIT_AND_ASSIGN},
    {"|=", TOK_BIT_OR_ASSIGN}, {"^=", TOK_BIT_XOR_ASSIGN},
    {"<<", TOK_LSHIFT},        {">>", TOK_RSHIFT},
    {"&", TOK_BIT_AND},        {"|", TOK_BIT_OR},
    {"~", TOK_BIT_NOT},        {"^", TOK_BIT_XOR},
    {"&&", TOK_AND},           {"||", TOK_OR},
    {"!=", TOK_NOT_EQ},        {"==", TOK_EQ},
    {"<", TOK_LESS},           {">", TOK_GREATER},
    {"<=", TOK_LESS_EQ},       {">=", TOK_GREATER_EQ},
    {"++", TOK_INCREMENT},     {"--", TOK_DECREMENT},
    {"!", TOK_BANG},           {"->", TOK_ARROW},
};

TokenDef exp_delimeters[] = {
    {"(", TOK_LPAREN},    {")", TOK_RPAREN},   {"{", TOK_LBRACE},
    {"}", TOK_RBRACE},    {"[", TOK_LBRACKET}, {"]", TOK_RBRACKET},
    {",", TOK_COMMA},     {".", TOK_DOT},      {":", TOK_COLON},
    {";", TOK_SEMICOLON},
};

TokenDef exp_keywords[] = {
    {"auto", TOK_KW_AUTO},
    {"break", TOK_KW_BREAK},
    {"case", TOK_KW_CASE},
    {"char", TOK_KW_CHAR},
    {"const", TOK_KW_CONST},
    {"continue", TOK_KW_CONTINUE},
    {"default", TOK_KW_DEFAULT},
    {"do", TOK_KW_DO},
    {"double", TOK_KW_DOUBLE},
    {"else", TOK_KW_ELSE},
    {"enum", TOK_KW_ENUM},
    {"extern", TOK_KW_EXTERN},
    {"float", TOK_KW_FLOAT},
    {"for", TOK_KW_FOR},
    {"goto", TOK_KW_GOTO},
    {"if", TOK_KW_IF},
    {"inline", TOK_KW_INLINE},
    {"int", TOK_KW_INT},
    {"long", TOK_KW_LONG},
    {"register", TOK_KW_REGISTER},
    {"restrict", TOK_KW_RESTRICT},
    {"return", TOK_KW_RETURN},
    {"short", TOK_KW_SHORT},
    {"signed", TOK_KW_SIGNED},
    {"sizeof", TOK_KW_SIZEOF},
    {"static", TOK_KW_STATIC},
    {"struct", TOK_KW_STRUCT},
    {"switch", TOK_KW_SWITCH},
    {"typedef", TOK_KW_TYPEDEF},
    {"union", TOK_KW_UNION},
    {"unsigned", TOK_KW_UNSIGNED},
    {"void", TOK_KW_VOID},
    {"volatile", TOK_KW_VOLATILE},
    {"while", TOK_KW_WHILE},

    // C99/C11 keywords
    {"_Bool", TOK_KW_BOOL},
    {"_Complex", TOK_KW_COMPLEX},
    {"_Imaginary", TOK_KW_IMAGINARY},
    {"_Alignas", TOK_KW_ALIGNAS},
    {"_Alignof", TOK_KW_ALIGNOF},
    {"_Atomic", TOK_KW_ATOMIC},
    {"_Generic", TOK_KW_GENERIC},
    {"_Noreturn", TOK_KW_NORETURN},
    {"_Static_assert", TOK_KW_STATIC_ASSERT},
    {"_Thread_local", TOK_KW_THREAD_LOCAL},
};

size_t exp_operators_len = sizeof exp_operators / sizeof exp_operators[0];
size_t exp_delimeters_len = sizeof exp_delimeters / sizeof exp_delimeters[0];
size_t exp_keywords_len = sizeof exp_keywords / sizeof exp_keywords[0];
