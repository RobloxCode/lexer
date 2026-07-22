#ifndef LEXER_SCAN_H
#define LEXER_SCAN_H

#include "../str_buf/str_buf.h"
#include "lexer.h"

#include <stdio.h>

void handle_str(Lexer *l);

int handle_number(Lexer *l);

void handle_one_line_comment(Lexer *l);

void handle_multiline_comment(Lexer *l);

#endif
