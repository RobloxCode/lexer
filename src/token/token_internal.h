#ifndef LEXER_TOKEN_INTERNAL_H
#define LEXER_TOKEN_INTERNAL_H

#include "lexer/token.h"
#include "str_buf/str_buf.h"

#include <stdbool.h>
#include <stddef.h>

void token_init_type(Token *t, TokenType type, const StrBuf *word,
                     const int line, const int col);

// TODO: use the is_alpha() and is_digit() functions from ctype.h instead of these custom ones
bool is_number(const char *s);
bool is_digit(const int c);
bool is_letter(const int c);
bool is_operator(const char *s, size_t *found_idx);
bool is_keyword(const char *s, size_t *idx);
bool all_letters(const char *items, const size_t len);

#endif
