#include "lexer.h"

#include "../utils/Token.h"
#include "../utils/TokenArr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_MAX_CAP         255
#define SOURCE_CODE_FILENAME "source.c"

void emit_token(TokenArr *token_arr, Token *token, char *cur_word_buff,
                size_t *cur_word_buff_pos) {
    clear_str(cur_word_buff);
    *cur_word_buff_pos = 0;
    TokenArr_append(token_arr, *token);
}

void handle_str(size_t *cur, char *src_code, char *cur_word_buff,
                size_t *cur_word_buff_pos) {
    (*cur)++;

    while (src_code[*cur] != '"') {
        cur_word_buff[(*cur_word_buff_pos)++] = src_code[*cur];
        (*cur)++;
    }

    cur_word_buff[(*cur_word_buff_pos)++] = '"';
}

void hande_number(size_t *cur, char *src_code, char *cur_word_buff,
                  size_t *cur_word_buff_pos) {
    (*cur)++;
    while (is_digit(src_code[*cur]) || src_code[*cur] == '.') {
        if (src_code[*cur] == '.') {
            cur_word_buff[(*cur_word_buff_pos)++] = src_code[*cur];
            (*cur)++;
            continue;
        }

        cur_word_buff[(*cur_word_buff_pos)++] = src_code[*cur];
        (*cur)++;
    }

    // i dont know why we go pass one when its not number
    (*cur)--;
}

TokenArr *lexeme(char *src_code) {
    if (!src_code) {
        return NULL;
    }

    size_t src_code_len = strlen(src_code);
    TokenArr *token_arr = TokenArr_init(src_code_len);
    if (!token_arr) {
        return NULL;
    }

    char cur_word_buff[WORD_MAX_CAP] = {0};
    size_t cur_word_buff_pos = 0;

    char ahead_word_buff[WORD_MAX_CAP] = {0};

    size_t ahead = 0;
    for (size_t cur = 0; cur < src_code_len; ++cur) {
        Token token;
        ahead = cur + 1;

        if (src_code[cur] == ' ') {
            continue;
        }

        if (src_code[cur] == '\n') {
            continue;
        }

        cur_word_buff[cur_word_buff_pos++] = src_code[cur];
        ahead_word_buff[0] = src_code[ahead];

        if (src_code[cur] == '"') {
            handle_str(&cur, src_code, cur_word_buff, &cur_word_buff_pos);
            strcpy(token.type, "STRING");
            strcpy(token.value, cur_word_buff);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }

        if (is_digit(src_code[cur])) {
            hande_number(&cur, src_code, cur_word_buff, &cur_word_buff_pos);
            strcpy(token.type, "NUMBER");
            strcpy(token.value, cur_word_buff);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }

        if (is_language_feature(cur_word_buff)) {
            Token_init(&token, cur_word_buff);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }

        if (is_language_feature(ahead_word_buff)) {
            Token_init(&token, cur_word_buff);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }

        if (src_code[ahead] == ' ') {
            Token_init(&token, cur_word_buff);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }
    }

    return token_arr;
}

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);

    long size = ftell(file);

    rewind(file);

    char *buffer = malloc((size_t)size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, (size_t)size, file);

    buffer[size] = '\0';

    fclose(file);

    return buffer;
}

void clear_str(char *str) {
    for (size_t i = 0; str[i] != '\0'; ++i) {
        str[i] = 0;
    }
}
