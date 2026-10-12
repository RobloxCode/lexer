#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

/**
 * @file lexer.h
 * @brief Public entry point of the lexer library.
 *
 * Typical usage:
 *
 * 1. Call lexer_lex() with the path of a source file
 * 2. Read the resulting tokens through lexer_tokens()
 * 3. Release everything with lexer_deinit()
 */

#include "lexer/token_arr.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque lexer handle. Its fields are private to the
 *        library and can only be used through the functions
 *        declared in this header.
 */
typedef struct Lexer Lexer;

/**
 * @brief Lexes a file at a given path and splits it into tokens.
 *
 * Whitespace and comments are skipped. Malformed input does not make
 * the call fail: it is reported as a token of type TOK_INVALID,
 * TOK_INVALID_STR, TOK_INVALID_CHAR or TOK_INVALID_NUMBER, so the
 * caller can inspect it.
 *
 * If memory runs out the program is terminade instead of returning NULL.
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
 * Passing NULL, or a pointer that already holds NULL, is safe
 * and does nothing, so calling this twice on the same variable
 * is harmless.
 *
 * Every pointer obtained from lexer_token(), and every pointer
 * into teh token array, becomes invalid after this call, Tokens that
 * were copied by value (for example token_arr_get()) stay vaild.
 *
 * @param l Double pointer to a Lexer, sets to NULL
 *          the pointer after freeing.
 */
void lexer_deinit(Lexer **l);

/**
 * @brief Give access to the tokens produced by lexer_lex().
 *
 * The array belongs to the Lexer, do not modify it, free it or pass
 * it to token_arr_deinit(). It stays valid until lexer_deinit() is
 * called on l.
 *
 * @param l Pointer to a heap allocated Lexer.
 *
 * @return Read-only pointer to the token array, or NULL if l is NULL.
 */
const TokenArr *lexer_tokens(const Lexer *l);

#ifdef __cplusplus
}
#endif

#endif
