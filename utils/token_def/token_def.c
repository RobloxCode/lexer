#include "token_def.h"

const TokenDef tok_definitions[] = {
    // delimiters
    [TOK_LPAREN] = {"LPAREN", "(", TOK_LPAREN},
    [TOK_RPAREN] = {"RPAREN", ")", TOK_RPAREN},
    [TOK_LBRACE] = {"LBRACE", "{", TOK_LBRACE},
    [TOK_RBRACE] = {"RBRACE", "}", TOK_RBRACE},
    [TOK_LBRACKET] = {"LBRACKET", "[", TOK_LBRACKET},
    [TOK_RBRACKET] = {"RBRACKET", "]", TOK_RBRACKET},
    [TOK_COMMA] = {"COMMA", ",", TOK_COMMA},
    [TOK_DOT] = {"DOT", ".", TOK_DOT},
    [TOK_COLON] = {"COLON", ":", TOK_COLON},
    [TOK_SEMICOLON] = {"SEMICOLON", ";", TOK_SEMICOLON},

    // operators
    [TOK_PLUS] = {"PLUS", "+", TOK_PLUS},
    [TOK_MINUS] = {"MINUS", "-", TOK_MINUS},
    [TOK_STAR] = {"STAR", "*", TOK_STAR},
    [TOK_SLASH] = {"SLASH", "/", TOK_SLASH},
    [TOK_MODULO] = {"MODULO", "%", TOK_MODULO},

    [TOK_ASSIGN] = {"ASSIGN", "=", TOK_ASSIGN},

    [TOK_ADD_ASSIGN] = {"ADD_ASSIGN", "+=", TOK_ADD_ASSIGN},
    [TOK_SUB_ASSIGN] = {"SUB_ASSIGN", "-=", TOK_SUB_ASSIGN},
    [TOK_MUL_ASSIGN] = {"MUL_ASSIGN", "*=", TOK_MUL_ASSIGN},
    [TOK_DIV_ASSIGN] = {"DIV_ASSIGN", "/=", TOK_DIV_ASSIGN},
    [TOK_MOD_ASSIGN] = {"MOD_ASSIGN", "%=", TOK_MOD_ASSIGN},

    [TOK_BIT_AND_ASSIGN] = {"BIT_AND_ASSIGN", "&=", TOK_BIT_AND_ASSIGN},
    [TOK_BIT_OR_ASSIGN] = {"BIT_OR_ASSIGN", "|=", TOK_BIT_OR_ASSIGN},
    [TOK_BIT_XOR_ASSIGN] = {"BIT_XOR_ASSIGN", "^=", TOK_BIT_XOR_ASSIGN},
    [TOK_LSHIFT_ASSIGN] = {"LSHIFT_ASSIGN", "<<=", TOK_LSHIFT_ASSIGN},
    [TOK_RSHIFT_ASSIGN] = {"RSHIFT_ASSIGN", ">>=", TOK_RSHIFT_ASSIGN},

    [TOK_LSHIFT] = {"LSHIFT", "<<", TOK_LSHIFT},
    [TOK_RSHIFT] = {"RSHIFT", ">>", TOK_RSHIFT},

    [TOK_BIT_AND] = {"BIT_AND", "&", TOK_BIT_AND},
    [TOK_BIT_OR] = {"BIT_OR", "|", TOK_BIT_OR},
    [TOK_BIT_NOT] = {"BIT_NOT", "~", TOK_BIT_NOT},
    [TOK_BIT_XOR] = {"BIT_XOR", "^", TOK_BIT_XOR},

    [TOK_AND] = {"AND", "&&", TOK_AND},
    [TOK_OR] = {"OR", "||", TOK_OR},
    [TOK_NOT] = {"NOT", "!", TOK_NOT},

    [TOK_EQ] = {"EQ", "==", TOK_EQ},
    [TOK_NOT_EQ] = {"NOT_EQ", "!=", TOK_NOT_EQ},

    [TOK_LESS] = {"LESS", "<", TOK_LESS},
    [TOK_GREATER] = {"GREATER", ">", TOK_GREATER},
    [TOK_LESS_EQ] = {"LESS_EQ", "<=", TOK_LESS_EQ},
    [TOK_GREATER_EQ] = {"GREATER_EQ", ">=", TOK_GREATER_EQ},

    [TOK_INCREMENT] = {"INCREMENT", "++", TOK_INCREMENT},
    [TOK_DECREMENT] = {"DECREMENT", "--", TOK_DECREMENT},

    // literals
    [TOK_IDENTIFIER] = {"IDENTIFIER", NULL, TOK_IDENTIFIER},
    [TOK_INTEGER] = {"INTEGER", NULL, TOK_INTEGER},
    [TOK_FLOAT] = {"FLOAT", NULL, TOK_FLOAT},
    [TOK_CHAR] = {"CHAR", NULL, TOK_CHAR},
    [TOK_STRING] = {"STRING", NULL, TOK_STRING},

    // keywords
    [TOK_KW_AUTO] = {"KW_AUTO", "auto", TOK_KW_AUTO},
    [TOK_KW_BREAK] = {"KW_BREAK", "break", TOK_KW_BREAK},
    [TOK_KW_CASE] = {"KW_CASE", "case", TOK_KW_CASE},
    [TOK_KW_CHAR] = {"KW_CHAR", "char", TOK_KW_CHAR},
    [TOK_KW_CONST] = {"KW_CONST", "const", TOK_KW_CONST},
    [TOK_KW_CONTINUE] = {"KW_CONTINUE", "continue", TOK_KW_CONTINUE},
    [TOK_KW_DEFAULT] = {"KW_DEFAULT", "default", TOK_KW_DEFAULT},
    [TOK_KW_DO] = {"KW_DO", "do", TOK_KW_DO},
    [TOK_KW_DOUBLE] = {"KW_DOUBLE", "double", TOK_KW_DOUBLE},
    [TOK_KW_ELSE] = {"KW_ELSE", "else", TOK_KW_ELSE},
    [TOK_KW_ENUM] = {"KW_ENUM", "enum", TOK_KW_ENUM},
    [TOK_KW_EXTERN] = {"KW_EXTERN", "extern", TOK_KW_EXTERN},
    [TOK_KW_FLOAT] = {"KW_FLOAT", "float", TOK_KW_FLOAT},
    [TOK_KW_FOR] = {"KW_FOR", "for", TOK_KW_FOR},
    [TOK_KW_GOTO] = {"KW_GOTO", "goto", TOK_KW_GOTO},
    [TOK_KW_IF] = {"KW_IF", "if", TOK_KW_IF},
    [TOK_KW_INLINE] = {"KW_INLINE", "inline", TOK_KW_INLINE},
    [TOK_KW_INT] = {"KW_INT", "int", TOK_KW_INT},
    [TOK_KW_LONG] = {"KW_LONG", "long", TOK_KW_LONG},
    [TOK_KW_REGISTER] = {"KW_REGISTER", "register", TOK_KW_REGISTER},
    [TOK_KW_RESTRICT] = {"KW_RESTRICT", "restrict", TOK_KW_RESTRICT},
    [TOK_KW_RETURN] = {"KW_RETURN", "return", TOK_KW_RETURN},
    [TOK_KW_SHORT] = {"KW_SHORT", "short", TOK_KW_SHORT},
    [TOK_KW_SIGNED] = {"KW_SIGNED", "signed", TOK_KW_SIGNED},
    [TOK_KW_SIZEOF] = {"KW_SIZEOF", "sizeof", TOK_KW_SIZEOF},
    [TOK_KW_STATIC] = {"KW_STATIC", "static", TOK_KW_STATIC},
    [TOK_KW_STRUCT] = {"KW_STRUCT", "struct", TOK_KW_STRUCT},
    [TOK_KW_SWITCH] = {"KW_SWITCH", "switch", TOK_KW_SWITCH},
    [TOK_KW_TYPEDEF] = {"KW_TYPEDEF", "typedef", TOK_KW_TYPEDEF},
    [TOK_KW_UNION] = {"KW_UNION", "union", TOK_KW_UNION},
    [TOK_KW_UNSIGNED] = {"KW_UNSIGNED", "unsigned", TOK_KW_UNSIGNED},
    [TOK_KW_VOID] = {"KW_VOID", "void", TOK_KW_VOID},
    [TOK_KW_VOLATILE] = {"KW_VOLATILE", "volatile", TOK_KW_VOLATILE},
    [TOK_KW_WHILE] = {"KW_WHILE", "while", TOK_KW_WHILE},

    // C99/C11 keywords
    [TOK_KW_BOOL] = {"KW_BOOL", "_Bool", TOK_KW_BOOL},
    [TOK_KW_COMPLEX] = {"KW_COMPLEX", "_Complex", TOK_KW_COMPLEX},
    [TOK_KW_IMAGINARY] = {"KW_IMAGINARY", "_Imaginary", TOK_KW_IMAGINARY},
    [TOK_KW_ALIGNAS] = {"KW_ALIGNAS", "_Alignas", TOK_KW_ALIGNAS},
    [TOK_KW_ALIGNOF] = {"KW_ALIGNOF", "_Alignof", TOK_KW_ALIGNOF},
    [TOK_KW_ATOMIC] = {"KW_ATOMIC", "_Atomic", TOK_KW_ATOMIC},
    [TOK_KW_GENERIC] = {"KW_GENERIC", "_Generic", TOK_KW_GENERIC},
    [TOK_KW_NORETURN] = {"KW_NORETURN", "_Noreturn", TOK_KW_NORETURN},
    [TOK_KW_STATIC_ASSERT] = {"KW_STATIC_ASSERT", "_Static_assert",
                              TOK_KW_STATIC_ASSERT},
    [TOK_KW_THREAD_LOCAL] = {"KW_THREAD_LOCAL", "_Thread_local",
                             TOK_KW_THREAD_LOCAL},

    // special tokens
    [TOK_EOF] = {"EOF", NULL, TOK_EOF},
    [TOK_INVALID] = {"INVALID", NULL, TOK_INVALID},
    [TOK_BANG] = {"BANG", "!", TOK_BANG},
    [TOK_NUMBER] = {"NUMBER", NULL, TOK_NUMBER},
    [TOK_INVALID_NUMBER] = {"INVALID_NUMBER", NULL, TOK_INVALID_NUMBER},
    [TOK_ARROW] = {"ARROW", "->", TOK_ARROW},
    [TOK_HASH] = {"HASH", "#", TOK_HASH},
    [TOK_CONDITIONAL] = {"CONDITIONAL", "?", TOK_CONDITIONAL},
};

const size_t tok_definitions_len =
    sizeof tok_definitions / sizeof tok_definitions[0];
