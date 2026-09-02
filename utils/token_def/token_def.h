#ifndef TOKEN_DEF_H
#define TOKEN_DEF_H

#include "../../utils/token/token.h"

#include <stddef.h>

/**
 * @brief Struct containing the lexeme value of a token and its display value to
 *        help when printing to the console, also, every value is mapped to a
 *        token type
 */
typedef struct {
    char *display_name; /* < word that will go alongside when printing
                           (INCREMENT, LPAREN, ...) */
    char *lexeme;     /* < The elements that the expression has (++, ), ...) */
    TokType tok_type; /* < Actuall token type*/
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
