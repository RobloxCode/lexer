// TODO: add some macros to make testing easier, like "ASSERT_MSG", or
// "RUN_TEST"

/* You have to create the variables tests_run, tests_failed
 * in the file that use this macros
 *
 * Recommended declarations:
 * static int tests_run = 0;
 * static int tests_failed = 0;
 */
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
        TokenArr_status status = (expression);                                 \
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
