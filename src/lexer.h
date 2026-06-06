#ifndef LEXER_H
#define LEXER_H

#include "../utils/TokenArr.h"

TokenArr *lexeme(char *src_code);
char *read_file(const char *filename);
void clear_str(char *str);

#endif
