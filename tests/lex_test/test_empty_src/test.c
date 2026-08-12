#include "../../../utils/lexer/lexer.h"
#include "../assert_macro.h"

#include <stdlib.h>

int main(void) {
    const char *path = "input.c";
    Lexer *l = lexer_lex(path);

    ASSERT_MSG(l != NULL, "Failed to tokenize %s", path);

    printf("len of l->tokens: %zu\n", l->tokens->length); // 0
    token_arr_println(l->tokens);

    lexer_deinit(&l);
    return 0;
}
