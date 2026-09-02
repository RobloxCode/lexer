#ifndef TOKEN_DEF_H
#define TOKEN_DEF_H

#include "../../utils/token/token.h"

#include <stddef.h>

/**
 * @brief Individual expression from the C language
 */
typedef struct {
    char *display_name;
    char *lexeme;     /* < The elements that the expression has */
    TokType tok_type; /* < Actuall token type*/
} TokenDef;

extern const TokenDef tok_definitions[];
extern const size_t tok_definitions_len;

#endif
