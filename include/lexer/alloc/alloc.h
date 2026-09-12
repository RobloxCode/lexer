#ifndef ALLOC_H
#define ALLOC_H

#include <stddef.h>

/**
 * @brief Safe wrapper around malloc, terminates the program if
 *        allocation fails
 *
 * @param size Number of bytes to allocate
 *
 * @return Pointer to allocated memory
 */
void *xmalloc(size_t size);

/**
 * @brief Safe wrapper around calloc, terminates the program if
 *        allocation fails
 *
 * @param nmemb Number of items being allocated
 * @param size Size of each item in bytes
 *
 * @return Pointer to allocated, zero-initialized memory
 */
void *xcalloc(size_t nmemb, size_t size);

/**
 * @brief Safe wrapper arond realloc, terminates the program if
 *        reallocation fails
 *
 * @param src Pointer to data being reallocated
 * @param size New buffer size in bytes
 *
 * @return Pointer to the resized memory
 */
void *xrealloc(void *src, size_t size);

#endif
