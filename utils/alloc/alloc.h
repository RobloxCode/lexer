#ifndef ALLOC_H
#define ALLOC_H

#include <stddef.h>

void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
void *xrealloc(void *src, size_t size);

#endif
