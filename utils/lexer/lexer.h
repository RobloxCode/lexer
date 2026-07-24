#ifndef LEXER_H
#define LEXER_H

#include "../str_buf/str_buf.h"
#include "../token_arr/token_arr.h"

#define INIT_TOKEN_CAP 30

#include <stdio.h>

/**
 * @brief Lexer state holding data to help the lexeme
 */
typedef struct {
    FILE *file;       /* < Pointer to the file being lexed */

    int cur_char;     /* < Current character in the file */
    int peek_char;    /* < Character after cur_char */

    int line;         /* < Current number of lines */
    int col;          /* < Current number of columns */

    StrBuf cur_word;  /* < StrBuf storing the current word */
    char peek_buf[2]; /* < This is a buffer for peek_char since some
                       *   functions need to check for peek_char bet
                       *   they must take a char *
                       */

    TokenArr *tokens; /* < Pointer to a TokenArr */

} Lexer;

/**
 * @brief Lexes a file at a given path
 *
 * @param Path Path of the file to be lexed
 *
 * @return Pointer to a heap allocated Lexer
 */
Lexer *lexeme(char *path);

/**
 * @brief Frees the memory of a Lexer
 *
 * @param l Double pointer to a Lexer, sets to NULL
 *          the pointer after freeing
 */
void lexer_deinit(Lexer **l);

#endif
