#include "token_def.h"

// TODO: merge this list with the one from token.c
// static const char *token_type_names[] = {
//     // delimiters
//     [TOK_LPAREN] = "LPAREN",
//     [TOK_RPAREN] = "RPAREN",
//     [TOK_LBRACE] = "LBRACE",
//     [TOK_RBRACE] = "RBRACE",
//     [TOK_LBRACKET] = "LBRACKET",
//     [TOK_RBRACKET] = "RBRACKET",
//     [TOK_COMMA] = "COMMA",
//     [TOK_DOT] = "DOT",
//     [TOK_COLON] = "COLON",
//     [TOK_SEMICOLON] = "SEMICOLON",
//
//     // operators
//     [TOK_PLUS] = "PLUS",
//     [TOK_MINUS] = "MINUS",
//     [TOK_STAR] = "STAR",
//     [TOK_SLASH] = "SLASH",
//     [TOK_MODULO] = "MODULO",
//
//     [TOK_ASSIGN] = "ASSIGN",
//
//     [TOK_ADD_ASSIGN] = "ADD_ASSIGN",
//     [TOK_SUB_ASSIGN] = "SUB_ASSIGN",
//     [TOK_MUL_ASSIGN] = "MUL_ASSIGN",
//     [TOK_DIV_ASSIGN] = "DIV_ASSIGN",
//     [TOK_MOD_ASSIGN] = "MOD_ASSIGN",
//
//     [TOK_BIT_AND_ASSIGN] = "BIT_AND_ASSIGN",
//     [TOK_BIT_OR_ASSIGN] = "BIT_OR_ASSIGN",
//     [TOK_BIT_XOR_ASSIGN] = "BIT_XOR_ASSIGN",
//     [TOK_LSHIFT_ASSIGN] = "LSHIFT_ASSIGN",
//     [TOK_RSHIFT_ASSIGN] = "RSHIFT_ASSIGN",
//
//     [TOK_LSHIFT] = "LSHIFT",
//     [TOK_RSHIFT] = "RSHIFT",
//
//     [TOK_BIT_AND] = "BIT_AND",
//     [TOK_BIT_OR] = "BIT_OR",
//     [TOK_BIT_NOT] = "BIT_NOT",
//     [TOK_BIT_XOR] = "BIT_XOR",
//
//     [TOK_AND] = "AND",
//     [TOK_OR] = "OR",
//     [TOK_NOT] = "NOT",
//
//     [TOK_EQ] = "EQ",
//     [TOK_NOT_EQ] = "NOT_EQ",
//
//     [TOK_LESS] = "LESS",
//     [TOK_GREATER] = "GREATER",
//     [TOK_LESS_EQ] = "LESS_EQ",
//     [TOK_GREATER_EQ] = "GREATER_EQ",
//
//     [TOK_INCREMENT] = "INCREMENT",
//     [TOK_DECREMENT] = "DECREMENT",
//
//     // literals
//     [TOK_IDENTIFIER] = "IDENTIFIER",
//     [TOK_INTEGER] = "INTEGER",
//     [TOK_FLOAT] = "FLOAT",
//     [TOK_CHAR] = "CHAR",
//     [TOK_STRING] = "STRING",
//
//     // keywords
//     [TOK_KW_AUTO] = "KW_AUTO",
//     [TOK_KW_BREAK] = "KW_BREAK",
//     [TOK_KW_CASE] = "KW_CASE",
//     [TOK_KW_CHAR] = "KW_CHAR",
//     [TOK_KW_CONST] = "KW_CONST",
//     [TOK_KW_CONTINUE] = "KW_CONTINUE",
//     [TOK_KW_DEFAULT] = "KW_DEFAULT",
//     [TOK_KW_DO] = "KW_DO",
//     [TOK_KW_DOUBLE] = "KW_DOUBLE",
//     [TOK_KW_ELSE] = "KW_ELSE",
//     [TOK_KW_ENUM] = "KW_ENUM",
//     [TOK_KW_EXTERN] = "KW_EXTERN",
//     [TOK_KW_FLOAT] = "KW_FLOAT",
//     [TOK_KW_FOR] = "KW_FOR",
//     [TOK_KW_GOTO] = "KW_GOTO",
//     [TOK_KW_IF] = "KW_IF",
//     [TOK_KW_INLINE] = "KW_INLINE",
//     [TOK_KW_INT] = "KW_INT",
//     [TOK_KW_LONG] = "KW_LONG",
//     [TOK_KW_REGISTER] = "KW_REGISTER",
//     [TOK_KW_RESTRICT] = "KW_RESTRICT",
//     [TOK_KW_RETURN] = "KW_RETURN",
//     [TOK_KW_SHORT] = "KW_SHORT",
//     [TOK_KW_SIGNED] = "KW_SIGNED",
//     [TOK_KW_SIZEOF] = "KW_SIZEOF",
//     [TOK_KW_STATIC] = "KW_STATIC",
//     [TOK_KW_STRUCT] = "KW_STRUCT",
//     [TOK_KW_SWITCH] = "KW_SWITCH",
//     [TOK_KW_TYPEDEF] = "KW_TYPEDEF",
//     [TOK_KW_UNION] = "KW_UNION",
//     [TOK_KW_UNSIGNED] = "KW_UNSIGNED",
//     [TOK_KW_VOID] = "KW_VOID",
//     [TOK_KW_VOLATILE] = "KW_VOLATILE",
//     [TOK_KW_WHILE] = "KW_WHILE",
//
//     // C99/C11 keywords
//     [TOK_KW_BOOL] = "KW_BOOL",
//     [TOK_KW_COMPLEX] = "KW_COMPLEX",
//     [TOK_KW_IMAGINARY] = "KW_IMAGINARY",
//     [TOK_KW_ALIGNAS] = "KW_ALIGNAS",
//     [TOK_KW_ALIGNOF] = "KW_ALIGNOF",
//     [TOK_KW_ATOMIC] = "KW_ATOMIC",
//     [TOK_KW_GENERIC] = "KW_GENERIC",
//     [TOK_KW_NORETURN] = "KW_NORETURN",
//     [TOK_KW_STATIC_ASSERT] = "KW_STATIC_ASSERT",
//     [TOK_KW_THREAD_LOCAL] = "KW_THREAD_LOCAL",
//
//     // special tokens
//     [TOK_EOF] = "EOF",
//     [TOK_INVALID] = "INVALID",
//     [TOK_BANG] = "BANG",
//     [TOK_NUMBER] = "NUMBER",
//     [TOK_INVALID_NUMBER] = "INVALID_NUMBER",
//     [TOK_ARROW] = "ARROW",
//     [TOK_HASH] = "HASH",
// };

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
