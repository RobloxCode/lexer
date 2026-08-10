#include "../utils/lexer/lexer.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PATH "src/source.c"

int main(int argc, char **argv) {
    const char *path = (argc == 2) ? argv[1] : DEFAULT_PATH;

    Lexer *lexer = lexer_lex(path);
    if (!lexer) {
        fprintf(stderr, "Failed to tokenize: %s\n", path);
        return EXIT_FAILURE;
    }

    token_arr_println(lexer->tokens);

    lexer_deinit(&lexer);

    return EXIT_SUCCESS;
}
