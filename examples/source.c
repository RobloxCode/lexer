#include <stdio.h>

int some_fn() {
    int a, b, c, x, y, s;
    // this is a one line comment
    // another one line comment
    puts("hi");
    a /= 2;
    b = a / c;
    x = 'a';
    y = '"';
    /*/ not a comment end */ int z;
    s = "a\"b";

    struct bar;

    /*
     *
     *   5 lines comment
     *
     * */

    int var = 10;
    double dec = 3.33f;

    char newline = '\'';
    char tab = '\t';

    puts("hello");
    puts("he\"llo");

    somefn('t');
    somefn('\t');

    return 0;
}

/*
