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

void advance(Lexer *l) {
    l->cur = l->peek;
    l->peek = fgetc(l->file);
    l->col++;
}

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

    l->cur = fgetc(l->file);
    l->peek = fgetc(l->file);

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

    if ((*l)->file) {
        fclose((*l)->file);
    }

    free(*l);
    *l = NULL;
}

Lexer *lexer_lex(const char *path) {
    Lexer *l = NULL;

    if (!path) {
        return l;
    }

    l = lexer_init(path);
    if (!l) {
        return l;
    }

    while (l->cur != EOF) {
        Token token;

        advance(l);

        l->col++;

        switch (l->cur) {
            case ' ':
                continue;

            case '\n':
                l->line++;
                l->col = 0;
                continue;

            case '"':
                handle_str(l);
                token_init_type(&token, token_type_str(TOK_STRING),
                                &l->cur_word, l->line, l->col);
                emit_token(l, &token);
                strbuf_clear(&l->cur_word);
                l->col++;
                continue;

            case '/':
                if (l->peek == '/') {
                    handle_one_line_comment(l);
                    strbuf_clear(&l->cur_word);
                    continue;
                }

                if (l->peek == '*') {
                    handle_multiline_comment(l);
                    strbuf_clear(&l->cur_word);
                    continue;
                }

                continue;
        }

        strbuf_push(&l->cur_word, (char)l->cur);
        l->peek_buf[0] = (char)l->peek;

        if (is_operator(l->cur_word.items, NULL)
            && is_operator(l->peek_buf, NULL)) {
            size_t idx = 0;

            strbuf_push(&l->cur_word, (char)l->peek);

            memset(l->peek_buf, 0, sizeof l->peek_buf);
            advance(l);

            is_operator(l->cur_word.items, &idx);
            token_init_type(&token, exp_operators[idx].tok_type_str,
                            &l->cur_word, l->line, l->col);
            emit_token(l, &token);
            strbuf_clear(&l->cur_word);
            continue;
        }

        if (is_digit((char)l->cur)) {
            if (handle_number(l) == 0) {
                token_init_type(&token, token_type_str(TOK_NUMBER),
                                &l->cur_word, l->line, l->col);
                emit_token(l, &token);
                strbuf_clear(&l->cur_word);
                continue;
            } else {
                token_init_type(&token, token_type_str(TOK_INVALID_NUMBER),
                                &l->cur_word, l->line, l->col);
                emit_token(l, &token);
                strbuf_clear(&l->cur_word);
                continue;
            }
        }

        if (is_sintax_element(l->cur_word.items)) {
            token_init(&token, &l->cur_word, l->line, l->col);
            emit_token(l, &token);
            strbuf_clear(&l->cur_word);
            continue;
        }

        if (is_sintax_element(l->peek_buf)) {
            token_init(&token, &l->cur_word, l->line, l->col);
            emit_token(l, &token);
            strbuf_clear(&l->cur_word);
            continue;
        }

        if (l->peek == ' ') {
            token_init(&token, &l->cur_word, l->line, l->col);
            emit_token(l, &token);
            strbuf_clear(&l->cur_word);
            continue;
        }

        // TODO: unknown / error
    }

    return l;
}
