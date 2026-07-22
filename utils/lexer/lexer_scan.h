#ifndef LEXER_SCAN_H
#define LEXER_SCAN_H

#include "../str_buf/str_buf.h"

#include <stdio.h>

void handle_str(FILE *file, int *cur_char, StrBuf *cur_word, int *col);

int handle_number(FILE *file, int *cur_char, StrBuf *cur_word, int *col);

void handle_one_line_comment(FILE *file, int *cur_char);

void handle_multiline_comment(FILE *file, int *cur_char, int *ahead);

#endif
