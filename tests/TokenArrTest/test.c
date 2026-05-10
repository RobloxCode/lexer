#include <stdio.h>
#include "../../TokenArr.h"

int main()
{
    TokenArr *token_arr = TokenArr_init(10);
    if (!token_arr)
        return 1;

    // int number = 3 + 2;
    TokenArr_append(token_arr, (Token) { .type = "KEYWORD", .value = "int"});
    TokenArr_append(token_arr, (Token) { .type = "ID", .value = "number"});
    TokenArr_append(token_arr, (Token) { .type = "ASSIGN", .value = "="});
    TokenArr_append(token_arr, (Token) { .type = "NUMBER", .value = "3"});
    TokenArr_append(token_arr, (Token) { .type = "PLUS", .value = "+"});
    TokenArr_append(token_arr, (Token) { .type = "NUMBER", .value = "2"});
    TokenArr_append(token_arr, (Token) { .type = "SEMICOLON", .value = ";"});

    printf("example expression: int number = 3 + 2;\n");
    TokenArr_println(token_arr);

    TokenArr_deinit(&token_arr);
    return 0;
}
