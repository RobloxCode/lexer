#include "lexer.h"

#include <stdlib.h>

#define SOURCE_CODE_FILENAME "src/source.c"

int main(void) {
    TokenArr *token_arr = lexeme(SOURCE_CODE_FILENAME);
    if (!token_arr) {
        goto cleanup;
    }

    token_arr_println(token_arr);

cleanup:
    if (token_arr) {
        token_arr_deinit(&token_arr);
    }

    return EXIT_SUCCESS;
}
