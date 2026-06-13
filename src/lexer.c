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
                       size_t *cur_word_buff_pos) {
    *c = fgetc(f);

    while (*c != '"') {
        cur_word_buff[(*cur_word_buff_pos)++] = (char)*c;
        *c = fgetc(f);
    }

    cur_word_buff[(*cur_word_buff_pos)++] = '"';
}

static void hande_number(FILE *f, int *c, char *cur_word_buff,
                         size_t *cur_word_buff_pos) {
    *c = fgetc(f);

    while (is_digit((char)*c) || *c == '.') {
        cur_word_buff[(*cur_word_buff_pos)++] = (char)*c;
        *c = fgetc(f);
    }
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

    int c;
    int ahead;
    while (c != EOF) {
        Token token;
        c = fgetc(file);
        ahead = fgetc(file);
        ungetc(ahead, file);

        if (c == ' ') {
            continue;
        }

        if (c == '\n') {
            continue;
        }

        cur_word_buff[cur_word_buff_pos++] = (char)c;
        ahead_word_buff[0] = (char)ahead;

        if (c == '"') {
            handle_str(file, &c, cur_word_buff, &cur_word_buff_pos);
            strcpy(token.type, "STRING");
            strcpy(token.value, cur_word_buff);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }

        if (is_digit((char)c)) {
            hande_number(file, &c, cur_word_buff, &cur_word_buff_pos);
            strcpy(token.type, "NUMBER");
            strcpy(token.value, cur_word_buff);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }

        if (is_language_feature(cur_word_buff)) {
            token_init(&token, cur_word_buff);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }

        if (is_language_feature(ahead_word_buff)) {
            token_init(&token, cur_word_buff);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }

        if (ahead == ' ') {
            token_init(&token, cur_word_buff);
            emit_token(token_arr, &token, cur_word_buff, &cur_word_buff_pos);
            continue;
        }
    }

    return token_arr;
}
