#ifndef TOKENARR_H
#define TOKENARR_H

#include "Token.h"

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

TokenArr *TokenArr_init(size_t init_capacity);
TokenArr_status TokenArr_deinit(TokenArr **token_arr);
TokenArr_status TokenArr_append(TokenArr *token_arr, Token item);
TokenArr_status TokenArr_swap(TokenArr *token_arr, size_t idx1, size_t idx2);
TokenArr_status TokenArr_remove(TokenArr *token_arr, size_t idx);
TokenArr_status TokenArr_println(TokenArr *token_arr);
TokenArr_status TokenArr_get(TokenArr *token_arr, size_t idx, Token *buff);

#endif
