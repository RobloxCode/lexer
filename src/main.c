#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

#define SOURCE_CODE_FILENAME "src/source.c"

int main(void) {
    TokenArr *token_arr = lexeme(SOURCE_CODE_FILENAME);
    if (!token_arr) {
        fprintf(stderr, "Error lexing: %s\n", SOURCE_CODE_FILENAME);
        return EXIT_FAILURE;
    }

    token_arr_println(token_arr);

    token_arr_deinit(&token_arr);
    return EXIT_SUCCESS;
}
