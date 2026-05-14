#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/Token.h"
#include "utils/TokenArr.h"

#define WORD_MAX_CAP 255

void Token_set_type(Token *t, const char *word);
TokenArr *lexeme(char *code_sample);

int main(void)
{
    char *code_example = "int some_var = 10 + ( num2 % 5); "
                         "if (x == 8) return 1";
    TokenArr *token_arr = lexeme(code_example);
    if (!token_arr)
        return EXIT_FAILURE;

    TokenArr_println(token_arr);

    TokenArr_deinit(&token_arr);

    return EXIT_SUCCESS;
}

void Token_set_type(Token *t, const char *word)
{
    if (is_keyword(word)) {
        strcpy(t->type, "KEYWORD");
    }

    else if (is_operator(word)) {
        strcpy(t->type, "OPERATOR");
    }

    else if (is_number(word)) {
        strcpy(t->type, "NUMBER");
    }

    else if (is_identifier(word)) {
        strcpy(t->type, "IDENTIFIER");
    }

    else if (is_delimeter(word)) {
        strcpy(t->type, "DELIMETER");
    }

    else {
        strcpy(t->type, "INVALID");
    }
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

        if (code_sample[i] == ' ') {
            cur_word_buff[cur_word_buff_pos] = '\0';

            Token_set_type(&new_token, cur_word_buff);
            strcpy(new_token.value, cur_word_buff);

            TokenArr_append(token_arr, new_token);

            cur_word_buff_pos = 0;
            continue;
        }

        cur_word_buff[cur_word_buff_pos++] = code_sample[i];

        if (code_sample[i + 1] == '\0') {
            cur_word_buff[cur_word_buff_pos] = '\0';

            Token_set_type(&new_token, cur_word_buff);
            strcpy(new_token.value, cur_word_buff);

            TokenArr_append(token_arr, new_token);
            break;
        }
    }

    return token_arr;
}

