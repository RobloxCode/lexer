#include <stdio.h>
#include <stdlib.h>

#define ASSERT_MSG(cond, fmt, ...)                                             \
    do {                                                                       \
        if (!(cond)) {                                                         \
            fprintf(stderr,                                                    \
                    "Assertion failed: (%s), file %s, line %d\n" fmt "\n",     \
                    #cond, __FILE__, __LINE__, ##__VA_ARGS__);                 \
            abort();                                                           \
        }                                                                      \
    } while (0)
