#ifndef LEXER_SCAN_H
#define LEXER_SCAN_H

#include "../str_buf/str_buf.h"
#include "lexer.h"

#include <stdio.h>

/**
 * @brief Reads the next character from the field l->file
 *
 * @param l Pointer to Lexer
 *
 * @return character as integer
 */
int next_char(Lexer *l);

/**
 * @brief Reads one character ahead of the current character
 *
 * @param l Pointer to Lexer
 *
 * @return character as integer
 */
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
