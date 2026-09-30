#include "lexer/alloc/alloc.h"

#include <stdio.h>
#include <stdlib.h>

void *xmalloc(const size_t size) {
    void *ptr = malloc(size);

    if (!ptr) {
        fprintf(stderr, "fatal: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

void *xcalloc(const size_t nmemb, const size_t size) {
    void *ptr = calloc(nmemb, size);

    if (!ptr) {
        fprintf(stderr, "fatal: calloc failed\n");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

void *xrealloc(void *src, const size_t size) {
    if (size == 0) {
        free(src);
        return NULL;
    }

    void *ptr = realloc(src, size);

    if (!ptr) {
        fprintf(stderr, "fatal: realloc failed\n");
        exit(EXIT_FAILURE);
    }

    return ptr;
}
