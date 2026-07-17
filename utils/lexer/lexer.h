#ifndef LEXER_H
#define LEXER_H

#include "../token_arr/token_arr.h"

/**
 * @brief Lexes a file at a given path
 *
 * @param path Path of the file to be lexed
 */
TokenArr *lexeme(char *path);

#endif
