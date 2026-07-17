#include "../utils/lexer/lexer.h"

#include <stdio.h>
#include <stdlib.h>

#define PATH "src/source.c"

int main(void) {
    TokenArr *token_arr = lexeme(PATH);
    if (!token_arr) {
        fprintf(stderr, "Error lexing: %s\n", PATH);
        return EXIT_FAILURE;
    }

    token_arr_println(token_arr);

    token_arr_deinit(&token_arr);
    return EXIT_SUCCESS;
}
