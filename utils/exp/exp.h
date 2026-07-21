#ifndef EXP_H
#define EXP_H

#include "../../utils/token/token.h"

#include <stddef.h>

/**
 * @brief Individual expression from the C language
 */
typedef struct {
    char *val;          /* < The elements that the expression has */
    char *tok_type_str; /* < String text of the token type */
    TokType tok_type;   /* < Actuall token type*/
} Exp;

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
} exp_operators_idxs;

/* Array of Exp containing all the operators (+, -, =, ...) */
extern Exp exp_operators[];

/* Array of Exp containing all the delimeters ( [, (, }, ;, ...) */
extern Exp exp_delimeters[];

/* Array of Exp containing all the keywords (for, auto, if, ...) */
extern Exp exp_keywords[];

/* Number of elements of each array */
extern size_t exp_keywords_len;
extern size_t exp_delimeters_len;
extern size_t exp_operators_len;

#endif
