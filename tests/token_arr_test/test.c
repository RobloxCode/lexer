#include "../../utils/token_arr.h"

#include <stdio.h>
#include <stdlib.h>

static int fail;

int main() {
    TokenArr_status status = TOKENARR_OK;
    TokenArr *token_arr = token_arr_init(10);
    if (!token_arr) {
        return 1;
    }

    // int number = 3 + 2;
    status =
        token_arr_append(token_arr, (Token){.type = "KEYWORD", .value = "int"});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status =
        token_arr_append(token_arr, (Token){.type = "ID", .value = "number"});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status =
        token_arr_append(token_arr, (Token){.type = "ASSIGN", .value = "="});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status =
        token_arr_append(token_arr, (Token){.type = "NUMBER", .value = "3"});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status = token_arr_append(token_arr, (Token){.type = "PLUS", .value = "+"});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status =
        token_arr_append(token_arr, (Token){.type = "NUMBER", .value = "2"});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status =
        token_arr_append(token_arr, (Token){.type = "SEMICOLON", .value = ";"});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status = token_arr_remove(token_arr, 0);
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    printf("example expression: int number = 3 + 2;\n");
    status = token_arr_println(token_arr);
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status = token_arr_remove(token_arr, 0);
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status = token_arr_remove(token_arr, token_arr->length - 1);
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status = token_arr_println(token_arr);
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

cleanup:
    if (token_arr) {
        token_arr_deinit(&token_arr);
    }

    if (status != TOKENARR_OK) {
        fail = 1;
        printf("status: %d\n", status);
    }

    return fail ? EXIT_FAILURE : EXIT_SUCCESS;
}
