#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int tests_run = 0;
static int tests_failed = 0;

#define ASSERT_EQ(expected, actual)                                            \
    do {                                                                       \
        tests_run++;                                                           \
        if ((expected) != (actual)) {                                          \
            tests_failed++;                                                    \
            printf("[FAIL] %s:%d: %s != %s\n", __FILE__, __LINE__, #expected,  \
                   #actual);                                                   \
        } else {                                                               \
            printf("[PASS] %s == %s\n", #expected, #actual);                   \
        }                                                                      \
    } while (0)

// These functions are copied and pasted from the token.c file.
bool is_digit(const int c) {
    return c >= '0' && c <= '9';
}

bool is_number(const char *s) {
    size_t i = 0;
    int dots_counter = 0;

    if (!strlen(s)) {
        return false;
    }

    if (s[0] == '.' || s[strlen(s) - 1] == '.') {
        return false;
    }

    if (s[0] == '+' || s[0] == '-') {
        i = 1;

        if (s[i] == '\0') {
            return false;
        }
    }

    for (; s[i] != '\0'; ++i) {
        if (s[i] == '.') {
            dots_counter++;
            continue;
        }

        if (!is_digit(s[i])) {
            return false;
        }
    }

    if (dots_counter > 1) {
        return false;
    }

    return true;
}

void test_is_number(const char *num, bool expected);

int main(void) {
    test_is_number("12345", true);
    test_is_number("+12345", true);
    test_is_number("-12345", true);
    test_is_number("  12345  ", false);
    test_is_number("u12345", false);
    test_is_number("1.2345", true);
    test_is_number("1.2.3.4.5", false);
    test_is_number("12345;", false);
    test_is_number("", false);
    test_is_number(" ", false);
    test_is_number("+", false);
    test_is_number("-", false);
    test_is_number("3.", false);
    test_is_number(".", false);
    test_is_number(".3", false);

    printf("Tests run:    %d\n", tests_run);
    printf("Tests passed: %d\n", tests_run - tests_failed);
    printf("Tests failed: %d\n", tests_failed);

    return tests_failed > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

void test_is_number(const char *num, bool expected) {
    bool actual = is_number(num);

    if (actual == expected) {
        tests_run++;
        printf("[PASS] is_number(\"%s\")\n", num);
    } else {
        tests_run++;
        tests_failed++;
        printf("[FAIL] is_number(\"%s\")\n", num);
        printf("       Expected: %s\n", expected ? "true" : "false");
        printf("       Got:      %s\n", actual ? "true" : "false");
    }
}
