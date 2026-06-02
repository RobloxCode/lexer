#include "utils/Token.h"
#include "utils/TokenArr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_MAX_CAP         255
#define SOURCE_CODE_FILENAME "c_code.c"

TokenArr *lexeme(char *src_code);
char *read_file(const char *filename);
void clear_str(char *str);
int is_language_feature(const char *word);

int main(void) {
    char *file_content = read_file(SOURCE_CODE_FILENAME);
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

TokenArr *lexeme(char *src_code) {
    if (!src_code) {
        return NULL;
    }

    size_t src_code_len = strlen(src_code);
    TokenArr *token_arr = TokenArr_init(src_code_len);
    if (!token_arr) {
        return NULL;
    }

    char cur_word_buff[WORD_MAX_CAP] = {0};
    size_t cur_word_buff_pos = 0;

    char ahead_word_buff[WORD_MAX_CAP] = {0};

    size_t j = 0;
    for (size_t i = 0; i < src_code_len; ++i) {
        j = i + 1;
        Token new_token = {0};

        if (src_code[i] == ' ') {
            continue;
        }

        if (src_code[i] == '\n') {
            continue;
        }

        cur_word_buff[cur_word_buff_pos++] = src_code[i];
        ahead_word_buff[0] = src_code[j];

        if (is_language_feature(cur_word_buff)) {
            Token_init(&new_token, cur_word_buff);

            clear_str(cur_word_buff);
            cur_word_buff_pos = 0;

            TokenArr_append(token_arr, new_token);

            continue;
        }

        if (is_language_feature(ahead_word_buff)) {
            Token_init(&new_token, cur_word_buff);

            clear_str(cur_word_buff);
            cur_word_buff_pos = 0;

            TokenArr_append(token_arr, new_token);

            continue;
        }

        if (src_code[j] == ' ') {
            Token_init(&new_token, cur_word_buff);

            clear_str(cur_word_buff);
            cur_word_buff_pos = 0;

            TokenArr_append(token_arr, new_token);

            continue;
        }
    }

    return token_arr;
}

char *read_file(const char *filename) {
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

void clear_str(char *str) {
    for (size_t i = 0; str[i] != '\0'; ++i) {
        str[i] = 0;
    }
}

int is_language_feature(const char *word) {
    if (is_hash(word) || is_keyword(word) || is_operator(word)
        || is_delimeter(word)) {
        return 1;
    }

    return 0;
}
