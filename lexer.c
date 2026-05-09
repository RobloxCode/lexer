#include <stdio.h>

typedef struct {
    char *type;
    char *value;
} Token;

void Token_print(Token t)
{
    printf("%s(%s)\n", t.type, t.value);
}

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

int main(void)
{
    char *code_example = "int x =  10 + 5;";

    return 0;
}
