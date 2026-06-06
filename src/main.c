#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

#define SOURCE_CODE_FILENAME "src/source.c"

int main(void) {
    char *file_content = NULL;
    TokenArr *token_arr = NULL;

    file_content = read_file(SOURCE_CODE_FILENAME);
    if (!file_content) {
        fprintf(stderr, "failed to open %s\n", SOURCE_CODE_FILENAME);
        goto cleanup;
    }

    token_arr = lexeme(file_content);
    if (!token_arr) {
        goto cleanup;
    }

    TokenArr_println(token_arr);

cleanup:
    if (token_arr) {
        TokenArr_deinit(&token_arr);
    }

    if (file_content) {
        free(file_content);
    }

    return EXIT_SUCCESS;
}
