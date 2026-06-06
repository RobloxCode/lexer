#ifndef LEXER_H
#define LEXER_H

#include "../utils/TokenArr.h"

char *read_file(const char *filename);
void clear_str(char *str);

void emit_token(TokenArr *token_arr, Token *token, char *cur_word_buff,
                size_t *cur_word_buff_pos);
void handle_str(size_t *cur, char *src_code, char *cur_word_buff,
                size_t *cur_word_buff_pos);
void hande_number(size_t *cur, char *src_code, char *cur_word_buff,
                  size_t *cur_word_buff_pos);
TokenArr *lexeme(char *src_code);

#endif
