#ifndef LEXER_TOKEN_ARR_H
#define LEXER_TOKEN_ARR_H

/**
 * @file token_arr.h
 * @brief Growable array of Token values, used by the Lexer to store its
 *        output.
 *
 * Tokens are stored by value, so the array owns all of its data: releasing it
 * with token_arr_deinit() is the only cleanup needed.
 */

/*
 * Makes GCC and Clang warn when the status returned by a function is ignored.
 * Expands to nothing on other compilers.
 */
#if defined(__GNUC__) || defined(__clang__)
    #define LEXER_WARN_UNUSED __attribute__((warn_unused_result))
#else
    #define LEXER_WARN_UNUSED
#endif

#include "lexer/token.h"

#include <stddef.h>

/**
 * @brief Result of a TokenArr operation. TOKENARR_OK mean
 *        success, every other value is an error.
 */
typedef enum {
    /** The operation completed successfully. */
    TOKENARR_OK,

    /** A required pointer argument was NULL. */
    TOKENARR_WRONG_PTR,

    /**
     * Reserved for a failed initial allocation. It is not returned at the
     * moment: the allocation wrappers terminate the program instead.
     */
    TOKENARR_ERR_MALLOC,

    /**
     * Reserved for a failed reallocation while growing. It is not returned at
     * the moment: the allocation wrappers terminate the program instead.
     */
    TOKENARR_ERR_REALLOC,

    /** The capacity cannot be doubled without overflowing size_t. */
    TOKENARR_ERR_OVERFLOW,

    /**
     * Reserved for an invalid capacity. It is not returned at the moment:
     * token_arr_init() reports a capacity of zero by returning NULL.
     */
    TOKENARR_ERR_INVALID_SIZE,

    /** The given index is not smaller than the length of the array. */
    TOKENARR_IDX_OUT_OF_BOUNDS,
} TokenArrStatus;

/**
 * @brief Dynamic array of Token values that grows automatically.
 *
 * The fields can be read directly, but they must only be changed through the
 * token_arr_* functions, which keep them consistent with each other.
 */
typedef struct TokenArr {
    /**
     * Heap-allocated buffer with room for capacity tokens. Only the first
     * length slots hold valid tokens. The buffer may move whenever the array
     * grows, so do not keep pointers into it across a call to
     * token_arr_append().
     */
    Token *items;

    /** Number of token slots currently allocated. */
    size_t capacity;

    /** Number of token slots currently in use (the valid elements). */
    size_t length;
} TokenArr;

/**
 * @brief Allocate and initialize a new TokenArr.
 *
 * If memory runs out the program is terminated instead of returning NULL
 *
 * @param cap Number of token slots to reserve up front. Must be greater than
 *            zero. The array grows on its own when it fills up.
 *
 * @return A heap-allocated TokenArr with length 0, or NULL if cap is zero. The
 *         caller owns the result and must release it with token_arr_deinit().
 */
TokenArr *token_arr_init(const size_t cap);

/**
 * @brief Frees a TokenArr and its backing buffer.
 *
 * The pointer is set to NULL after freeing, so a second call on the same
 * variable is rejected instead of freeing the memory twice.
 *
 * @param token_arr Address of the TokenArr pointer to release.
 *
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if token_arr or
 *         *token_arr is NULL.
 */
TokenArrStatus token_arr_deinit(TokenArr **token_arr) LEXER_WARN_UNUSED;

/**
 * @brief Adds a copy of a Token at the end of the array.
 *
 * When the array is full its capacity is doubled first, which can move the
 * buffer and invalidate pointers into items. If memory runs out during that
 * growth the program is terminated.
 *
 * @param token_arr Array to append to.
 * @param item      Token to copy into the array. The array keeps its own copy,
 *                  so the original can be changed or discarded afterwards.
 *
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if token_arr or item is
 *         NULL, TOKENARR_ERR_OVERFLOW if the capacity cannot be doubled
 *         without overflowing size_t.
 */
TokenArrStatus token_arr_append(TokenArr *token_arr,
                                const Token *item) LEXER_WARN_UNUSED;

/**
 * @brief Exchanges the tokens stored at two positions.
 *
 * Swapping a position with itself is allowed and changes nothing.
 *
 * @param token_arr Array to modify.
 * @param index1    Position of the first token.
 * @param index2    Position of the second token.
 *
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if token_arr is NULL,
 *         TOKENARR_IDX_OUT_OF_BOUNDS if either index is >= length. The array
 *         is left unchanged on error.
 */
static inline TokenArrStatus token_arr_swap(TokenArr *token_arr, size_t index1,
                                            size_t index2) LEXER_WARN_UNUSED;

static inline TokenArrStatus token_arr_swap(TokenArr *token_arr, size_t index1,
                                            size_t index2) {
    if (!token_arr) {
        return TOKENARR_WRONG_PTR;
    }

    if (index1 >= token_arr->length || index2 >= token_arr->length) {
        return TOKENARR_IDX_OUT_OF_BOUNDS;
    }

    Token tmp = token_arr->items[index1];
    token_arr->items[index1] = token_arr->items[index2];
    token_arr->items[index2] = tmp;

    return TOKENARR_OK;
}

/**
 * @brief Removes the token at a position, keeping the order of the rest.
 *
 * Every token after idx moves one position down, so the cost grows with the
 * number of tokens that follow. The length decreases by one, the capacity does
 * not change.
 *
 * @param token_arr Array to modify.
 * @param idx       Position of the token to remove.
 *
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if token_arr is NULL,
 *         TOKENARR_IDX_OUT_OF_BOUNDS if idx is >= length (this includes any
 *         index on an empty array). The array is left unchanged on error.
 */
TokenArrStatus token_arr_remove(TokenArr *token_arr,
                                const size_t idx) LEXER_WARN_UNUSED;

/**
 * @brief Prints every token of the array to stdout, one per line, followed by
 *        an empty line.
 *
 * Each line is printed with token_println(). Meant for debugging.
 *
 * @param token_arr Array to print.
 *
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if token_arr is NULL.
 */
TokenArrStatus token_arr_println(const TokenArr *token_arr) LEXER_WARN_UNUSED;

/**
 * @brief Copies the token at a position into a caller-provided variable.
 *
 * The copy is independent from the array, so it stays valid even after the
 * array grows or is released.
 *
 * @param token_arr Array to read from.
 * @param index     Position of the token to fetch.
 * @param buff      Where the copy is written. Must not be NULL.
 *
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if token_arr or buff is
 *         NULL, TOKENARR_IDX_OUT_OF_BOUNDS if index is >= length. buff is left
 *         untouched on error.
 */
static inline TokenArrStatus token_arr_get(const TokenArr *token_arr,
                                           size_t index,
                                           Token *buff) LEXER_WARN_UNUSED;

static inline TokenArrStatus token_arr_get(const TokenArr *token_arr,
                                           size_t index, Token *buff) {
    if (!token_arr || !buff) {
        return TOKENARR_WRONG_PTR;
    }

    if (index >= token_arr->length) {
        return TOKENARR_IDX_OUT_OF_BOUNDS;
    }

    *buff = token_arr->items[index];
    return TOKENARR_OK;
}

/**
 * @brief Returns the number of tokens stored in the array.
 *
 * @param ta Array to query.
 *
 * @return Number of valid tokens, or 0 if ta is NULL
 */
static inline size_t token_arr_len(const TokenArr *ta) {
    if (!ta) {
        return 0;
    }

    return ta->length;
}

#endif
