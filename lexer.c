#include <stdio.h>
#include "TokenArr.h"

char *KEYWORDS[] = {
    // control flow
    "if", "else", "switch", "case", "default",
    "for", "while", "do", "break", "continue",
    "goto", "return",

    // data types
    "int", "char", "float", "double", "void",
    "short", "long", "signed", "unsigned", "_Bool",

    // storage/class modifiers
    "auto", "register", "static", "extern", "typedef",
    "const", "volatile", "restrict",

    // user-defined types
    "struct", "union", "enum"
};

TokenArr *lexeme(char *code_sample);

int main(void)
{
    char *code_example = "int x =  10 + 5;";

    return 0;
}

TokenArr *lexeme(char *code_sample)
{
    if (!code_sample)
        return NULL;


}

