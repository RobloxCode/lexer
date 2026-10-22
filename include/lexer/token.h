#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#define TOKEN_BUF_MAX_CAP 300

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
    TOK_INVALID_SUFFIX,
    TOK_UNTERMINATED_COMMENT,
} TokenType;

/**
 * @brief A single lexical unit found in the source file
 */
typedef struct {
    /** Kind of token, one of the values of TokenType. */
    TokenType type;

    /**
     * Text of the token as written in the source, always NUL-terminated.
     *
     * - Quotes are not included: the string "hi" is stored as hi, and the
     *   character 'a' is stored as a.
     * - Escape sequences are kept as written: a backslash followed by n is
     *   stored as two characters, not as a newline.
     * - The TOK_EOF token has an empty lexeme.
     * - Text longer than TOKEN_BUF_MAX_CAP - 1 characters is truncated and the
     *   token is reported as TOK_INVALID.
     */

    // TODO: change this to char *lexeme
    // and also could add a size_t len
    char lexeme[TOKEN_BUF_MAX_CAP];

    /** Line where the token starts, counting from 1. */
    int line;

    /** Column of the first character of the token, counting from 1. */
    int col;
} Token;

/**
 * @brief Prints a token to stdout on a single line.
 *
 * The output looks like "[ 3:7 ]    KW_INT(int)": the line and column, the type
 * name given by token_type_to_str(), and the lexeme between parentheses.
 *
 * @param t Token to print. Must not be NULL.
 */
void token_println(const Token *t);

/**
 * @brief Gives the printable name of a token type.
 *
 * The name is the enumerator without its TOK_ prefix, for example "PLUS",
 * "KW_INT" or "EOF". It is meant for printing and debugging.
 *
 * @param t Token type to look up.
 *
 * @return A string literal with the name of the type, or "UNKNOWN" if t is not
 *         a valid TokenType value. The string is owned by the library: do not
 *         modify it or free it.
 */
const char *token_type_to_str(TokenType t);

#ifdef __cplusplus
}
#endif

#endif
