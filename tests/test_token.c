#include "lexer/token.h"
#include "str_buf/str_buf.h"
#include "test_helpers.h"
#include "token/token_internal.h"
#include "token_def/token_def.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    const char *input;
    bool expected;
} NumberCase;

static void test_is_digit(void) {
    for (int c = '0'; c <= '9'; ++c) {
        ASSERT_TRUE(is_digit(c));
    }

    /* Characters right next to the digit range in ASCII. */
    ASSERT_FALSE(is_digit('/'));
    ASSERT_FALSE(is_digit(':'));
    ASSERT_FALSE(is_digit('a'));
    ASSERT_FALSE(is_digit(' '));
    ASSERT_FALSE(is_digit(EOF));
}

static void test_is_letter(void) {
    for (int c = 'a'; c <= 'z'; ++c) {
        ASSERT_TRUE(is_letter(c));
    }

    for (int c = 'A'; c <= 'Z'; ++c) {
        ASSERT_TRUE(is_letter(c));
    }

    /* Characters right next to the letter ranges in ASCII. */
    ASSERT_FALSE(is_letter('@'));
    ASSERT_FALSE(is_letter('['));
    ASSERT_FALSE(is_letter('`'));
    ASSERT_FALSE(is_letter('{'));
    ASSERT_FALSE(is_letter('_'));
    ASSERT_FALSE(is_letter('5'));
    ASSERT_FALSE(is_letter(EOF));
}

static void test_is_number(void) {
    static const NumberCase cases[] = {
        {"12345", true},      {"+12345", true},  {"-12345", true},
        {"1.2345", true},     {"0", true},       {"007", true},
        {"  12345  ", false}, {"u12345", false}, {"1.2.3.4.5", false},
        {"12345;", false},    {"", false},       {" ", false},
        {"+", false},         {"-", false},      {"3.", false},
        {".", false},         {".3", false},     {"1..2", false},
        {"--1", false},       {"1-", false},
    };

    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
        bool actual = is_number(cases[i].input);

        tests_run++;
        if (actual != cases[i].expected) {
            TEST_FAIL("is_number(\"%s\") returned %s, expected %s",
                      cases[i].input, actual ? "true" : "false",
                      cases[i].expected ? "true" : "false");
        } else {
            TEST_PASS(cases[i].input);
        }
    }
}

static void test_is_keyword(void) {
    size_t idx = 0;

    ASSERT_TRUE(is_keyword("int", &idx));
    ASSERT_EQ_INT(tok_definitions[idx].tok_type, TOK_KW_INT);

    ASSERT_TRUE(is_keyword("while", &idx));
    ASSERT_EQ_INT(tok_definitions[idx].tok_type, TOK_KW_WHILE);

    ASSERT_TRUE(is_keyword("_Bool", &idx));
    ASSERT_EQ_INT(tok_definitions[idx].tok_type, TOK_KW_BOOL);

    /* The index output is optional. */
    ASSERT_TRUE(is_keyword("return", NULL));

    /* Keywords are case sensitive and must match exactly. */
    ASSERT_FALSE(is_keyword("Int", NULL));
    ASSERT_FALSE(is_keyword("integer", NULL));
    ASSERT_FALSE(is_keyword("in", NULL));
    ASSERT_FALSE(is_keyword("foo", NULL));
    ASSERT_FALSE(is_keyword("", NULL));
}

static void test_is_operator(void) {
    size_t idx = 0;

    ASSERT_TRUE(is_operator("+", &idx));
    ASSERT_EQ_INT(tok_definitions[idx].tok_type, TOK_PLUS);

    ASSERT_TRUE(is_operator("<<=", &idx));
    ASSERT_EQ_INT(tok_definitions[idx].tok_type, TOK_LSHIFT_ASSIGN);

    ASSERT_TRUE(is_operator("->", &idx));
    ASSERT_EQ_INT(tok_definitions[idx].tok_type, TOK_ARROW);

    ASSERT_TRUE(is_operator("&&", NULL));

    ASSERT_FALSE(is_operator("+++", NULL));
    ASSERT_FALSE(is_operator("=>", NULL));
    ASSERT_FALSE(is_operator("foo", NULL));
    ASSERT_FALSE(is_operator("", NULL));
}

