#include "token_def.h"

#include "lexer/token.h"

const TokenDef tok_definitions[] = {
    // delimiters
    [TOK_LPAREN] = {"LPAREN", "(", TOK_LPAREN, CAT_DELIMITER},
    [TOK_RPAREN] = {"RPAREN", ")", TOK_RPAREN, CAT_DELIMITER},
    [TOK_LBRACE] = {"LBRACE", "{", TOK_LBRACE, CAT_DELIMITER},
    [TOK_RBRACE] = {"RBRACE", "}", TOK_RBRACE, CAT_DELIMITER},
    [TOK_LBRACKET] = {"LBRACKET", "[", TOK_LBRACKET, CAT_DELIMITER},
    [TOK_RBRACKET] = {"RBRACKET", "]", TOK_RBRACKET, CAT_DELIMITER},
    [TOK_COMMA] = {"COMMA", ",", TOK_COMMA, CAT_DELIMITER},
    [TOK_DOT] = {"DOT", ".", TOK_DOT, CAT_DELIMITER},
    [TOK_COLON] = {"COLON", ":", TOK_COLON, CAT_DELIMITER},
    [TOK_SEMICOLON] = {"SEMICOLON", ";", TOK_SEMICOLON, CAT_DELIMITER},

    // operators
    [TOK_PLUS] = {"PLUS", "+", TOK_PLUS, CAT_OPERATOR},
    [TOK_MINUS] = {"MINUS", "-", TOK_MINUS, CAT_OPERATOR},
    [TOK_STAR] = {"STAR", "*", TOK_STAR, CAT_OPERATOR},
    [TOK_SLASH] = {"SLASH", "/", TOK_SLASH, CAT_OPERATOR},
    [TOK_MODULO] = {"MODULO", "%", TOK_MODULO, CAT_OPERATOR},

    [TOK_ASSIGN] = {"ASSIGN", "=", TOK_ASSIGN, CAT_OPERATOR},

    [TOK_ADD_ASSIGN] = {"ADD_ASSIGN", "+=", TOK_ADD_ASSIGN, CAT_OPERATOR},
    [TOK_SUB_ASSIGN] = {"SUB_ASSIGN", "-=", TOK_SUB_ASSIGN, CAT_OPERATOR},
    [TOK_MUL_ASSIGN] = {"MUL_ASSIGN", "*=", TOK_MUL_ASSIGN, CAT_OPERATOR},
    [TOK_DIV_ASSIGN] = {"DIV_ASSIGN", "/=", TOK_DIV_ASSIGN, CAT_OPERATOR},
    [TOK_MOD_ASSIGN] = {"MOD_ASSIGN", "%=", TOK_MOD_ASSIGN, CAT_OPERATOR},

    [TOK_BIT_AND_ASSIGN] = {"BIT_AND_ASSIGN", "&=", TOK_BIT_AND_ASSIGN,
                            CAT_OPERATOR},
    [TOK_BIT_OR_ASSIGN] = {"BIT_OR_ASSIGN", "|=", TOK_BIT_OR_ASSIGN,
                           CAT_OPERATOR},
    [TOK_BIT_XOR_ASSIGN] = {"BIT_XOR_ASSIGN", "^=", TOK_BIT_XOR_ASSIGN,
                            CAT_OPERATOR},
    [TOK_LSHIFT_ASSIGN] = {"LSHIFT_ASSIGN", "<<=", TOK_LSHIFT_ASSIGN,
                           CAT_OPERATOR},
    [TOK_RSHIFT_ASSIGN] = {"RSHIFT_ASSIGN", ">>=", TOK_RSHIFT_ASSIGN,
                           CAT_OPERATOR},

    [TOK_LSHIFT] = {"LSHIFT", "<<", TOK_LSHIFT, CAT_OPERATOR},
    [TOK_RSHIFT] = {"RSHIFT", ">>", TOK_RSHIFT, CAT_OPERATOR},

    [TOK_BIT_AND] = {"BIT_AND", "&", TOK_BIT_AND, CAT_OPERATOR},
    [TOK_BIT_OR] = {"BIT_OR", "|", TOK_BIT_OR, CAT_OPERATOR},
    [TOK_BIT_NOT] = {"BIT_NOT", "~", TOK_BIT_NOT, CAT_OPERATOR},
    [TOK_BIT_XOR] = {"BIT_XOR", "^", TOK_BIT_XOR, CAT_OPERATOR},

    [TOK_AND] = {"AND", "&&", TOK_AND, CAT_OPERATOR},
    [TOK_OR] = {"OR", "||", TOK_OR, CAT_OPERATOR},
    [TOK_NOT] = {"NOT", "!", TOK_NOT, CAT_OPERATOR},

    [TOK_EQ] = {"EQ", "==", TOK_EQ, CAT_OPERATOR},
    [TOK_NOT_EQ] = {"NOT_EQ", "!=", TOK_NOT_EQ, CAT_OPERATOR},

    [TOK_LESS] = {"LESS", "<", TOK_LESS, CAT_OPERATOR},
    [TOK_GREATER] = {"GREATER", ">", TOK_GREATER, CAT_OPERATOR},
    [TOK_LESS_EQ] = {"LESS_EQ", "<=", TOK_LESS_EQ, CAT_OPERATOR},
    [TOK_GREATER_EQ] = {"GREATER_EQ", ">=", TOK_GREATER_EQ, CAT_OPERATOR},

    [TOK_INCREMENT] = {"INCREMENT", "++", TOK_INCREMENT, CAT_OPERATOR},
    [TOK_DECREMENT] = {"DECREMENT", "--", TOK_DECREMENT, CAT_OPERATOR},

    [TOK_ARROW] = {"ARROW", "->", TOK_ARROW, CAT_OPERATOR},
    [TOK_HASH] = {"HASH", "#", TOK_HASH, CAT_OPERATOR},
    [TOK_CONDITIONAL] = {"CONDITIONAL", "?", TOK_CONDITIONAL, CAT_OPERATOR},

    // literals
    [TOK_IDENTIFIER] = {"IDENTIFIER", NULL, TOK_IDENTIFIER, CAT_LITERAL},
    [TOK_INTEGER] = {"INTEGER", NULL, TOK_INTEGER, CAT_LITERAL},
    [TOK_FLOAT] = {"FLOAT", NULL, TOK_FLOAT, CAT_LITERAL},
    [TOK_CHAR] = {"CHAR", NULL, TOK_CHAR, CAT_LITERAL},
    [TOK_STRING] = {"STRING", NULL, TOK_STRING, CAT_LITERAL},

    // keywords
    [TOK_KW_AUTO] = {"KW_AUTO", "auto", TOK_KW_AUTO, CAT_KEYWORD},
    [TOK_KW_BREAK] = {"KW_BREAK", "break", TOK_KW_BREAK, CAT_KEYWORD},
    [TOK_KW_CASE] = {"KW_CASE", "case", TOK_KW_CASE, CAT_KEYWORD},
    [TOK_KW_CHAR] = {"KW_CHAR", "char", TOK_KW_CHAR, CAT_KEYWORD},
    [TOK_KW_CONST] = {"KW_CONST", "const", TOK_KW_CONST, CAT_KEYWORD},
    [TOK_KW_CONTINUE] = {"KW_CONTINUE", "continue", TOK_KW_CONTINUE,
                         CAT_KEYWORD},
    [TOK_KW_DEFAULT] = {"KW_DEFAULT", "default", TOK_KW_DEFAULT, CAT_KEYWORD},
    [TOK_KW_DO] = {"KW_DO", "do", TOK_KW_DO, CAT_KEYWORD},
    [TOK_KW_DOUBLE] = {"KW_DOUBLE", "double", TOK_KW_DOUBLE, CAT_KEYWORD},
    [TOK_KW_ELSE] = {"KW_ELSE", "else", TOK_KW_ELSE, CAT_KEYWORD},
    [TOK_KW_ENUM] = {"KW_ENUM", "enum", TOK_KW_ENUM, CAT_KEYWORD},
    [TOK_KW_EXTERN] = {"KW_EXTERN", "extern", TOK_KW_EXTERN, CAT_KEYWORD},
    [TOK_KW_FLOAT] = {"KW_FLOAT", "float", TOK_KW_FLOAT, CAT_KEYWORD},
    [TOK_KW_FOR] = {"KW_FOR", "for", TOK_KW_FOR, CAT_KEYWORD},
    [TOK_KW_GOTO] = {"KW_GOTO", "goto", TOK_KW_GOTO, CAT_KEYWORD},
    [TOK_KW_IF] = {"KW_IF", "if", TOK_KW_IF, CAT_KEYWORD},
    [TOK_KW_INLINE] = {"KW_INLINE", "inline", TOK_KW_INLINE, CAT_KEYWORD},
    [TOK_KW_INT] = {"KW_INT", "int", TOK_KW_INT, CAT_KEYWORD},
    [TOK_KW_LONG] = {"KW_LONG", "long", TOK_KW_LONG, CAT_KEYWORD},
    [TOK_KW_REGISTER] = {"KW_REGISTER", "register", TOK_KW_REGISTER,
                         CAT_KEYWORD},
    [TOK_KW_RESTRICT] = {"KW_RESTRICT", "restrict", TOK_KW_RESTRICT,
                         CAT_KEYWORD},
    [TOK_KW_RETURN] = {"KW_RETURN", "return", TOK_KW_RETURN, CAT_KEYWORD},
    [TOK_KW_SHORT] = {"KW_SHORT", "short", TOK_KW_SHORT, CAT_KEYWORD},
    [TOK_KW_SIGNED] = {"KW_SIGNED", "signed", TOK_KW_SIGNED, CAT_KEYWORD},
    [TOK_KW_SIZEOF] = {"KW_SIZEOF", "sizeof", TOK_KW_SIZEOF, CAT_KEYWORD},
    [TOK_KW_STATIC] = {"KW_STATIC", "static", TOK_KW_STATIC, CAT_KEYWORD},
    [TOK_KW_STRUCT] = {"KW_STRUCT", "struct", TOK_KW_STRUCT, CAT_KEYWORD},
    [TOK_KW_SWITCH] = {"KW_SWITCH", "switch", TOK_KW_SWITCH, CAT_KEYWORD},
    [TOK_KW_TYPEDEF] = {"KW_TYPEDEF", "typedef", TOK_KW_TYPEDEF, CAT_KEYWORD},
    [TOK_KW_UNION] = {"KW_UNION", "union", TOK_KW_UNION, CAT_KEYWORD},
    [TOK_KW_UNSIGNED] = {"KW_UNSIGNED", "unsigned", TOK_KW_UNSIGNED,
                         CAT_KEYWORD},
    [TOK_KW_VOID] = {"KW_VOID", "void", TOK_KW_VOID, CAT_KEYWORD},
    [TOK_KW_VOLATILE] = {"KW_VOLATILE", "volatile", TOK_KW_VOLATILE,
                         CAT_KEYWORD},
    [TOK_KW_WHILE] = {"KW_WHILE", "while", TOK_KW_WHILE, CAT_KEYWORD},

    // C99/C11 keywords
    [TOK_KW_BOOL] = {"KW_BOOL", "_Bool", TOK_KW_BOOL, CAT_KEYWORD},
    [TOK_KW_COMPLEX] = {"KW_COMPLEX", "_Complex", TOK_KW_COMPLEX, CAT_KEYWORD},
    [TOK_KW_IMAGINARY] = {"KW_IMAGINARY", "_Imaginary", TOK_KW_IMAGINARY,
                          CAT_KEYWORD},
    [TOK_KW_ALIGNAS] = {"KW_ALIGNAS", "_Alignas", TOK_KW_ALIGNAS, CAT_KEYWORD},
    [TOK_KW_ALIGNOF] = {"KW_ALIGNOF", "_Alignof", TOK_KW_ALIGNOF, CAT_KEYWORD},
    [TOK_KW_ATOMIC] = {"KW_ATOMIC", "_Atomic", TOK_KW_ATOMIC, CAT_KEYWORD},
    [TOK_KW_GENERIC] = {"KW_GENERIC", "_Generic", TOK_KW_GENERIC, CAT_KEYWORD},
    [TOK_KW_NORETURN] = {"KW_NORETURN", "_Noreturn", TOK_KW_NORETURN,
                         CAT_KEYWORD},
    [TOK_KW_STATIC_ASSERT] = {"KW_STATIC_ASSERT", "_Static_assert",
                              TOK_KW_STATIC_ASSERT, CAT_KEYWORD},
    [TOK_KW_THREAD_LOCAL] = {"KW_THREAD_LOCAL", "_Thread_local",
                             TOK_KW_THREAD_LOCAL, CAT_KEYWORD},

    // special tokens
    [TOK_EOF] = {"EOF", NULL, TOK_EOF, CAT_SPECIAL},
    [TOK_INVALID] = {"INVALID", NULL, TOK_INVALID, CAT_SPECIAL},
    [TOK_INVALID_NUMBER] = {"INVALID_NUMBER", NULL, TOK_INVALID_NUMBER,
                            CAT_SPECIAL},
    // [TOK_ARROW] = {"ARROW", "->", TOK_ARROW, CAT_SPECIAL},
    [TOK_INVALID_STR] = {"INVALID_STR", NULL, TOK_INVALID_STR, CAT_SPECIAL},
    [TOK_INVALID_CHAR] = {"INVALID_CHAR", NULL, TOK_INVALID_CHAR, CAT_SPECIAL},
    [TOK_INVALID_SUFFIX] = {"INVALID_SUFFIX", NULL, TOK_INVALID_SUFFIX,
                            CAT_SPECIAL},
    [TOK_UNTERMINATED_COMMENT] = {"UNTERMINATED_COMMENT", NULL,
                                  TOK_UNTERMINATED_COMMENT, CAT_SPECIAL},
};

const size_t tok_definitions_len =
    sizeof tok_definitions / sizeof tok_definitions[0];

_Static_assert(sizeof tok_definitions / sizeof tok_definitions[0]
                   == TOK_UNTERMINATED_COMMENT + 1,
               "tok_definitions must have one row per TokenType");
