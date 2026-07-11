#ifndef EXP_H
#define EXP_H

#include "../../utils/token/token.h"

#include <stddef.h>

typedef struct {
    char *val;
    char *tok_type_str;
    TokType tok_type;
} Exp;

extern Exp exp_operators[];
extern Exp exp_delimeters[];
extern Exp exp_keywords[];

extern size_t exp_keywords_len;
extern size_t exp_delimeters_len;
extern size_t exp_operators_len;

#endif
