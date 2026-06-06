#include "../../utils/Token.h"

#include <stdio.h>

void test_is_number(const char *s);

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
    return 0;
}

void test_is_number(const char *s) {
    if (is_number(s)) {
        printf("%s is a number\n", s);
    } else {
        printf("%s is not a number\n", s);
    }
}
