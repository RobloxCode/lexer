#ifndef LEXER_SCAN_H
#define LEXER_SCAN_H

#include "../str_buf/str_buf.h"
#include "lexer.h"

#include <stdio.h>

#define STR_TOK_TYPE         "STRING"
#define NUM_TOK_TYPE         "NUMBER"
#define INVALID_NUM_TOK_TYPE "INVALID NUMBER"

void scan_token(Lexer *l);

#endif
