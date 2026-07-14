#include "token_arr.h"

#include "../../utils/token/token.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TokenArr *token_arr_init(size_t cap) {
    if (cap == 0) {
        return NULL;
    }

    TokenArr *token_arr = malloc(sizeof *token_arr);
    if (!token_arr) {
        return NULL;
    }

    Token *items = malloc(cap * sizeof *items);
    if (!items) {
        free(token_arr);
        return NULL;
    }

    token_arr->items = items;
    token_arr->capacity = cap;
    token_arr->length = 0;

    return token_arr;
}

TokenArr_status token_arr_deinit(TokenArr **token_arr) {
    if (!token_arr || !*token_arr) {
        return TOKENARR_WRONG_PTR;
    }

    free((*token_arr)->items);
    free(*token_arr);
    *token_arr = NULL;

    return TOKENARR_OK;
}

TokenArr_status token_arr_append(TokenArr *token_arr, Token item) {
    if (!token_arr) {
        return TOKENARR_WRONG_PTR;
    }

    if (token_arr->length >= token_arr->capacity) {
        if (token_arr->capacity > SIZE_MAX / 2) {
            return TOKENARR_ERR_OVERFLOW;
        }

        size_t new_capacity = token_arr->capacity * 2;
        Token *new_items =
            realloc(token_arr->items, new_capacity * sizeof *new_items);

        if (!new_items) {
            return TOKENARR_ERR_MALLOC;
        }

        token_arr->items = new_items;
        token_arr->capacity = new_capacity;
    }

    token_arr->items[token_arr->length++] = item;

    return TOKENARR_OK;
}

TokenArr_status token_arr_swap(TokenArr *token_arr, size_t index1,
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

TokenArr_status token_arr_remove(TokenArr *token_arr, size_t index) {
    if (!token_arr) {
        return TOKENARR_WRONG_PTR;
    }

    if (index >= token_arr->length) {
        return TOKENARR_IDX_OUT_OF_BOUNDS;
    }

    TokenArr_status status = TOKENARR_OK;
    for (size_t i = index; i < token_arr->length - 1; ++i) {
        status = token_arr_swap(token_arr, i, i + 1);
        if (status != TOKENARR_OK) {
            return status;
        }
    }

    token_arr->length--;

    return TOKENARR_OK;
}

TokenArr_status token_arr_println(TokenArr *token_arr) {
    if (!token_arr) {
        return TOKENARR_WRONG_PTR;
    }

    for (size_t i = 0; i < token_arr->length; ++i) {
        token_println(&token_arr->items[i]);
    }

    printf("\n");
    return TOKENARR_OK;
}

TokenArr_status token_arr_get(TokenArr *token_arr, size_t index, Token *buff) {
    if (!token_arr || !buff) {
        return TOKENARR_WRONG_PTR;
    }

    if (index >= token_arr->length) {
        return TOKENARR_IDX_OUT_OF_BOUNDS;
    }

    *buff = token_arr->items[index];
    return TOKENARR_OK;
}
