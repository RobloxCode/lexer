#define _POSIX_C_SOURCE 200809L

#include "lexer/lexer.h"
#include "lexer/token.h"
#include "lexer/token_arr.h"
#include "test_helpers.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Writes source to a temporary file, lexes it and returns the Lexer
 * (NULL on failure). The temporary file is removed before returning.
 */
static Lexer *_lex_string(const char *source) {
    char path[] = "/tmp/lexer_test_XXXXXX";

    int fd = mkstemp(path);
    if (fd < 0) {
        return NULL;
    }

    size_t len = strlen(source);
    ssize_t written = write(fd, source, len);
    close(fd);

    Lexer *l = NULL;
    if (written >= 0 && (size_t)written == len) {
        l = lexer_lex(path);
    }

    unlink(path);
    return l;
}

static Token _token_at(const Lexer *l, size_t idx) {
    Token t;
    memset(&t, 0, sizeof t);
    t.type = TOK_INVALID;

    if (token_arr_get(lexer_tokens(l), idx, &t) != TOKENARR_OK) {
        t.type = TOK_INVALID;
        strcpy(t.lexeme, "<missing>");
    }

    return t;
}

/*
 * Lexes 'source' and checks the exact sequence of token types.
 * 'line' is the line of the assertion in this file, used in failure messages.
 */
static void _check_types(const char *source, const TokenType *want, size_t n,
                         int line) {
    Lexer *l = _lex_string(source);

    tests_run++;

    if (!l) {
        tests_failed++;
        fprintf(stderr, "  [FAIL] %s:%d: could not lex \"%s\"\n", __FILE__,
                line, source);
        return;
    }

    size_t got = token_arr_len(lexer_tokens(l));
    if (got != n) {
        tests_failed++;
        fprintf(stderr,
                "  [FAIL] %s:%d: \"%s\": got %zu tokens, expected %zu\n",
                __FILE__, line, source, got, n);
        lexer_deinit(&l);
        return;
    }

    for (size_t i = 0; i < n; ++i) {
        Token t = _token_at(l, i);

        if (t.type != want[i]) {
            tests_failed++;
            fprintf(stderr,
                    "  [FAIL] %s:%d: \"%s\": token %zu is %s, expected %s\n",
                    __FILE__, line, source, i, token_type_to_str(t.type),
                    token_type_to_str(want[i]));
            lexer_deinit(&l);
            return;
        }
    }

    TEST_PASS(source);
    lexer_deinit(&l);
}

/* The final TOK_EOF is added automatically. Needs at least one type. */
#define ASSERT_TYPES(source, ...)                                              \
    do {                                                                       \
        static const TokenType want_[] = {__VA_ARGS__, TOK_EOF};               \
        _check_types(source, want_, sizeof want_ / sizeof want_[0], __LINE__); \
    } while (0)

/* Input that must produce nothing but the final TOK_EOF. */
#define ASSERT_ONLY_EOF(source)                                                \
    do {                                                                       \
        static const TokenType want_[] = {TOK_EOF};                            \
        _check_types(source, want_, 1, __LINE__);                              \
    } while (0)

static void test_api_edge_cases(void) {
    ASSERT_NULL(lexer_lex(NULL));
    ASSERT_NULL(lexer_lex("/this/path/does/not/exist.c"));
    ASSERT_NULL(lexer_tokens(NULL));

    Lexer *l = NULL;
    lexer_deinit(&l);
    lexer_deinit(NULL);
    ASSERT_NULL(l);
}

static void test_deinit_nulls_the_pointer(void) {
    Lexer *l = _lex_string("int x;");
    REQUIRE_NOT_NULL(l);

    lexer_deinit(&l);
    ASSERT_NULL(l);
}

static void test_empty_input(void) {
    ASSERT_ONLY_EOF("");
    ASSERT_ONLY_EOF("   \n\t\r\n  ");
}

static void test_declaration(void) {
    ASSERT_TYPES("int x = 42;", TOK_KW_INT, TOK_IDENTIFIER, TOK_ASSIGN,
                 TOK_INTEGER, TOK_SEMICOLON);
}

static void test_keywords_and_identifiers(void) {
    ASSERT_TYPES("return returned _Bool _x1 int2", TOK_KW_RETURN,
                 TOK_IDENTIFIER, TOK_KW_BOOL, TOK_IDENTIFIER, TOK_IDENTIFIER);
}

static void test_delimiters(void) {
    ASSERT_TYPES("( ) { } [ ] , . : ;", TOK_LPAREN, TOK_RPAREN, TOK_LBRACE,
                 TOK_RBRACE, TOK_LBRACKET, TOK_RBRACKET, TOK_COMMA, TOK_DOT,
                 TOK_COLON, TOK_SEMICOLON);
}

