#ifndef TOKEN_ARR_H
#define TOKEN_ARR_H

#include "token.h"

#include <stddef.h>

typedef enum {
    TOKENARR_OK,
    TOKENARR_WRONG_PTR,
    TOKENARR_ERR_MALLOC,
    TOKENARR_ERR_REALLOC,
    TOKENARR_ERR_OVERFLOW,
    TOKENARR_ERR_INVALID_SIZE,
    TOKENARR_IDX_OUT_OF_BOUNDS,
} TokenArr_status;

typedef struct TokenArr {
    Token *items;
    size_t capacity;
    size_t length;
} TokenArr;

TokenArr *token_arr_init(size_t cap);
TokenArr_status token_arr_deinit(TokenArr **token_arr);
TokenArr_status token_arr_append(TokenArr *token_arr, Token item);
TokenArr_status token_arr_swap(TokenArr *token_arr, size_t idx1, size_t idx2);
TokenArr_status token_arr_remove(TokenArr *token_arr, size_t idx);
TokenArr_status token_arr_println(TokenArr *token_arr);
TokenArr_status token_arr_get(TokenArr *token_arr, size_t idx, Token *buff);

#endif
