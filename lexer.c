#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/TokenArr.h"

#define WORD_MAX_CAP 255

char *keywords[] = {
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

void clear_buff(char *buff);
TokenArr *lexeme(char *code_sample);

int main(void)
{
    char *code_example = "int x = 10 + 5;";
    TokenArr *token_arr = lexeme(code_example);
    if (!token_arr)
        return EXIT_FAILURE;

    TokenArr_println(token_arr);

    TokenArr_deinit(&token_arr);

    return EXIT_SUCCESS;
}

TokenArr *lexeme(char *code_sample)
{
    if (!code_sample)
        return NULL;

    size_t code_sample_len = strlen(code_sample);
    TokenArr *token_arr = TokenArr_init(code_sample_len);
    if (!token_arr)
        return NULL;

    char cur_word_buff[WORD_MAX_CAP] = {0};
    size_t cur_word_buff_pos = 0;

    for (size_t i = 0; i < code_sample_len; ++i) {
        Token new_token = {0};

        if (code_sample[i + 1] == '\0') {
            cur_word_buff[cur_word_buff_pos] = '\0';

            memcpy(new_token.type, "NULL", sizeof "NULL");
            memcpy(new_token.value, cur_word_buff, sizeof cur_word_buff);
            TokenArr_append(token_arr, new_token);
            break;
        }

        if (code_sample[i] == ' ') {
            cur_word_buff[cur_word_buff_pos] = '\0';

            memcpy(new_token.type, "NULL", sizeof "NULL");
            memcpy(new_token.value, cur_word_buff, sizeof cur_word_buff);
            TokenArr_append(token_arr, new_token);

            cur_word_buff_pos = 0;
            continue;
        }

        cur_word_buff[cur_word_buff_pos++] = code_sample[i];
    }

    // size_t code_sample_pos = 0;
    //
    // while (1) {
    //     Token new_token = {0};
    //     char cur_char = code_sample[code_sample_pos];
    //
    //     if (cur_char == '\0') {
    //         memcpy(new_token.type, "NULL", sizeof "NULL");
    //         memcpy(new_token.value, cur_word_buff, sizeof cur_word_buff);
    //         TokenArr_append(token_arr, new_token);
    //         break;
    //     }
    //
    //     if (cur_char == ' ') {
    //         cur_word_buff[cur_word_buff_pos] = '\0';
    //
    //         memcpy(new_token.type, "NULL", sizeof "NULL");
    //         memcpy(new_token.value, cur_word_buff, sizeof cur_word_buff);
    //
    //         cur_word_buff_pos = 0;
    //     } else {
    //         cur_word_buff[cur_word_buff_pos++] = cur_char;
    //     }
    //
    //     code_sample_pos++;
    //     TokenArr_append(token_arr, new_token);
    // }

    printf("len: %zu\n", token_arr->length);

    return token_arr;
}