static void test_operators_use_longest_match(void) {
    ASSERT_TYPES("a <<= b", TOK_IDENTIFIER, TOK_LSHIFT_ASSIGN, TOK_IDENTIFIER);
    ASSERT_TYPES("a >>= b", TOK_IDENTIFIER, TOK_RSHIFT_ASSIGN, TOK_IDENTIFIER);
    ASSERT_TYPES("a << b", TOK_IDENTIFIER, TOK_LSHIFT, TOK_IDENTIFIER);
    ASSERT_TYPES("a != b", TOK_IDENTIFIER, TOK_NOT_EQ, TOK_IDENTIFIER);
    ASSERT_TYPES("a == b", TOK_IDENTIFIER, TOK_EQ, TOK_IDENTIFIER);
    ASSERT_TYPES("a <= b", TOK_IDENTIFIER, TOK_LESS_EQ, TOK_IDENTIFIER);
    ASSERT_TYPES("a && b", TOK_IDENTIFIER, TOK_AND, TOK_IDENTIFIER);
    ASSERT_TYPES("p->x", TOK_IDENTIFIER, TOK_ARROW, TOK_IDENTIFIER);
    ASSERT_TYPES("a /= b", TOK_IDENTIFIER, TOK_DIV_ASSIGN, TOK_IDENTIFIER);
    ASSERT_TYPES("i++", TOK_IDENTIFIER, TOK_INCREMENT);
    ASSERT_TYPES("a ? b : c", TOK_IDENTIFIER, TOK_CONDITIONAL, TOK_IDENTIFIER,
                 TOK_COLON, TOK_IDENTIFIER);
    ASSERT_TYPES("#", TOK_HASH);
}

static void test_comments_are_skipped(void) {
    ASSERT_TYPES("a // line comment\nb", TOK_IDENTIFIER, TOK_IDENTIFIER);
    ASSERT_TYPES("a /* block */ b", TOK_IDENTIFIER, TOK_IDENTIFIER);
    ASSERT_TYPES("a /* multi\nline\ncomment */ b", TOK_IDENTIFIER,
                 TOK_IDENTIFIER);
    ASSERT_ONLY_EOF("// only a comment");
    ASSERT_TYPES("a / b", TOK_IDENTIFIER, TOK_SLASH, TOK_IDENTIFIER);
}

static void test_numbers(void) {
    ASSERT_TYPES("42", TOK_INTEGER);
    ASSERT_TYPES("3.14", TOK_FLOAT);
    ASSERT_TYPES("1.2.3", TOK_INVALID_NUMBER);
    ASSERT_TYPES("23ull", TOK_INTEGER);
    ASSERT_TYPES("23ULL", TOK_INTEGER);
    // ASSERT_TYPES("0x1F", TOK_INVALID_NUMBER);
}

static void test_string_and_char_literals(void) {
    ASSERT_TYPES("\"hello\" 'a'", TOK_STRING, TOK_CHAR);

    Lexer *l = _lex_string("\"hello\"");
    REQUIRE_NOT_NULL(l);
    ASSERT_STR_EQ(_token_at(l, 0).lexeme, "hello");
    lexer_deinit(&l);
}

static void test_unterminated_literals(void) {
    ASSERT_TYPES("\"never closed", TOK_INVALID_STR);
    ASSERT_TYPES("'x", TOK_INVALID_CHAR);
}

static void test_unknown_character(void) {
    ASSERT_TYPES("a @ b", TOK_IDENTIFIER, TOK_INVALID, TOK_IDENTIFIER);
}

static void test_lexemes(void) {
    Lexer *l = _lex_string("int count = 10;");
    REQUIRE_NOT_NULL(l);

    ASSERT_STR_EQ(_token_at(l, 0).lexeme, "int");
    ASSERT_STR_EQ(_token_at(l, 1).lexeme, "count");
    ASSERT_STR_EQ(_token_at(l, 2).lexeme, "=");
    ASSERT_STR_EQ(_token_at(l, 3).lexeme, "10");
    ASSERT_STR_EQ(_token_at(l, 4).lexeme, ";");

    lexer_deinit(&l);
}

static void test_positions(void) {
    Lexer *l = _lex_string("ab\n  cd");
    REQUIRE_NOT_NULL(l);

    Token first = _token_at(l, 0);
    Token second = _token_at(l, 1);

    ASSERT_EQ_INT(first.line, 1);
    ASSERT_EQ_INT(first.col, 1);
    ASSERT_EQ_INT(second.line, 2);
    ASSERT_EQ_INT(second.col, 3);

    lexer_deinit(&l);
}

static void test_overlong_token_is_invalid(void) {
    char source[TOKEN_BUF_MAX_CAP + 50];

    memset(source, 'a', sizeof source - 1);
    source[sizeof source - 1] = '\0';

    ASSERT_TYPES(source, TOK_INVALID);
}

static void test_eof_is_always_last(void) {
    Lexer *l = _lex_string("a b c");
    REQUIRE_NOT_NULL(l);

    size_t len = token_arr_len(lexer_tokens(l));
    ASSERT_EQ_SIZE(len, 4);
    ASSERT_EQ_INT(_token_at(l, len - 1).type, TOK_EOF);

    lexer_deinit(&l);
}

int main(void) {
    RUN_TEST(test_api_edge_cases);
    RUN_TEST(test_deinit_nulls_the_pointer);
    RUN_TEST(test_empty_input);
    RUN_TEST(test_declaration);
    RUN_TEST(test_keywords_and_identifiers);
    RUN_TEST(test_delimiters);
    RUN_TEST(test_operators_use_longest_match);
    RUN_TEST(test_comments_are_skipped);
    RUN_TEST(test_numbers);
    RUN_TEST(test_string_and_char_literals);
    RUN_TEST(test_unterminated_literals);
    RUN_TEST(test_unknown_character);
    RUN_TEST(test_lexemes);
    RUN_TEST(test_positions);
    RUN_TEST(test_overlong_token_is_invalid);
    RUN_TEST(test_eof_is_always_last);

    return test_summary();
}
