#include "utils/Token.h"
#include "utils/TokenArr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_MAX_CAP         255
#define SAMPLE_CODE_FILENAME "c_code.c"

void Token_set_type(Token *t, const char *word);
TokenArr *lexeme(char *code_sample);
char *read_file(const char *filename);
void clear_str(char *str);
int is_language_feature(const char *str);

int main(void)
{
    char *file_content = read_file(SAMPLE_CODE_FILENAME);
    if (!file_content) {
        goto cleanup;
    }

    TokenArr *token_arr = lexeme(file_content);
    if (!token_arr) {
        goto cleanup;
    }

    TokenArr_println(token_arr);

cleanup:
    if (token_arr) {
        TokenArr_deinit(&token_arr);
    }

    if (file_content) {
        free(file_content);
    }

    return EXIT_SUCCESS;
}

void Token_set_type(Token *t, const char *word)
{
    if (is_hash(word)) {
        strcpy(t->type, "HASH");
    }

    else if (is_keyword(word)) {
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
    if (!code_sample) {
        return NULL;
    }

    size_t code_sample_len = strlen(code_sample);
    TokenArr *token_arr = TokenArr_init(code_sample_len);
    if (!token_arr) {
        return NULL;
    }

    char cur_word_buff[WORD_MAX_CAP] = {0};
    size_t cur_word_buff_pos = 0;

    char ahead_word_buff[WORD_MAX_CAP] = {0};

    TokenType cur_token_type;
    TokenType ahead_token_type;

    size_t j = 0;
    for (size_t i = 0; i < code_sample_len; ++i) {
        j = i + 1;
        Token new_token = {0};
        Token ahead_token = {0};

        cur_word_buff[cur_word_buff_pos++] = code_sample[i];
        ahead_word_buff[0] = code_sample[j];

        if (code_sample[i] == '\n') {
            continue;
        }

        if (is_language_feature(ahead_word_buff)) {
            Token_set_type(&new_token, cur_word_buff);
            Token_set_type(&ahead_token, ahead_word_buff);

            strcpy(new_token.value, cur_word_buff);
            strcpy(ahead_token.value, ahead_word_buff);

            clear_str(cur_word_buff);
            clear_str(ahead_word_buff);

            TokenArr_append(token_arr, new_token);
            TokenArr_append(token_arr, ahead_token);

            cur_word_buff_pos = 0;
            continue;
        }

        if (code_sample[i] == ' ') {
            Token_set_type(&new_token, cur_word_buff);
            strcpy(new_token.value, cur_word_buff);

            clear_str(cur_word_buff);

            TokenArr_append(token_arr, new_token);

            cur_word_buff_pos = 0;
            continue;
        }

        if (is_language_feature(cur_word_buff)) {
            Token_set_type(&new_token, cur_word_buff);
            strcpy(new_token.value, cur_word_buff);

            clear_str(cur_word_buff);

            TokenArr_append(token_arr, new_token);

            cur_word_buff_pos = 0;
            continue;
        }
    }

    return token_arr;
}

char *read_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);

    long size = ftell(file);

    rewind(file);

    char *buffer = malloc((size_t)size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, (size_t)size, file);

    buffer[size] = '\0';

    fclose(file);

    return buffer;
}

void clear_str(char *str)
{
    for (size_t i = 0; str[i] != '\0'; ++i) {
        str[i] = 0;
    }
}

int is_language_feature(const char *str)
{
    if (is_hash(str) || is_keyword(str) || is_operator(str) || is_number(str) ||
        is_delimeter(str)) {
        return 1;
    }

    return 0;
}
