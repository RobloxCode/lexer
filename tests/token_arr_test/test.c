#include "lexer/token_arr/token_arr.h"

#include <stdio.h>
#include <stdlib.h>

static int tests_run = 0;
static int fail = 0;

#define ASSERT_EQ(a, b)                                                        \
    do {                                                                       \
        tests_run++;                                                           \
        if ((a) != (b)) {                                                      \
            tests_failed++;                                                    \
            printf("FAIL %s:%d: %s != %s\n", __FILE__, __LINE__, #a, #b);      \
        }                                                                      \
    } while (0)

int main() {
    TokenArr_status status = TOKENARR_OK;
    TokenArr *token_arr = token_arr_init(10);
    if (!token_arr) {
        return 1;
    }

    status = token_arr_append(token_arr, &(Token){.type = TOK_KW_INT});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status = token_arr_append(token_arr, &(Token){.type = TOK_IDENTIFIER});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status = token_arr_append(token_arr, &(Token){.type = TOK_ASSIGN});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status = token_arr_append(token_arr, &(Token){.type = TOK_NUMBER});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status = token_arr_append(token_arr, &(Token){.type = TOK_ADD_ASSIGN});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status = token_arr_append(token_arr, &(Token){.type = TOK_NUMBER});
    if (status != TOKENARR_OK) {
        goto cleanup;
    }

    status = token_arr_append(token_arr, &(Token){.type = TOK_SEMICOLON});
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
        if ((status = token_arr_deinit(&token_arr)) != TOKENARR_OK) {
            fprintf(stderr, "could not deinitialize the token array\n");
            exit(1);
        }
    }

    if (status != TOKENARR_OK) {
        fail = 1;
        printf("status: %d\n", status);
    }

    return fail ? EXIT_FAILURE : EXIT_SUCCESS;
}
