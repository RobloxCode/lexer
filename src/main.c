#include "../utils/lexer/lexer.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PATH "src/source.c"

int main(int argc, char **argv) {
    const char *path = (argc == 2) ? argv[1] : DEFAULT_PATH;
    TokenArr_status status = TOKENARR_OK;

    Lexer *lexer = lexer_lex(path);
    if (!lexer) {
        fprintf(stderr, "Failed to tokenize: %s\n", path);
        return EXIT_FAILURE;
    }

    if ((status = token_arr_println(lexer->tokens)) != TOKENARR_OK) {
        fprintf(stderr, "Failed to print tokens, status: %d", status);
        return EXIT_FAILURE;
    }

    lexer_deinit(&lexer);

    return EXIT_SUCCESS;
}
