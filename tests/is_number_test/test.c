#include "../../utils/token/token.h"

#include <stdio.h>
#include <stdlib.h>

static int tests_run = 0, tests_failed = 0;

#define ASSERT_EQ(a, b)                                                        \
    do {                                                                       \
        tests_run++;                                                           \
        if ((a) != (b)) {                                                      \
            tests_failed++;                                                    \
            printf("FAIL %s:%d: %s != %s\n", __FILE__, __LINE__, #a, #b);      \
        }                                                                      \
    } while (0)

void test_is_number(const char *num);

int main(void) {
    test_is_number("12345");
    test_is_number("+12345");
    test_is_number("-12345");
    test_is_number("  12345  ");
    test_is_number("u12345");
    test_is_number("1.2345");
    test_is_number("1.2.3.4.5");
    test_is_number("12345;");
    test_is_number("");
    test_is_number(" ");

    return tests_failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

void test_is_number(const char *num) {
    ASSERT_EQ(is_number(num), true);
}
