#ifndef TOKEN_ARR_H
#define TOKEN_ARR_H

#include "../token/token.h"

#include <stddef.h>

/**
 * @brief Status codes returned by TokenArr operations.
 */
typedef enum {
    TOKENARR_OK,                /**< Operation completed successfully. */
    TOKENARR_WRONG_PTR,         /**< A required pointer argument was NULL. */
    TOKENARR_ERR_MALLOC,        /**< Initial heap allocation failed. */
    TOKENARR_ERR_REALLOC,       /**< Growing the backing buffer failed. */
    TOKENARR_ERR_OVERFLOW,      /**< Capacity/length calculation would overflow
                                     size_t. */
    TOKENARR_ERR_INVALID_SIZE,  /**< Requested capacity was zero or otherwise
                                     invalid. */
    TOKENARR_IDX_OUT_OF_BOUNDS, /**< Supplied index is >= length. */
} TokenArr_status;

/**
 * @brief Dynamic, growable array of Token values.
 *
 * @var items    Pointer to the heap-allocated backing buffer.
 * @var capacity Number of Token slots currently allocated.
 * @var length   Number of Token slots currently in use.
 */
typedef struct TokenArr {
    Token *items;
    size_t capacity;
    size_t length;
} TokenArr;

/**
 * @brief Allocate and initialize a new TokenArr.
 *
 * @param cap Initial capacity to reserve (number of Token slots).
 * @return Pointer to a heap-allocated TokenArr, or NULL on allocation failure
 *         or if @p cap is invalid.
 */
TokenArr *token_arr_init(size_t cap);

/**
 * @brief Free a TokenArr and its backing buffer.
 *
 * Sets *token_arr to NULL after freeing to prevent dangling access.
 *
 * @param token_arr Pointer to the TokenArr pointer to deinitialize.
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if @p token_arr
 *         or *token_arr is NULL.
 */
TokenArr_status token_arr_deinit(TokenArr **token_arr);

/**
 * @brief Append a Token to the end of the array, growing capacity if needed.
 *
 * @param token_arr Array to append to.
 * @param item      Token value to copy into the array.
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if @p token_arr is NULL,
 *         TOKENARR_ERR_REALLOC if growth was needed and reallocation failed,
 *         TOKENARR_ERR_OVERFLOW if growing would overflow size_t.
 */
TokenArr_status token_arr_append(TokenArr *token_arr, Token item);

/**
 * @brief Swap the Tokens at two indices in place.
 *
 * @param token_arr Array to operate on.
 * @param idx1      First index.
 * @param idx2      Second index.
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if @p token_arr is NULL,
 *         TOKENARR_IDX_OUT_OF_BOUNDS if either index is >= length.
 */
TokenArr_status token_arr_swap(TokenArr *token_arr, size_t idx1, size_t idx2);

/**
 * @brief Remove the Token at the given index, shifting subsequent elements
 * down.
 *
 * @param token_arr Array to operate on.
 * @param idx       Index of the element to remove.
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if @p token_arr is NULL,
 *         TOKENARR_IDX_OUT_OF_BOUNDS if @p idx >= length.
 */
TokenArr_status token_arr_remove(TokenArr *token_arr, size_t idx);

/**
 * @brief Print the contents of the array to stdout for debugging.
 *
 * @param token_arr Array to print.
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if @p token_arr is NULL.
 */
TokenArr_status token_arr_println(TokenArr *token_arr);

/**
 * @brief Copy the Token at a given index into a caller-provided buffer.
 *
 * @param token_arr Array to read from.
 * @param idx       Index of the element to fetch.
 * @param buff      Destination buffer to receive a copy of the Token.
 * @return TOKENARR_OK on success, TOKENARR_WRONG_PTR if @p token_arr or
 *         @p buff is NULL, TOKENARR_IDX_OUT_OF_BOUNDS if @p idx >= length.
 */
TokenArr_status token_arr_get(TokenArr *token_arr, size_t idx, Token *buff);

#endif
