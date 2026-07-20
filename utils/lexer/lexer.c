#include "lexer.h"

#include "../str_buf/str_buf.h"
#include "../token/token.h"
#include "../token_arr/token_arr.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MIN_FILE_LEN 30

static void emit_token(TokenArr *token_arr, Token *token, StrBuf *cur_word) {
    strbuf_clear(cur_word);
    token_arr_append(token_arr, token);
}

static void handle_str(FILE *file, int *cur_char, StrBuf *cur_word, int *col) {
    int chars_count = 0;
    *cur_char = fgetc(file);

    while (*cur_char != '"') {
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

static void handle_one_line_comment(FILE *file, int *cur_char, StrBuf *cur_word,
                                    int *col) {
    int cols_count = 0;
    *cur_char = fgetc(file);

    while (*cur_char != '\n') {
        strbuf_push(cur_word, (char)*cur_char);
        *cur_char = fgetc(file);
        cols_count++;
    }

    if (*cur_char != EOF) {
        ungetc(*cur_char, file);
    }
    *col += cols_count;
}

static void handle_multiline_comment(FILE *file, int *cur_char, int *ahead,
                                     StrBuf *cur_word, int *col, int *line) {
    int lines_count = 0;
    int cols_count = 0;

    while ((*cur_char = fgetc(file)) != EOF) {
        *ahead = fgetc(file);

        if (*ahead != EOF) {
            ungetc(*ahead, file);
        }

        if (*cur_char == '*' && *ahead == '/') {
            *cur_char = fgetc(file);
            strbuf_push(cur_word, (char)*ahead);
            break;
        }

        if (*cur_char == '\n') {
            lines_count++;
        }

        strbuf_push(cur_word, (char)*cur_char);
        cols_count++;
    }

    *col += cols_count;
    *line += lines_count;
}

TokenArr *lexeme(char *path) {
    if (!path) {
        return NULL;
    }

    FILE *file = fopen(path, "r");
    if (!file) {
        return NULL;
    }

    TokenArr *token_arr = token_arr_init(MIN_FILE_LEN);
    if (!token_arr) {
        return NULL;
    }

    StrBuf cur_word;
    strbuf_init(&cur_word);

    StrBuf ahead_word;
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

        if (cur_char == ' ') {
            continue;
        }

        if (cur_char == '\n') {
            line++;
            col = 0;
            continue;
        }

        strbuf_push(&cur_word, (char)cur_char);
        strbuf_set(&ahead_word, (char)ahead_char, 0);

        // TODO: have to add a way of checking for multi line characters
        // if (cur_char == '=' || cur_char == '!' || cur_char == '<'
        //     || cur_char == '>' || cur_char == '&' || cur_char == '|'
        //     || cur_char == '-' ||) {
        // }

        if (cur_char == '"') {
            handle_str(file, &cur_char, &cur_word, &col);
            token_init_type(&token, "STRING", cur_word.items, line, col);
            emit_token(token_arr, &token, &cur_word);
            col++;
            continue;
        }

        if (cur_char == '/' && ahead_char == '/') {
            handle_one_line_comment(file, &cur_char, &cur_word, &col);
            token_init_type(&token, "ONE LINE COMMENT", cur_word.items, line,
                            col);
            emit_token(token_arr, &token, &cur_word);
            continue;
        }

        if (cur_char == '/' && ahead_char == '*') {
            handle_multiline_comment(file, &cur_char, &ahead_char, &cur_word,
                                     &col, &line);
            token_init_type(&token, "MULTI-LINE COMMENT", cur_word.items, line,
                            col);
            emit_token(token_arr, &token, &cur_word);
            continue;
        }

        if (is_digit((char)cur_char)) {
            handle_number(file, &cur_char, &cur_word, &col);
            token_init_type(&token, "NUMBER", cur_word.items, line, col);
            emit_token(token_arr, &token, &cur_word);
            continue;
        }

        if (is_sintax_element(cur_word.items)) {
            token_init(&token, cur_word.items, line, col);
            emit_token(token_arr, &token, &cur_word);
            continue;
        }

        if (is_sintax_element(ahead_word.items)) {
            token_init(&token, cur_word.items, line, col);
            emit_token(token_arr, &token, &cur_word);
            continue;
        }

        if (ahead_char == ' ') {
            token_init(&token, cur_word.items, line, col);
            emit_token(token_arr, &token, &cur_word);
            continue;
        }
    }

    fclose(file);
    return token_arr;
}
