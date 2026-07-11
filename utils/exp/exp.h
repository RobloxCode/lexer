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
