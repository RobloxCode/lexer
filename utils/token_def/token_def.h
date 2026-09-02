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

/**
 * @brief indexes of the operators in the exp_operators array
 */
typedef enum {
    PLUS_IDX,
    MINUS_IDX,
    STAR_IDX,
    SLASH_IDX,
    MODULO_IDX,
    ASSIGN_IDX,
    ADD_ASSIGN_IDX,
    SUB_ASSIGN_IDX,
    MUL_ASSIGN_IDX,
    DIV_ASSIGN_IDX,
    MOD_ASSIGN_IDX,
    AND_ASSIGN_IDX,
    OR_ASSIGN_IDX,
    XOR_ASSIGN_IDX,
    LBITSHIFT_IDX,
    RBITSHIFT_IDX,
    BIT_AND_IDX,
    BIT_OR_IDX,
    BIT_NOT_IDX,
    BIT_XOR_IDX,
    AND_IDX,
    OR_IDX,
    NOT_EQUAL_IDX,
    EQUAL_IDX,
    LESS_IDX,
    GREATER_IDX,
    LESS_EQ_IDX,
    GREATER_EQ_IDX,
    INCREMENT_IDX,
    DECREMENT_IDX,

    EXP_OPERATORS_COUNT
} token_definitions_idxs;

extern const TokenDef tok_definitions[];
extern const size_t tok_definitions_len;

#endif
