#include "utils/Token.h"
#include "utils/TokenArr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_MAX_CAP         255
#define SAMPLE_CODE_FILENAME "c_code.c"

TokenArr *lexeme(char *code_sample);
char *read_file(const char *filename);
void clear_str(char *str);
int is_language_feature(const char *str);

int main(void) {
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

TokenArr *lexeme(char *code_sample) {
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

        if (code_sample[i] == ' ') {
            continue;
        }

        if (code_sample[i] == '\n') {
            continue;
        }

        cur_word_buff[cur_word_buff_pos++] = code_sample[i];
        ahead_word_buff[0] = code_sample[j];

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

        if (code_sample[j] == ' ') {
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

int is_language_feature(const char *str) {
    if (is_hash(str) || is_keyword(str) || is_operator(str)
        || is_delimeter(str)) {
        return 1;
    }

    return 0;
}
