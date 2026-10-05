#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#define TOKEN_BUF_MAX_CAP 255

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerator for all the token types available
 * */
typedef enum {
    // delimiters
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_LBRACE,
    TOK_RBRACE,
    TOK_LBRACKET,
    TOK_RBRACKET,
    TOK_COMMA,
    TOK_DOT,
    TOK_COLON,
    TOK_SEMICOLON,

    // operators
    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_MODULO,

    TOK_ASSIGN,

    TOK_ADD_ASSIGN,
    TOK_SUB_ASSIGN,
    TOK_MUL_ASSIGN,
    TOK_DIV_ASSIGN,
    TOK_MOD_ASSIGN,

    TOK_BIT_AND_ASSIGN,
    TOK_BIT_OR_ASSIGN,
    TOK_BIT_XOR_ASSIGN,
    TOK_LSHIFT_ASSIGN,
    TOK_RSHIFT_ASSIGN,

    TOK_LSHIFT,
    TOK_RSHIFT,

    TOK_BIT_AND,
    TOK_BIT_OR,
    TOK_BIT_NOT,
    TOK_BIT_XOR,

    TOK_AND,
    TOK_OR,
    TOK_NOT,

    TOK_EQ,
    TOK_NOT_EQ,

    TOK_LESS,
    TOK_GREATER,
    TOK_LESS_EQ,
    TOK_GREATER_EQ,

    TOK_INCREMENT,
    TOK_DECREMENT,

    // literals
    TOK_IDENTIFIER,
    TOK_INTEGER,
    TOK_FLOAT,
    TOK_CHAR,
    TOK_STRING,

    // keywords
    TOK_KW_AUTO,
    TOK_KW_BREAK,
    TOK_KW_CASE,
    TOK_KW_CHAR,
    TOK_KW_CONST,
    TOK_KW_CONTINUE,
    TOK_KW_DEFAULT,
    TOK_KW_DO,
    TOK_KW_DOUBLE,
    TOK_KW_ELSE,
    TOK_KW_ENUM,
    TOK_KW_EXTERN,
    TOK_KW_FLOAT,
    TOK_KW_FOR,
    TOK_KW_GOTO,
    TOK_KW_IF,
    TOK_KW_INLINE,
    TOK_KW_INT,
    TOK_KW_LONG,
    TOK_KW_REGISTER,
    TOK_KW_RESTRICT,
    TOK_KW_RETURN,
    TOK_KW_SHORT,
    TOK_KW_SIGNED,
    TOK_KW_SIZEOF,
    TOK_KW_STATIC,
    TOK_KW_STRUCT,
    TOK_KW_SWITCH,
    TOK_KW_TYPEDEF,
    TOK_KW_UNION,
    TOK_KW_UNSIGNED,
    TOK_KW_VOID,
    TOK_KW_VOLATILE,
    TOK_KW_WHILE,

    // C99/C11 keywords
    TOK_KW_BOOL,
    TOK_KW_COMPLEX,
    TOK_KW_IMAGINARY,
    TOK_KW_ALIGNAS,
    TOK_KW_ALIGNOF,
    TOK_KW_ATOMIC,
    TOK_KW_GENERIC,
    TOK_KW_NORETURN,
    TOK_KW_STATIC_ASSERT,
    TOK_KW_THREAD_LOCAL,

    // special tokens
    TOK_EOF,
    TOK_INVALID,

    TOK_INVALID_NUMBER,
    TOK_ARROW,
    TOK_HASH,
    TOK_CONDITIONAL,
    TOK_INVALID_STR,
    TOK_INVALID_CHAR,
} TokenType;

/**
 * @brief Single Token
 */
typedef struct {
    TokenType type;                 /* < Token type from the enum TokenType */
    char lexeme[TOKEN_BUF_MAX_CAP]; /* < Value found in source code */
    int line; /* < Number of line where token was found at */
    int col;  /* < Number of column where token was found at */
} Token;

/**
 * @brief Prints the elements of a Token
 *
 * @param t Pointer to Token
 */
void token_println(const Token *t);

/**
 * @brief Returns a string literal of the string type based on a given token
 * type
 *
 * @param t Token type
 *
 * @return String literal containing the type of token
 */
const char *token_type_to_str(TokenType t);

#ifdef __cplusplus
}
#endif

#endif
