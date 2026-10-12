#include "str_buf/str_buf.h"
#include "test_helpers.h"

#include <stddef.h>

#define LAST_USABLE (STR_BUF_MAX_CAP - 1)

static void test_init_zeroes_everything(void) {
    StrBuf sb;
    memset(&sb, 'x', sizeof sb);

    strbuf_init(&sb);

    ASSERT_EQ_SIZE(sb.count, 0);
    for (size_t i = 0; i < STR_BUF_MAX_CAP; ++i) {
        if (sb.items[i] != '\0') {
            TEST_FAIL("items[%zu] not zeroed", i);
            return;
        }
    }
    ASSERT_TRUE(1);
}

static void test_init_null_is_safe(void) {
    strbuf_init(NULL);
    ASSERT_TRUE(1);
}

static void test_push_appends_in_order(void) {
    StrBuf sb;
    strbuf_init(&sb);

    ASSERT_EQ_INT(strbuf_push(&sb, 'h'), 0);
    ASSERT_EQ_INT(strbuf_push(&sb, 'i'), 0);

    ASSERT_STR_EQ(sb.items, "hi");
    ASSERT_EQ_SIZE(sb.count, 2);
}

static void test_push_stops_before_the_terminator(void) {
    StrBuf sb;
    strbuf_init(&sb);

    for (size_t i = 0; i < LAST_USABLE; ++i) {
        if (strbuf_push(&sb, 'a') != 0) {
            TEST_FAIL("push %zu failed before reaching capacity", i);
            return;
        }
    }

    ASSERT_EQ_SIZE(sb.count, LAST_USABLE);

    /* The buffer is full: one more push must fail and change nothing. */
    ASSERT_EQ_INT(strbuf_push(&sb, 'b'), 1);
    ASSERT_EQ_SIZE(sb.count, LAST_USABLE);
    ASSERT_EQ_INT(sb.items[LAST_USABLE], '\0');
    ASSERT_EQ_SIZE(strlen(sb.items), LAST_USABLE);
}

static void test_set_writes_and_checks_bounds(void) {
    StrBuf sb;
    strbuf_init(&sb);

    ASSERT_EQ_INT(strbuf_set(&sb, 'z', 0), 0);
    ASSERT_EQ_INT(sb.items[0], 'z');

    ASSERT_EQ_INT(strbuf_set(&sb, 'z', LAST_USABLE - 1), 0);
    ASSERT_EQ_INT(sb.items[LAST_USABLE - 1], 'z');

    /* Index LAST_USABLE is reserved for the terminator. */
    ASSERT_EQ_INT(strbuf_set(&sb, 'z', LAST_USABLE), 1);
    ASSERT_EQ_INT(strbuf_set(&sb, 'z', STR_BUF_MAX_CAP), 1);
    ASSERT_EQ_INT(sb.items[LAST_USABLE], '\0');
}

static void test_clear_resets_and_allows_reuse(void) {
    StrBuf sb;
    strbuf_init(&sb);
    ASSERT_EQ_INT(strbuf_push(&sb, 'a'), 0);
    ASSERT_EQ_INT(strbuf_push(&sb, 'b'), 0);

    strbuf_clear(&sb);

    ASSERT_EQ_SIZE(sb.count, 0);
    ASSERT_STR_EQ(sb.items, "");

    ASSERT_EQ_INT(strbuf_push(&sb, 'c'), 0);
    ASSERT_STR_EQ(sb.items, "c");
}

int main(void) {
    RUN_TEST(test_init_zeroes_everything);
    RUN_TEST(test_init_null_is_safe);
    RUN_TEST(test_push_appends_in_order);
    RUN_TEST(test_push_stops_before_the_terminator);
    RUN_TEST(test_set_writes_and_checks_bounds);
    RUN_TEST(test_clear_resets_and_allows_reuse);

    return test_summary();
}
