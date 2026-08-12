#include "../../utils/lexer/lexer.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Lexer *l = lexer_lex("");
    if (!l) {
        fprintf(stderr, "Failed to tokenize: %s\n", "");
        return EXIT_FAILURE;
    }
    lexer_deinit(&l);
    return 0;
}
