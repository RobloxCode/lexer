#include "lexer/lexer/lexer.h"

#include "lexer/alloc/alloc.h"
#include "lexer/lexer/lexer_scan.h"
#include "lexer/str_buf/str_buf.h"
#include "lexer/token/token.h"
#include "lexer/token_arr/token_arr.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void advance(Lexer *l) {
    l->cur = l->peek;
    l->peek = l->peek2;
    l->peek2 = fgetc(l->file);

    if (l->cur == '\n') {
        l->cur_line++;
        l->cur_col = 0;
    } else {
        l->cur_col++;
    }
}

static Lexer *_lexer_init(const char *path) {
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
    l->peek2 = fgetc(l->file);

    l->cur_line = 1;
    l->cur_col = 1;
    l->tok_start_line = 1;
    l->tok_start_col = 1;

    l->overflow = false;

    strbuf_init(&l->cur_word);
    memset(l->peek_buf, 0, sizeof l->peek_buf);

    return l;
}

void lexer_deinit(Lexer **l) {
    if (!l || !*l) {
        return;
    }

    TokenArr_status status = TOKENARR_OK;

    if ((*l)->tokens) {
        if ((status = token_arr_deinit(&(*l)->tokens)) != TOKENARR_OK) {
            fprintf(stderr, "Failed to deinitialize tokens, status: %d\n",
                    status);
        }
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

    l = _lexer_init(path);
    if (!l) {
        return l;
    }

    while (l->cur != EOF) {
        scan_token(l);
        advance(l);
    }

    Token eof;
    StrBuf empty;

    strbuf_init(&empty);
    token_init_type(&eof, TOK_EOF, &empty, l->cur_line, l->cur_col);

    if ((token_arr_append(l->tokens, &eof)) != TOKENARR_OK) {
        return NULL;
    }

    return l;
}
