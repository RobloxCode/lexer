#include "lexer.h"

#include "../str_buf/str_buf.h"
#include "../token/token.h"
#include "../token_arr/token_arr.h"
#include "lexer_scan.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void emit_token(TokenArr *token_arr, Token *token) {
    token_arr_append(token_arr, token);
}

Lexer *lexer_init(const char *path) {
    Lexer *l = malloc(sizeof *l);
    if (!l) {
        return NULL;
    }

    l->file = fopen(path, "r");
    if (!l->file) {
        return NULL;
    }

    l->tokens = token_arr_init(INIT_TOKEN_CAP);
    if (!l->tokens) {
        fclose(l->file);
        return NULL;
    }

    l->cur_char = 0;
    l->ahead_char = 0;
    l->line = 0;
    l->col = 0;
    strbuf_init(&l->cur_word);
    strbuf_init(&l->ahead_word);

    return l;
}

void lexer_deinit(Lexer **l) {
    if (!l || !*l) {
        return;
    }

    if ((*l)->tokens) {
        token_arr_deinit(&(*l)->tokens);
    }

    free(*l);
    *l = NULL;
}

Lexer *lexeme(char *path) {
    if (!path) {
        return NULL;
    }

    Lexer *lexer = lexer_init(path);
    if (!lexer) {
        return NULL;
    }

    while (lexer->cur_char != EOF) {
        Token token;
        lexer->cur_char = fgetc(lexer->file);
        lexer->ahead_char = fgetc(lexer->file);

        if (lexer->ahead_char != EOF) {
            ungetc(lexer->ahead_char, lexer->file);
        }

        lexer->col++;

        switch (lexer->cur_char) {
            case ' ':
                continue;

            case '\n':
                lexer->line++;
                lexer->col = 0;
                continue;

            case '"':
                handle_str(lexer);
                token_init_type(&token, "STRING", lexer->cur_word.items,
                                lexer->line, lexer->col);
                emit_token(lexer->tokens, &token);
                strbuf_clear(&lexer->cur_word);
                lexer->col++;
                continue;

            case '/':
                if (lexer->ahead_char == '/') {
                    handle_one_line_comment(lexer->file, &lexer->cur_char);
                    strbuf_clear(&lexer->cur_word);
                    continue;
                }

                if (lexer->ahead_char == '*') {
                    handle_multiline_comment(lexer->file, &lexer->cur_char,
                                             &lexer->ahead_char);
                    strbuf_clear(&lexer->cur_word);
                    continue;
                }

                continue;
        }

        strbuf_push(&lexer->cur_word, (char)lexer->cur_char);
        strbuf_set(&lexer->ahead_word, (char)lexer->ahead_char, 0);

        if (is_digit((char)lexer->cur_char)) {
            if (handle_number(lexer->file, &lexer->cur_char, &lexer->cur_word,
                              &lexer->col)
                == 0) {
                handle_number(lexer->file, &lexer->cur_char, &lexer->cur_word,
                              &lexer->col);
                token_init_type(&token, "NUMBER", lexer->cur_word.items,
                                lexer->line, lexer->col);
                emit_token(lexer->tokens, &token);
                strbuf_clear(&lexer->cur_word);
                continue;
            } else {
                token_init_type(&token, "INVALID NUMBER", lexer->cur_word.items,
                                lexer->line, lexer->col);
                emit_token(lexer->tokens, &token);
                strbuf_clear(&lexer->cur_word);
                continue;
            }
        }

        if (is_sintax_element(lexer->cur_word.items)) {
            token_init(&token, lexer->cur_word.items, lexer->line, lexer->col);
            emit_token(lexer->tokens, &token);
            strbuf_clear(&lexer->cur_word);
            continue;
        }

        if (is_sintax_element(lexer->ahead_word.items)) {
            token_init(&token, lexer->cur_word.items, lexer->line, lexer->col);
            emit_token(lexer->tokens, &token);
            strbuf_clear(&lexer->cur_word);
            continue;
        }

        if (lexer->ahead_char == ' ') {
            token_init(&token, lexer->cur_word.items, lexer->line, lexer->col);
            emit_token(lexer->tokens, &token);
            strbuf_clear(&lexer->cur_word);
            continue;
        }

        // TODO: unknown / error
    }

    fclose(lexer->file);
    return lexer;
}
