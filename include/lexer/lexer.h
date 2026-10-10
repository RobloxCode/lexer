#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include "lexer/token_arr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Lexer Lexer;

/**
 * @brief Lexes a file at a given path.
 *
 * @param path Path of the file to be lexed.
 *
 * @return A heap-allocated Lexer, or NULL if the path cannot be opened or
 *         tokenization cannot complete. Release it with lexer_deinit().
 */
Lexer *lexer_lex(const char *path);

/**
 * @brief Frees a Lexer and its tokens.
 *
 * @param l Double pointer to a Lexer, sets to NULL
 *          the pointer after freeing
 */
void lexer_deinit(Lexer **l);

/**
 * @brief Retrieves the tokens owned by a Lexer.
 *
 * @param l Pointer to a heap allocated Lexer
 *
 * @return Read-only pointer to the TokenArr, or NULL if l is NULL. The pointer
 *         remains valid only until lexer_deinit() is called for l.
 */
const TokenArr *lexer_tokens(const Lexer *l);

#ifdef __cplusplus
}
#endif

#endif
