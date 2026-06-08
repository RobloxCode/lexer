#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

#define SOURCE_CODE_FILENAME "src/source.c"

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

int main(void) {
    char *file_content = NULL;
    TokenArr *token_arr = NULL;

    file_content = read_file(SOURCE_CODE_FILENAME);
    if (!file_content) {
        fprintf(stderr, "failed to open %s\n", SOURCE_CODE_FILENAME);
        goto cleanup;
    }

    token_arr = lexeme(file_content);
    if (!token_arr) {
        goto cleanup;
    }

    token_arr_println(token_arr);

cleanup:
    if (token_arr) {
        token_arr_deinit(&token_arr);
    }

    if (file_content) {
        free(file_content);
    }

    return EXIT_SUCCESS;
}
