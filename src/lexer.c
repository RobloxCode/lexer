#include "lexer.h"

#include "../utils/token.h"
#include "../utils/token_arr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_MAX_CAP 255
#define MIN_FILE_LEN 30

static void clear_str(char *str) {
    for (size_t i = 0; str[i] != '\0'; ++i) {
        str[i] = 0;
    }
}

static void emit_token(TokenArr *token_arr, Token *token, char *cur_word_buff,
                       size_t *cur_word_buff_pos) {
    clear_str(cur_word_buff);
    *cur_word_buff_pos = 0;
    token_arr_append(token_arr, *token);
}

static void handle_str(FILE *f, int *c, char *cur_word_buff,
                       size_t *cur_word_buff_pos, int *chars_count) {
    *c = fgetc(f);

    while (*c != '"') {
        cur_word_buff[(*cur_word_buff_pos)++] = (char)*c;
        *c = fgetc(f);
        (*chars_count)++;
    }

    cur_word_buff[(*cur_word_buff_pos)++] = '"';
}

static void hande_number(FILE *f, int *c, char *cur_word_buff,
                         size_t *cur_word_buff_pos, int *digits_count) {
    *c = fgetc(f);

    while (is_digit((char)*c) || *c == '.') {
        cur_word_buff[(*cur_word_buff_pos)++] = (char)*c;
        *c = fgetc(f);
        (*digits_count)++;
    }

    ungetc(*c, f);
}

TokenArr *lexeme(char *filename) {
    if (!filename) {
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    TokenArr *token_arr = token_arr_init(MIN_FILE_LEN);
    if (!token_arr) {
        return NULL;
    }

    char cur_word_buff[WORD_MAX_CAP] = {0};
    size_t cur_word_buff_pos = 0;

    char ahead_word_buff[WORD_MAX_CAP] = {0};

    int line = 1;
    int col = 0;

    int cur_char;
    int ahead_char;

    while (cur_char != EOF) {
        Token token;
        cur_char = fgetc(file);
        ahead_char = fgetc(file);
        ungetc(ahead_char, file);

        col++;

        if (cur_char == ' ') {
            continue;
        }

        if (cur_char == '\n') {
            line++;
            col = 0;
            continue;
        }

        cur_word_buff[cur_word_buff_pos++] = (char)cur_char;
        ahead_word_buff[0] = (char)ahead_char;

        if (cur_char == '"') {
            int chars_count = 0;
            handle_str(file, &cur_char, cur_word_buff, &cur_word_buff_pos,
                       &chars_count);
            col += chars_count;
            token_init_type(&token, "STRING", cur_word_buff, line, col);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            col++;
            continue;
        }

        if (is_digit((char)cur_char)) {
            int digits_count = 0;
            hande_number(file, &cur_char, cur_word_buff, &cur_word_buff_pos,
                         &digits_count);
            col += digits_count;
            token_init_type(&token, "NUMBER", cur_word_buff, line, col);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }

        if (is_language_feature(cur_word_buff)) {
            token_init(&token, cur_word_buff, line, col);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }

        if (is_language_feature(ahead_word_buff)) {
            token_init(&token, cur_word_buff, line, col);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }

        if (ahead_char == ' ') {
            token_init(&token, cur_word_buff, line, col);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }
    }

    fclose(file);
    return token_arr;
}
