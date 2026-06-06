

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
