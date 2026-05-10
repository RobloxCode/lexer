#include "Token.h"
#include <stdio.h>

void Token_print(Token t)
{
    printf("%s(%s)\n", t.type, t.value);
}
