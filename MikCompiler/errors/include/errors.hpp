#ifndef MIK_ERRORS_H
#define MIK_ERRORS_H

#include <lexer.hpp>
#include <iostream>

// Colors
#define RED "\x1b[31m"
#define DEFAULT "\x1b[0m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"

// Error codes
#define GET_ERROR(X) (("https://miklang.org/errors/" + std::to_string((X))))

// Preprocessor
#define ERROR_OPENING_YOINKED_FILE 100
#define ERROR_OPENING_YOINKED_FILE_LINK GET_ERROR(ERROR_OPENING_YOINKED_FILE)

// Lexer
#define UNEXPECTED_TOKEN 200
#define UNEXPECTED_TOKEN_LINK GET_ERROR(UNEXPECTED_TOKEN)

#define UNTERMINATED_MULTILINE_COMMENT 201
#define UNTERMINATED_MULTILINE_COMMENT_LINK GET_ERROR(UNTERMINATED_MULTILINE_COMMENT)

#define UNTERMINATED_STRING 202
#define UNTERMINATED_STRING_LINK GET_ERROR(UNTERMINATED_STRING)

#define UNEXPECTED_DECIMAL_POINT 203
#define UNEXPECTED_DECIMAL_POINT_LINK GET_ERROR(UNEXPECTED_DECIMAL_POINT)

#define HEX_LITERAL_EXPECTED 204
#define HEX_LITERAL_EXPECTED_LINK GET_ERROR(HEX_LITERAL_EXPECTED)

#define BIN_LITERAL_EXPECTED 205
#define BIN_LITERAL_EXPECTED_LINK GET_ERROR(BIN_LITERAL_EXPECTED)

#define UNTERMINATED_CHARACTER_LITERAL 206
#define UNTERMINATED_CHARACTER_LITERAL_LINK GET_ERROR(UNTERMINATED_CHARACTER_LITERAL)

#define INVALID_COMPILER_DIRECTIVE 207
#define INVALID_COMPILER_DIRECTIVE_LINK GET_ERROR(INVALID_COMPILER_DIRECTIVE)

#define CLOSING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE 208
#define CLOSING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE_LINK GET_ERROR(CLOSING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE)

#define OPENING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE 209
#define OPENING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE_LINK GET_ERROR(OPENING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE)

void throw_error(int err_code, Lexer state);
void throw_error(int err_code, string line, int line_number, string path);
void print_error_location(Lexer state);

#endif // MIK_ERRORS_H
