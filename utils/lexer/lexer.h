#ifndef LEXER_H
#define LEXER_H

#include "../str_buf/str_buf.h"
#include "../token_arr/token_arr.h"

#define INIT_TOKEN_CAP 30

#include <stdio.h>

typedef struct {
    FILE *file;

    int cur_char;
    int ahead_char;

    int line;
    int col;

    StrBuf cur_word;
    StrBuf ahead_word;

    TokenArr *tokens;

} Lexer;

/**
 * @brief Lexes a file at a given path
 *
 * @param path Path of the file to be lexed
 */
Lexer *lexeme(char *path);

void lexer_deinit(Lexer **l);

#endif
