#include "lexer.h"

#include "../str_buf/str_buf.h"
#include "../token/token.h"
#include "../token_arr/token_arr.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define INIT_TOKEN_CAP 30

static void emit_token(TokenArr *token_arr, Token *token) {
    token_arr_append(token_arr, token);
}

static void handle_str(FILE *file, int *cur_char, StrBuf *cur_word, int *col) {
    int chars_count = 0;

    while ((*cur_char = fgetc(file)) != EOF && *cur_char != '"') {
        strbuf_push(cur_word, (char)*cur_char);
        *cur_char = fgetc(file);
        chars_count++;
    }

    strbuf_push(cur_word, '"');
    *col += chars_count;
}

static void handle_number(FILE *file, int *cur_char, StrBuf *cur_word,
                          int *col) {
    int digits_count = 0;
    *cur_char = fgetc(file);

    while (is_digit((char)*cur_char) || *cur_char == '.') {
        strbuf_push(cur_word, (char)*cur_char);
        *cur_char = fgetc(file);
        digits_count++;
    }

    if (*cur_char != EOF) {
        ungetc(*cur_char, file);
    }

    *col += digits_count;
}

static void handle_one_line_comment(FILE *file, int *cur_char) {
    *cur_char = fgetc(file);

    while (*cur_char != '\n') {
        *cur_char = fgetc(file);
    }

    if (*cur_char != EOF) {
        ungetc(*cur_char, file);
    }
}

static void handle_multiline_comment(FILE *file, int *cur_char, int *ahead) {
    while ((*cur_char = fgetc(file)) != EOF) {
        *ahead = fgetc(file);

        if (*ahead != EOF) {
            ungetc(*ahead, file);
        }

        if (*cur_char == '*' && *ahead == '/') {
            *cur_char = fgetc(file);
            break;
        }
    }
}

TokenArr *lexeme(char *path) {
    if (!path) {
        return NULL;
    }

    FILE *file = fopen(path, "r");
    if (!file) {
        return NULL;
    }

    TokenArr *token_arr = token_arr_init(INIT_TOKEN_CAP);
    if (!token_arr) {
        fclose(file);
        return NULL;
    }

    StrBuf cur_word = {0};
    strbuf_init(&cur_word);

    StrBuf ahead_word = {0};
    strbuf_init(&ahead_word);

    int line = 1;
    int col = 0;

    int cur_char = 0;
    int ahead_char = 0;

    while (cur_char != EOF) {
        Token token;
        cur_char = fgetc(file);
        ahead_char = fgetc(file);

        if (ahead_char != EOF) {
            ungetc(ahead_char, file);
        }

        col++;

        switch (cur_char) {
            case ' ':
                continue;

            case '\n':
                line++;
                col = 0;
                continue;

            case '"':
                handle_str(file, &cur_char, &cur_word, &col);
                token_init_type(&token, "STRING", cur_word.items, line, col);
                emit_token(token_arr, &token);
                strbuf_clear(&cur_word);
                col++;
                continue;

            case '/':
                if (ahead_char == '/') {
                    handle_one_line_comment(file, &cur_char);
                    strbuf_clear(&cur_word);
                    continue;
                }

                if (ahead_char == '*') {
                    handle_multiline_comment(file, &cur_char, &ahead_char);
                    strbuf_clear(&cur_word);
                    continue;
                }

                continue;
        }

        strbuf_push(&cur_word, (char)cur_char);
        strbuf_set(&ahead_word, (char)ahead_char, 0);

        if (is_digit((char)cur_char)) {
            handle_number(file, &cur_char, &cur_word, &col);
            token_init_type(&token, "NUMBER", cur_word.items, line, col);
            emit_token(token_arr, &token);
            strbuf_clear(&cur_word);
            continue;
        }

        if (is_sintax_element(cur_word.items)) {
            token_init(&token, cur_word.items, line, col);
            emit_token(token_arr, &token);
            strbuf_clear(&cur_word);
            continue;
        }

        if (is_sintax_element(ahead_word.items)) {
            token_init(&token, cur_word.items, line, col);
            emit_token(token_arr, &token);
            strbuf_clear(&cur_word);
            continue;
        }

        if (ahead_char == ' ') {
            token_init(&token, cur_word.items, line, col);
            emit_token(token_arr, &token);
            strbuf_clear(&cur_word);
            continue;
        }

        // TODO: unknown / error
    }

    fclose(file);
    return token_arr;
}
