#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

/*
 * Tiny test helpers shared by every test file in this folder.
 *
 * Include this header once per test file (it defines the counters as static
 * variables, so each test executable keeps its own totals).
 *
 * Failures are always printed to stderr. Passing checks are only printed when
 * the file is compiled with -DTEST_VERBOSE (make test V=1).
 *
 * Every macro evaluates its arguments exactly once.
 */

#include <stdio.h>
#include <string.h>

static int tests_run = 0;
static int tests_failed = 0;

#ifdef TEST_VERBOSE
    #define TEST_PASS(msg) printf("  [PASS] %s\n", msg)
#else
    #define TEST_PASS(msg) ((void)0)
#endif

#define TEST_FAIL(...)                                                         \
    do {                                                                       \
        tests_failed++;                                                        \
        fprintf(stderr, "  [FAIL] %s:%d: ", __FILE__, __LINE__);               \
        fprintf(stderr, __VA_ARGS__);                                          \
        fprintf(stderr, "\n");                                                 \
    } while (0)

#define ASSERT_TRUE(condition)                                                 \
    do {                                                                       \
        tests_run++;                                                           \
        if (condition) {                                                       \
            TEST_PASS(#condition);                                             \
        } else {                                                               \
            TEST_FAIL("expected true: %s", #condition);                        \
        }                                                                      \
    } while (0)

#define ASSERT_FALSE(condition)                                                \
    do {                                                                       \
        tests_run++;                                                           \
        if (!(condition)) {                                                    \
            TEST_PASS("!(" #condition ")");                                    \
        } else {                                                               \
            TEST_FAIL("expected false: %s", #condition);                       \
        }                                                                      \
    } while (0)

/* Compares any integer or enum values (signed or unsigned). */
#define ASSERT_EQ_INT(actual, expected)                                        \
    do {                                                                       \
        long long a_ = (long long)(actual);                                    \
        long long e_ = (long long)(expected);                                  \
        tests_run++;                                                           \
        if (a_ == e_) {                                                        \
            TEST_PASS(#actual " == " #expected);                               \
        } else {                                                               \
            TEST_FAIL("%s: got %lld, expected %lld", #actual, a_, e_);         \
        }                                                                      \
    } while (0)

/* Compares size_t values without sign-compare warnings. */
#define ASSERT_EQ_SIZE(actual, expected)                                       \
    do {                                                                       \
        unsigned long long a_ = (unsigned long long)(actual);                  \
        unsigned long long e_ = (unsigned long long)(expected);                \
        tests_run++;                                                           \
        if (a_ == e_) {                                                        \
            TEST_PASS(#actual " == " #expected);                               \
        } else {                                                               \
            TEST_FAIL("%s: got %llu, expected %llu", #actual, a_, e_);         \
        }                                                                      \
    } while (0)

#define ASSERT_STR_EQ(actual, expected)                                        \
    do {                                                                       \
        const char *a_ = (actual);                                             \
        const char *e_ = (expected);                                           \
        tests_run++;                                                           \
        if (a_ && e_ && strcmp(a_, e_) == 0) {                                 \
            TEST_PASS(#actual " == " #expected);                               \
        } else {                                                               \
            TEST_FAIL("%s: got \"%s\", expected \"%s\"", #actual,              \
                      a_ ? a_ : "(null)", e_ ? e_ : "(null)");                 \
        }                                                                      \
    } while (0)

#define ASSERT_NULL(ptr)     ASSERT_TRUE((ptr) == NULL)
#define ASSERT_NOT_NULL(ptr) ASSERT_TRUE((ptr) != NULL)

/*
 * Use at the top of a test function when the rest of the test cannot run
 * without the pointer (the test function must return void).
 */
#define REQUIRE_NOT_NULL(ptr)                                                  \
    do {                                                                       \
        tests_run++;                                                           \
        if ((ptr) == NULL) {                                                   \
            TEST_FAIL("required non-NULL: %s", #ptr);                          \
            return;                                                            \
        }                                                                      \
        TEST_PASS(#ptr " != NULL");                                            \
    } while (0)

/* Runs a `static void name(void)` test function. */
#define RUN_TEST(test)                                                         \
    do {                                                                       \
        printf("[TEST] %s\n", #test);                                          \
        test();                                                                \
    } while (0)

/* Prints the totals and returns the process exit code. */
static int test_summary(void) {
    printf("\nTests run:    %d\n", tests_run);
    printf("Tests passed: %d\n", tests_run - tests_failed);
    printf("Tests failed: %d\n", tests_failed);

    return tests_failed == 0 ? 0 : 1;
}

#endif
