#include "lexer.h"

#include "../str_buf/str_buf.h"
#include "../token/token.h"
#include "../token_arr/token_arr.h"
#include "lexer_scan.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_TOKEN_CAP 30

static void emit_token(TokenArr *token_arr, Token *token) {
    token_arr_append(token_arr, token);
}

Lexer *lexeme(char *path) {
    if (!path) {
        return NULL;
    }

    Lexer *lexer = malloc(sizeof *lexer);
    if (!lexer) {
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
            if (handle_number(file, &cur_char, &cur_word, &col) == 0) {
                handle_number(file, &cur_char, &cur_word, &col);
                token_init_type(&token, "NUMBER", cur_word.items, line, col);
                emit_token(token_arr, &token);
                strbuf_clear(&cur_word);
                continue;
            } else {
                token_init_type(&token, "INVALID NUMBER", cur_word.items, line,
                                col);
                emit_token(token_arr, &token);
                strbuf_clear(&cur_word);
                continue;
            }
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
    lexer->tokens = token_arr;
    return lexer;
}
