#ifndef TOKEN_DEF_H
#define TOKEN_DEF_H

#include "lexer/token.h"

#include <stddef.h>

typedef enum {
    CAT_DELIMITER,
    CAT_OPERATOR,
    CAT_KEYWORD,
    CAT_LITERAL,
    CAT_SPECIAL,
} TokenCategory;

/**
 * @brief Struct containing the lexeme value of a token and its display value to
 *        help when printing to the console, also, every value is mapped to a
 *        token type
 */
typedef struct {
    /* < word that will go alongside when printing */
    // (INCREMENT, LPAREN, ...) */
    const char *display_name;

    /* < The elements that the expression has (++, ), ...) */
    const char *lexeme;

    /* < Actuall token type*/
    TokenType type;

    TokenCategory category;
} TokenDef;

/**
 * Array containing a struct TokenDef for every TokType
 */
extern const TokenDef tok_definitions[];

/**
 * length of the array tok_definitions
 */
extern const size_t tok_definitions_len;

#endif
