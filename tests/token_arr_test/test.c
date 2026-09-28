#include "lexer/token/token.h"
#include "lexer/token_arr/token_arr.h"

#include <stdio.h>
#include <stdlib.h>

static int tests_run = 0;
static int tests_failed = 0;

#define RUN_TEST(test)                                                         \
    do {                                                                       \
        TokenArrStatus status = (test);                                        \
        tests_run++;                                                           \
                                                                               \
        if (status != TOKENARR_OK) {                                           \
            tests_failed++;                                                    \
            fprintf(stderr, "[FAIL] %s\n", #test);                             \
        } else {                                                               \
            printf("[PASS] %s\n", #test);                                      \
        }                                                                      \
    } while (0)

#define ASSERT_EQ(actual, expected)                                            \
    do {                                                                       \
        tests_run++;                                                           \
                                                                               \
        if ((actual) != (expected)) {                                          \
            tests_failed++;                                                    \
            fprintf(stderr, "[FAIL] %s:%d: %s != %s\n", __FILE__, __LINE__,    \
                    #actual, #expected);                                       \
        } else {                                                               \
            printf("[PASS] %s == %s\n", #actual, #expected);                   \
        }                                                                      \
    } while (0)

#define ASSERT_TRUE(condition)                                                 \
    do {                                                                       \
        tests_run++;                                                           \
                                                                               \
        if (!(condition)) {                                                    \
            tests_failed++;                                                    \
            fprintf(stderr, "[FAIL] %s:%d: %s\n", __FILE__, __LINE__,          \
                    #condition);                                               \
        } else {                                                               \
            printf("[PASS] %s\n", #condition);                                 \
        }                                                                      \
    } while (0)

#define ASSERT_STATUS(expression, expected)                                    \
    do {                                                                       \
        TokenArrStatus status = (expression);                                  \
        tests_run++;                                                           \
                                                                               \
        if (status != (expected)) {                                            \
            tests_failed++;                                                    \
            fprintf(stderr, "[FAIL] %s:%d: %s returned %d, expected %d\n",     \
                    __FILE__, __LINE__, #expression, status, (expected));      \
        } else {                                                               \
            printf("[PASS] %s == %s\n", #expression, #expected);               \
        }                                                                      \
    } while (0)

int main(void) {
    TokenArr *token_arr = token_arr_init(10);

    ASSERT_TRUE(token_arr != NULL);

    if (token_arr == NULL) {
        fprintf(stderr, "Could not initialize token array\n");
        return EXIT_FAILURE;
    }

    /*
     * Append tokens
     */

    RUN_TEST(token_arr_append(token_arr, &(Token){.type = TOK_KW_INT}));

    RUN_TEST(token_arr_append(token_arr, &(Token){.type = TOK_IDENTIFIER}));

    RUN_TEST(token_arr_append(token_arr, &(Token){.type = TOK_ASSIGN}));

    RUN_TEST(token_arr_append(token_arr, &(Token){.type = TOK_NUMBER}));

    RUN_TEST(token_arr_append(token_arr, &(Token){.type = TOK_ADD_ASSIGN}));

    RUN_TEST(token_arr_append(token_arr, &(Token){.type = TOK_NUMBER}));

    RUN_TEST(token_arr_append(token_arr, &(Token){.type = TOK_SEMICOLON}));

    /*
     * Verify length after appending
     */

    ASSERT_EQ(token_arr->length, 7);
    ASSERT_EQ(token_arr_len(token_arr), 7);

    /*
     * Remove first token
     */

    RUN_TEST(token_arr_remove(token_arr, 0));

    ASSERT_EQ(token_arr->length, 6);

    /*
     * Print current tokens
     */

    printf("\nExample expression:\n");

    RUN_TEST(token_arr_println(token_arr));

    /*
     * Remove first token again
     */

    RUN_TEST(token_arr_remove(token_arr, 0));

    ASSERT_EQ(token_arr->length, 5);

    /*
     * Remove last token
     */

    RUN_TEST(token_arr_remove(token_arr, token_arr->length - 1));

    ASSERT_EQ(token_arr->length, 4);

    /*
     * Print remaining tokens
     */

    printf("\nRemaining tokens:\n");

    RUN_TEST(token_arr_println(token_arr));

    /*
     * Test invalid operations
     *
     * Uncomment these if your API is expected to return
     * an error status for invalid indexes.
     */

    /*
    ASSERT_STATUS(
        token_arr_remove(token_arr, 100),
        TOKENARR_OUT_OF_BOUNDS
    );
    */

    /*
     * Cleanup
     */

    ASSERT_STATUS(token_arr_deinit(&token_arr), TOKENARR_OK);

    ASSERT_TRUE(token_arr == NULL);

    /*
     * Test summary
     */

    printf("\n");
    printf("Tests run:    %d\n", tests_run);
    printf("Tests passed: %d\n", tests_run - tests_failed);
    printf("Tests failed: %d\n", tests_failed);

    return tests_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
