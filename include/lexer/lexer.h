#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include "lexer/token_arr.h"

typedef struct Lexer Lexer;

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
 * @brief retrieves the tokens from the Lexer
 *
 * @param l Pointer to a heap allocated Lexer
 */
const TokenArr *lexer_tokens(const Lexer *l);

#endif
