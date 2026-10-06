#include "lexer/lexer.h"

#include <stdio.h>
#include <stdlib.h>

#define ASSERT_MSG(cond, fmt, ...)                                             \
    do {                                                                       \
        if (!(cond)) {                                                         \
            fprintf(stderr,                                                    \
                    "Assertion failed: (%s), file %s, line %d\n" fmt "\n",     \
                    #cond, __FILE__, __LINE__, ##__VA_ARGS__);                 \
            abort();                                                           \
        }                                                                      \
    } while (0)

int main(void) {
    const char *path = "input.c";
    Lexer *l = lexer_lex(path);

    ASSERT_MSG(l != NULL, "Failed to tokenize %s", path);

    token_arr_println(lexer_tokens(l));

    lexer_deinit(&l);
    return 0;
}
