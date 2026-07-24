#include "lexer.h"

#include "../exp/exp.h"
#include "../str_buf/str_buf.h"
#include "../token/token.h"
#include "../token_arr/token_arr.h"
#include "lexer_scan.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void emit_token(Lexer *l, Token *token) {
    token_arr_append(l->tokens, token);
}

static Lexer *lexer_init(const char *path) {
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
    l->peek_char = 0;
    l->line = 0;
    l->col = 0;
    strbuf_init(&l->cur_word);
    memset(l->peek_buf, 0, sizeof l->peek_buf);

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
        lexer->cur_char = next_char(lexer);
        lexer->peek_char = peek_char(lexer);

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
                token_init_type(&token, "STRING", &lexer->cur_word, lexer->line,
                                lexer->col);
                emit_token(lexer, &token);
                strbuf_clear(&lexer->cur_word);
                lexer->col++;
                continue;

            case '/':
                if (lexer->peek_char == '/') {
                    handle_one_line_comment(lexer);
                    strbuf_clear(&lexer->cur_word);
                    continue;
                }

                if (lexer->peek_char == '*') {
                    handle_multiline_comment(lexer);
                    strbuf_clear(&lexer->cur_word);
                    continue;
                }

                continue;
        }

        strbuf_push(&lexer->cur_word, (char)lexer->cur_char);
        lexer->peek_buf[0] = (char)lexer->peek_char;

        size_t found_idx_buf = 0;
        size_t found_idx_buf_two = 0;

        if (is_operator(lexer->cur_word.items, &found_idx_buf)
            && is_operator(lexer->peek_buf, &found_idx_buf_two)) {
            // TODO: the ahead_char gets tokenized by itself even though
            // theres the continue to skip the iteration

            strbuf_push(&lexer->cur_word, (char)lexer->peek_char);
            is_operator(lexer->cur_word.items, &found_idx_buf);
            token_init_type(&token, exp_operators[found_idx_buf].tok_type_str,
                            &lexer->cur_word, lexer->line, lexer->col);
            emit_token(lexer, &token);
            strbuf_clear(&lexer->cur_word);
            continue;
        }

        if (is_digit((char)lexer->cur_char)) {
            if (handle_number(lexer) == 0) {
                token_init_type(&token, "NUMBER", &lexer->cur_word, lexer->line,
                                lexer->col);
                emit_token(lexer, &token);
                strbuf_clear(&lexer->cur_word);
                continue;
            } else {
                token_init_type(&token, "INVALID NUMBER", &lexer->cur_word,
                                lexer->line, lexer->col);
                emit_token(lexer, &token);
                strbuf_clear(&lexer->cur_word);
                continue;
            }
        }

        if (is_sintax_element(lexer->cur_word.items)) {
            token_init(&token, &lexer->cur_word, lexer->line, lexer->col);
            emit_token(lexer, &token);
            strbuf_clear(&lexer->cur_word);
            continue;
        }

        if (is_sintax_element(lexer->peek_buf)) {
            token_init(&token, &lexer->cur_word, lexer->line, lexer->col);
            emit_token(lexer, &token);
            strbuf_clear(&lexer->cur_word);
            continue;
        }

        if (lexer->peek_char == ' ') {
            token_init(&token, &lexer->cur_word, lexer->line, lexer->col);
            emit_token(lexer, &token);
            strbuf_clear(&lexer->cur_word);
            continue;
        }

        // TODO: unknown / error
    }

    fclose(lexer->file);
    return lexer;
}
