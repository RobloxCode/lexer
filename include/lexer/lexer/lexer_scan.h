#ifndef LEXER_SCAN_H
#define LEXER_SCAN_H

#include "lexer/lexer/lexer.h"
#include "lexer/str_buf/str_buf.h"

#include <stdio.h>

/**
 * @brief Scans the current character and identifies the corresponding token.
 *
 * @param l Pointer to Lexer
 */
void scan_token(Lexer *l);

#endif
