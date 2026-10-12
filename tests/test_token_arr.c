#include "lexer/token.h"
#include "lexer/token_arr.h"
#include "test_helpers.h"

#include <stddef.h>
#include <string.h>

/* Builds a Token whose line field identifies it, so order is easy to check. */
static Token _make_token(TokenType type, int line) {
    Token t;
    memset(&t, 0, sizeof t);

    t.type = type;
    t.line = line;

    return t;
}

static TokenArr *_make_arr_with_lines(size_t cap, int count) {
    TokenArr *arr = token_arr_init(cap);
    if (!arr) {
        return NULL;
    }

    for (int line = 1; line <= count; ++line) {
        Token t = _make_token(TOK_IDENTIFIER, line);
        if (token_arr_append(arr, &t) != TOKENARR_OK) {
            return arr;
        }
    }

    return arr;
}

/* Returns the line stored at idx, or -1 if the index is invalid. */
static int _line_at(const TokenArr *arr, size_t idx) {
    Token t;

    if (token_arr_get(arr, idx, &t) != TOKENARR_OK) {
        return -1;
    }

    return t.line;
}

static void test_init(void) {
    TokenArr *arr = token_arr_init(10);
    REQUIRE_NOT_NULL(arr);

    ASSERT_EQ_SIZE(arr->capacity, 10);
    ASSERT_EQ_SIZE(arr->length, 0);
    ASSERT_NOT_NULL(arr->items);

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_init_zero_capacity_fails(void) {
    ASSERT_NULL(token_arr_init(0));
}

static void test_append_and_len(void) {
    TokenArr *arr = _make_arr_with_lines(4, 3);
    REQUIRE_NOT_NULL(arr);

    ASSERT_EQ_SIZE(token_arr_len(arr), 3);
    ASSERT_EQ_INT(_line_at(arr, 0), 1);
    ASSERT_EQ_INT(_line_at(arr, 2), 3);

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_append_grows_past_capacity(void) {
    TokenArr *arr = _make_arr_with_lines(2, 100);
    REQUIRE_NOT_NULL(arr);

    ASSERT_EQ_SIZE(token_arr_len(arr), 100);
    ASSERT_TRUE(arr->capacity >= 100);

    for (size_t i = 0; i < 100; ++i) {
        if (_line_at(arr, i) != (int)i + 1) {
            TEST_FAIL("token %zu lost or reordered after growth", i);
            break;
        }
    }

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_append_copies_the_token(void) {
    TokenArr *arr = token_arr_init(2);
    REQUIRE_NOT_NULL(arr);

    Token t = _make_token(TOK_PLUS, 7);
    strcpy(t.lexeme, "+");
    ASSERT_EQ_INT(token_arr_append(arr, &t), TOKENARR_OK);

    /* Changing the original must not affect the stored copy. */
    strcpy(t.lexeme, "changed");

    Token out;
    ASSERT_EQ_INT(token_arr_get(arr, 0, &out), TOKENARR_OK);
    ASSERT_EQ_INT(out.type, TOK_PLUS);
    ASSERT_STR_EQ(out.lexeme, "+");

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_append_null_arguments(void) {
    TokenArr *arr = token_arr_init(2);
    REQUIRE_NOT_NULL(arr);

    Token t = _make_token(TOK_PLUS, 1);

    ASSERT_EQ_INT(token_arr_append(NULL, &t), TOKENARR_WRONG_PTR);
    ASSERT_EQ_INT(token_arr_append(arr, NULL), TOKENARR_WRONG_PTR);
    ASSERT_EQ_SIZE(token_arr_len(arr), 0);

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_get(void) {
    TokenArr *arr = _make_arr_with_lines(4, 3);
    REQUIRE_NOT_NULL(arr);

    Token out;

    ASSERT_EQ_INT(token_arr_get(arr, 1, &out), TOKENARR_OK);
    ASSERT_EQ_INT(out.line, 2);

    ASSERT_EQ_INT(token_arr_get(arr, 3, &out), TOKENARR_IDX_OUT_OF_BOUNDS);
    ASSERT_EQ_INT(token_arr_get(NULL, 0, &out), TOKENARR_WRONG_PTR);
    ASSERT_EQ_INT(token_arr_get(arr, 0, NULL), TOKENARR_WRONG_PTR);

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_swap(void) {
    TokenArr *arr = _make_arr_with_lines(4, 3);
    REQUIRE_NOT_NULL(arr);

    ASSERT_EQ_INT(token_arr_swap(arr, 0, 2), TOKENARR_OK);
    ASSERT_EQ_INT(_line_at(arr, 0), 3);
    ASSERT_EQ_INT(_line_at(arr, 1), 2);
    ASSERT_EQ_INT(_line_at(arr, 2), 1);

    /* Swapping an element with itself is a no-op. */
    ASSERT_EQ_INT(token_arr_swap(arr, 1, 1), TOKENARR_OK);
    ASSERT_EQ_INT(_line_at(arr, 1), 2);

    ASSERT_EQ_INT(token_arr_swap(arr, 0, 3), TOKENARR_IDX_OUT_OF_BOUNDS);
    ASSERT_EQ_INT(token_arr_swap(arr, 3, 0), TOKENARR_IDX_OUT_OF_BOUNDS);
    ASSERT_EQ_INT(token_arr_swap(NULL, 0, 1), TOKENARR_WRONG_PTR);

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_remove_first(void) {
    TokenArr *arr = _make_arr_with_lines(5, 4);
    REQUIRE_NOT_NULL(arr);

    ASSERT_EQ_INT(token_arr_remove(arr, 0), TOKENARR_OK);

    ASSERT_EQ_SIZE(token_arr_len(arr), 3);
    ASSERT_EQ_INT(_line_at(arr, 0), 2);
    ASSERT_EQ_INT(_line_at(arr, 1), 3);
    ASSERT_EQ_INT(_line_at(arr, 2), 4);

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_remove_middle(void) {
    TokenArr *arr = _make_arr_with_lines(5, 4);
    REQUIRE_NOT_NULL(arr);

    ASSERT_EQ_INT(token_arr_remove(arr, 1), TOKENARR_OK);

    ASSERT_EQ_SIZE(token_arr_len(arr), 3);
    ASSERT_EQ_INT(_line_at(arr, 0), 1);
    ASSERT_EQ_INT(_line_at(arr, 1), 3);
    ASSERT_EQ_INT(_line_at(arr, 2), 4);

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_remove_last(void) {
    TokenArr *arr = _make_arr_with_lines(5, 4);
    REQUIRE_NOT_NULL(arr);

    ASSERT_EQ_INT(token_arr_remove(arr, 3), TOKENARR_OK);

    ASSERT_EQ_SIZE(token_arr_len(arr), 3);
    ASSERT_EQ_INT(_line_at(arr, 2), 3);
    ASSERT_EQ_INT(_line_at(arr, 3), -1);

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_remove_until_empty(void) {
    TokenArr *arr = _make_arr_with_lines(3, 3);
    REQUIRE_NOT_NULL(arr);

    ASSERT_EQ_INT(token_arr_remove(arr, 0), TOKENARR_OK);
    ASSERT_EQ_INT(token_arr_remove(arr, 0), TOKENARR_OK);
    ASSERT_EQ_INT(token_arr_remove(arr, 0), TOKENARR_OK);
    ASSERT_EQ_SIZE(token_arr_len(arr), 0);

    /* Removing from an empty array must fail cleanly, not underflow. */
    ASSERT_EQ_INT(token_arr_remove(arr, 0), TOKENARR_IDX_OUT_OF_BOUNDS);

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_remove_invalid(void) {
    TokenArr *arr = _make_arr_with_lines(5, 4);
    REQUIRE_NOT_NULL(arr);

    ASSERT_EQ_INT(token_arr_remove(arr, 4), TOKENARR_IDX_OUT_OF_BOUNDS);
    ASSERT_EQ_INT(token_arr_remove(arr, 100), TOKENARR_IDX_OUT_OF_BOUNDS);
    ASSERT_EQ_INT(token_arr_remove(NULL, 0), TOKENARR_WRONG_PTR);
    ASSERT_EQ_SIZE(token_arr_len(arr), 4);

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
}

static void test_len_null(void) {
    ASSERT_EQ_SIZE(token_arr_len(NULL), 0);
}

static void test_println_null(void) {
    ASSERT_EQ_INT(token_arr_println(NULL), TOKENARR_WRONG_PTR);
}

static void test_deinit(void) {
    TokenArr *arr = token_arr_init(3);
    REQUIRE_NOT_NULL(arr);

    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_OK);
    ASSERT_NULL(arr);

    /* A second deinit and a NULL argument are both rejected. */
    ASSERT_EQ_INT(token_arr_deinit(&arr), TOKENARR_WRONG_PTR);
    ASSERT_EQ_INT(token_arr_deinit(NULL), TOKENARR_WRONG_PTR);
}

int main(void) {
    RUN_TEST(test_init);
    RUN_TEST(test_init_zero_capacity_fails);
    RUN_TEST(test_append_and_len);
    RUN_TEST(test_append_grows_past_capacity);
    RUN_TEST(test_append_copies_the_token);
    RUN_TEST(test_append_null_arguments);
    RUN_TEST(test_get);
    RUN_TEST(test_swap);
    RUN_TEST(test_remove_first);
    RUN_TEST(test_remove_middle);
    RUN_TEST(test_remove_last);
    RUN_TEST(test_remove_until_empty);
    RUN_TEST(test_remove_invalid);
    RUN_TEST(test_len_null);
    RUN_TEST(test_println_null);
    RUN_TEST(test_deinit);

    return test_summary();
}
