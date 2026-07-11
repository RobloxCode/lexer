#ifndef STR_BUF_H
#define STR_BUF_H

#include <stddef.h>

/* Maximun number of elements in each StrBuf */
#define STR_BUF_MAX_CAP 255

/**
 * @brief String buffer made to manage stack allocated strings
 */
typedef struct {
    char items[STR_BUF_MAX_CAP]; /* < Characters in the string */
    size_t count;                /* < index to the last character */
} StrBuf;

/**
 * @brief Sets all the fields in a StrBuf to default
 *
 * @param sb Pointer to StrBuf
 */
void strbuf_init(StrBuf *sl);

/**
 * @brief Adds a character after the current last element
 *
 * @param sb Pointer to StrBuf
 * @param c  Character to be added
 */
int strbuf_push(StrBuf *sl, char c);

/**
 * @brief Sets a character at a given index
 *
 * @param sb Pointer to StrBuf
 * @param c  Character to be set
 * @param i  Index of the character being set
 */
int strbuf_set(StrBuf *sl, char c, size_t i);

/**
 * @brief Sets all the characters to 0
 *
 * @param sb Pointer to StrBuf
 */
void strbuf_clear(StrBuf *sl);

#endif
