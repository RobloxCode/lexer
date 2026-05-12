#ifndef TOKENARR_H
#define TOKENARR_H

#include <stddef.h>
#include "Token.h"

typedef enum {
    TOKENARR_OK                   = 0,
    TOKENARR_WRONG_PTR            = 10,
    TOKENARR_ERR_MALLOC           = 20,
    TOKENARR_ERR_REALLOC          = 21,
    TOKENARR_ERR_OVERFLOW         = 22,
    TOKENARR_ERR_INVALID_SIZE     = 23,
    TOKENARR_IDX_OUT_OF_BOUNDS    = 30,
} TokenArr_status;

typedef struct TokenArr {
    Token *items;
    size_t capacity;
    size_t length;
} TokenArr;

TokenArr *TokenArr_init(size_t init_capacity);
TokenArr_status TokenArr_deinit(TokenArr** token_arr);
TokenArr_status TokenArr_append(TokenArr* token_arr, Token item);
TokenArr_status TokenArr_swap(TokenArr* token_arr,
                              size_t idx1,
                              size_t idx2);
TokenArr_status TokenArr_remove(TokenArr* token_arr, size_t idx);
TokenArr_status TokenArr_println(TokenArr* token_arr);
TokenArr_status TokenArr_get(TokenArr* token_arr,
                                  size_t idx,
                                  Token* buff);

#endif
