#include "../utils/lexer/lexer.h"

#include <stdio.h>
#include <stdlib.h>

#define PATH "src/source.c"

int main(void) {
    Lexer *lexer = lexeme(PATH);
    if (!lexer) {
        return EXIT_FAILURE;
    }

    if (!lexer->tokens) {
        fprintf(stderr, "Error lexing: %s\n", PATH);
        return EXIT_FAILURE;
    }

    token_arr_println(lexer->tokens);

    token_arr_deinit(&lexer->tokens);
    free(lexer);

    return EXIT_SUCCESS;
}