static void test_token_type_to_str(void) {
    ASSERT_STR_EQ(token_type_to_str(TOK_PLUS), "PLUS");
    ASSERT_STR_EQ(token_type_to_str(TOK_KW_INT), "KW_INT");
    ASSERT_STR_EQ(token_type_to_str(TOK_EOF), "EOF");
    ASSERT_STR_EQ(token_type_to_str(TOK_INVALID_CHAR), "INVALID_CHAR");

    /* Values outside the enum must not crash. */
    ASSERT_STR_EQ(token_type_to_str((TokenType)9999), "UNKNOWN");
}

static void test_token_init_type(void) {
    StrBuf word;
    strbuf_init(&word);
    ASSERT_EQ_INT(strbuf_push(&word, 'a'), 0);
    ASSERT_EQ_INT(strbuf_push(&word, 'b'), 0);

    Token t;
    token_init_type(&t, TOK_IDENTIFIER, &word, 3, 9);

    ASSERT_EQ_INT(t.type, TOK_IDENTIFIER);
    ASSERT_STR_EQ(t.lexeme, "ab");
    ASSERT_EQ_INT(t.line, 3);
    ASSERT_EQ_INT(t.col, 9);
}

static void test_token_init_classifies_the_word(void) {
    StrBuf word;
    Token t;

    strbuf_init(&word);
    ASSERT_EQ_INT(strbuf_push(&word, '#'), 0);
    token_init(&t, &word, 1, 1);
    ASSERT_EQ_INT(t.type, TOK_HASH);

    strbuf_clear(&word);
    ASSERT_EQ_INT(strbuf_push(&word, '+'), 0);
    ASSERT_EQ_INT(strbuf_push(&word, '='), 0);
    token_init(&t, &word, 1, 1);
    ASSERT_EQ_INT(t.type, TOK_ADD_ASSIGN);

    strbuf_clear(&word);
    ASSERT_EQ_INT(strbuf_push(&word, 'f'), 0);
    ASSERT_EQ_INT(strbuf_push(&word, 'o'), 0);
    ASSERT_EQ_INT(strbuf_push(&word, 'o'), 0);
    token_init(&t, &word, 1, 1);
    ASSERT_EQ_INT(t.type, TOK_IDENTIFIER);

    strbuf_clear(&word);
    ASSERT_EQ_INT(strbuf_push(&word, '@'), 0);
    token_init(&t, &word, 1, 1);
    ASSERT_EQ_INT(t.type, TOK_INVALID);
}

/*
 * tok_definitions is indexed by TokenType using designated initializers.
 * If someone adds an enum value and forgets the table entry (or the reverse),
 * lookups silently return the wrong data. This catches that.
 */
static void test_definition_table_matches_the_enum(void) {
    ASSERT_EQ_SIZE(tok_definitions_len, (size_t)TOK_INVALID_SUFFIX + 1);

    for (size_t i = 0; i < tok_definitions_len; ++i) {
        tests_run++;

        if (tok_definitions[i].display_name == NULL) {
            TEST_FAIL("tok_definitions[%zu] has no display name (hole)", i);
        } else if ((size_t)tok_definitions[i].tok_type != i) {
            TEST_FAIL("tok_definitions[%zu] is mapped to type %d", i,
                      (int)tok_definitions[i].tok_type);
        } else {
            TEST_PASS(tok_definitions[i].display_name);
        }
    }
}

int main(void) {
    RUN_TEST(test_is_digit);
    RUN_TEST(test_is_letter);
    RUN_TEST(test_is_number);
    RUN_TEST(test_is_keyword);
    RUN_TEST(test_is_operator);
    RUN_TEST(test_token_type_to_str);
    RUN_TEST(test_token_init_type);
    RUN_TEST(test_token_init_classifies_the_word);
    RUN_TEST(test_definition_table_matches_the_enum);

    return test_summary();
}
