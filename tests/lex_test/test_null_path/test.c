#include "../../../utils/lexer/lexer.h"
#include "../assert_macro.h"

#include <stdlib.h>

int main(void) {
    const char *path = "";
    Lexer *l = lexer_lex(path);

    ASSERT_MSG(l != NULL, "Failed to tokenize %s", path);

    lexer_deinit(&l);
    return 0;
}
