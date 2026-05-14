#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/TokenArr.h"

#define WORD_MAX_CAP 255

typedef enum {
    IDENTIFIER,
    KEYWORD,
    NUMBER,
    OPERATOR,
    DELIMETER,
    STRING,
    CHARACTER,
    COMMENT,
    ENDOFFILE,
} TokenType;

char *operators[] = {
    "+", "-", "*", "/", "%",
    "+=", "-=", "*=", "/=", "%=", "&=", "|=", "~=", "^=",
    "<<", ">>", "&", "|", "~", "^",
    "&&", "||", "!=", "==", "<", ">", "<=", ">=",
    "++", "--",
};

char delimeters[] = "(){}[],;";

char *keywords[] = {
    "if", "else", "switch", "case", "default",
    "for", "while", "do", "break", "continue",
    "goto", "return",
    "int", "char", "float", "double", "void",
    "short", "long", "signed", "unsigned", "_Bool",
    "auto", "register", "static", "extern", "typedef",
    "const", "volatile", "restrict",
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

        if (code_sample[i] == ' ') {
            cur_word_buff[cur_word_buff_pos] = '\0';

            strcpy(new_token.type, "NULL");
            strcpy(new_token.value, cur_word_buff);
            TokenArr_append(token_arr, new_token);

            cur_word_buff_pos = 0;
            continue;
        }

        cur_word_buff[cur_word_buff_pos++] = code_sample[i];

        if (code_sample[i + 1] == '\0') {
            cur_word_buff[cur_word_buff_pos] = '\0';

            strcpy(new_token.type, "NULL");
            strcpy(new_token.value, cur_word_buff);
            TokenArr_append(token_arr, new_token);
            break;
        }
    }

    return token_arr;
}

