#ifndef LEXER_TOKEN_INTERNAL_H
#define LEXER_TOKEN_INTERNAL_H

#include "lexer/token.h"
#include "str_buf/str_buf.h"

#include <stdbool.h>
#include <stddef.h>

void token_init(Token *t, const StrBuf *word, const int line, const int col);
void token_init_type(Token *t, TokenType type, const StrBuf *word,
                     const int line, const int col);

bool is_number(const char *s);
bool is_digit(const int c);
bool is_letter(const int c);
bool is_operator(const char *s, size_t *found_idx);
bool is_keyword(const char *s, size_t *idx);

#endif
