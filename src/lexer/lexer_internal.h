#ifndef LEXER_INTERNAL_H
#define LEXER_INTERNAL_H

#include "lexer/lexer.h"
#include "lexer/token_arr.h"
#include "str_buf/str_buf.h"

#include <stdbool.h>
#include <stdio.h>

#define INIT_TOKEN_CAP 30

struct Lexer {
    FILE *file;         /* < Pointer to the file being lexed */

    int cur;            /* < Current character in the file */
    int peek;           /* < Second character lookahead (after cur) */
    int peek2;          /* < Third character lookahead */

    int cur_line;       /* < Current line where 'cur' is at (1 based) */
    int cur_col;        /* < Current column where 'cur' is at (1 based) */

    int tok_start_line; /* < Line where the current token began */
    int tok_start_col;  /* < Column where the current token began */

    StrBuf cur_word;    /* < Text of the token being built */
    bool overflow;      /* < true if 'cur_word' hit STR_BUF_MAX_CAP */

    TokenArr *tokens;   /* < Tokens produced so far */
};

/**
 * @brief Goes one character ahead and increments the column
 */
void lexer_advance(Lexer *l);

#endif
