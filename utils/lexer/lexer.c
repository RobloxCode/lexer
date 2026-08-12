#include "lexer.h"

#include "../alloc/alloc.h"
#include "../str_buf/str_buf.h"
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

static Lexer *lexer_init(const char *path) {
    Lexer *l = xmalloc(sizeof *l);

    l->file = fopen(path, "r");
    if (!l->file) {
        free(l);
        return NULL;
    }

    l->tokens = token_arr_init(INIT_TOKEN_CAP);
    if (!l->tokens) {
        fclose(l->file);
        free(l);
        return NULL;
    }

    l->cur = fgetc(l->file);
    l->peek = fgetc(l->file);

    l->line = 1;
    l->col = 1;
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
        // TODO: since we advance first, the first char
        // doesn't get tokenized
        advance(l);
        scan_token(l);
    }

    return l;
}
