#ifndef LEXER_SCAN_H
#define LEXER_SCAN_H

#include "../str_buf/str_buf.h"
#include "lexer.h"

#include <stdio.h>

int next_char(Lexer *l);

int peek_char(Lexer *l);

/**
 * @brief Helper function to lexe strings
 *
 * @param l Pointer to a Lexer
 */
void handle_str(Lexer *l);

/**
 * @brief Helper function to lexe numbers
 *
 * @param l Pointer to a Lexer
 *
 * @return 0 on success
 *         1 on invalid decimal number (more than one decimal point)
 */
int handle_number(Lexer *l);

/**
 * @brief Helper function to lexe one line comments
 *
 * @param l Pointer to a Lexer
 */
void handle_one_line_comment(Lexer *l);

/**
 * @brief Helper function to lexe multi-line comments
 *
 * @param l Pointer to a Lexer
 */
void handle_multiline_comment(Lexer *l);

#endif
