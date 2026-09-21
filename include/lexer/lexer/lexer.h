#ifndef LEXER_H
#define LEXER_H

#include "lexer/str_buf/str_buf.h"
#include "lexer/token_arr/token_arr.h"

#define INIT_TOKEN_CAP 30

#include <stdio.h>

/**
 * @brief Lexer state holding data to help the lexeme
 */
typedef struct {
    FILE *file;         /* < Pointer to the file being lexed */

    int cur;            /* < Current character in the file */
    int peek;           /* < Second character lookahead (after cur) */
    int peek2;          /* < Third character lookahead */

    int cur_line;       /* < Current number of line (1 based) */
    int cur_col;        /* < Current number of column (1 based) */

    int tok_start_line; /* < Line where the current token began */
    int tok_start_col;  /* < Column where the current token began */

    StrBuf cur_word;    /* < current word/text of the token being built */

    bool overflow;      /* < Checks if 'cur_word' has exceeded STR_BUF_MAX_CAP
                             true if 'cur_word' hit STR_BUF_MAX_CAP,
                             otherwise false */

    TokenArr *tokens;   /* < Tokens produced so far */

} Lexer;

/**
 * @brief Lexes a file at a given path
 *
 * @param Path Path of the file to be lexed
 *
 * @return Pointer to a heap allocated Lexer
 */
Lexer *lexer_lex(const char *path);

/**
 * @brief Frees the memory of a Lexer
 *
 * @param l Double pointer to a Lexer, sets to NULL
 *          the pointer after freeing
 */
void lexer_deinit(Lexer **l);

/**
 * @brief Goes one character ahead, it also increments
 *        the column by one
 *
 * @param l Pointer to a Lexer
 */
void advance(Lexer *l);

#endif
