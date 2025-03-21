#ifndef MIK_ERRORS_H
#define MIK_ERRORS_H

#include <lexer.hpp>
#include <parser.hpp>
#include <iostream>

// Colors
#define RED "\x1b[31m"
#define DEFAULT "\x1b[0m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"

// Error codes
#define GET_ERROR(X) (("https://miklang.org/errors/" + std::to_string((X))))

// Compiler Intern
#define COMPILER_ERROR 0
#define COMPILER_ERROR_LINK GET_ERROR(COMPILER_ERROR)

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

// Parser
#define EXPECTED_IDENTIFIER_FOR_FIRST_CLASS_EXPRESSION 300
#define EXPECTED_IDENTIFIER_FOR_FIRST_CLASS_EXPRESSION_LINK GET_ERROR(EXPECTED_IDENTIFIER_FOR_FIRST_CLASS_EXPRESSION)

#define EXPECTED_VARIABLE_NAME_AFTER_TYPE 301
#define EXPECTED_VARIABLE_NAME_AFTER_TYPE_LINK GET_ERROR(EXPECTED_VARIABLE_NAME_AFTER_TYPE)

#define EXPECTED_BOUND_OR_ARRAY_DEFINITION_OR_ASSIGNMENT_AFTER_VARIABLE_NAME 302
#define EXPECTED_BOUND_OR_ARRAY_DEFINITION_OR_ASSIGNMENT_AFTER_VARIABLE_NAME_LINK GET_ERROR(EXPECTED_BOUND_OR_ARRAY_DEFINITION_OR_ASSIGNMENT_AFTER_VARIABLE_NAME)

#define EXPECTED_NEWLINE_BEFORE_NEW_FIRST_CLASS_EXPRESSION 303
#define EXPECTED_NEWLINE_BEFORE_NEW_FIRST_CLASS_EXPRESSION_LINK GET_ERROR(EXPECTED_NEWLINE_BEFORE_NEW_FIRST_CLASS_EXPRESSION)

#define EXPEXTED_EXPRESSION_AFTER_OPERATION_IN_ASSIGNMENT 304 
#define EXPEXTED_EXPRESSION_AFTER_OPERATION_IN_ASSIGNMENT_LINK GET_ERROR(EXPEXTED_EXPRESSION_AFTER_OPERATION_IN_ASSIGNMENT)

#define TYPES_NOT_CONSISTENT 305
#define TYPES_NOT_CONSISTENT_LINK GET_ERROR(TYPES_NOT_CONSISTENT)

#define PREFIX_NOT_DEFINED_FOR_TYPE 306
#define PREFIX_NOT_DEFINED_FOR_TYPE_LINK GET_ERROR(PREFIX_NOT_DEFINED_FOR_TYPE)

#define UNKNOWN_IDENTIFIER_IN_EXPRESSION 307
#define UNKNOWN_IDENTIFIER_IN_EXPRESSION_LINK GET_ERROR(UNKNOWN_IDENTIFIER_IN_EXPRESSION)

#define VARIABLE_NAME_TAKEN_OR_KEYWORD 308
#define VARIABLE_NAME_TAKEN_OR_KEYWORD_LINK GET_ERROR(VARIABLE_NAME_TAKEN_OR_KEYWORD)

#define BUILTIN_GUARDS_TYPE_MISSMATCH 309
#define BUILTIN_GUARDS_TYPE_MISSMATCH_LINK GET_ERROR(BUILTIN_GUARDS_TYPE_MISSMATCH)

#define EXPECTED_OPENING_PARENTHESIS_IN_FUNCTION_CALL 310
#define EXPECTED_OPENING_PARENTHESIS_IN_FUNCTION_CALL_LINK GET_ERROR(EXPECTED_OPENING_PARENTHESIS_IN_FUNCTION_CALL)

#define EXPECTED_CLOSING_PARENTHESIS_IN_FUNCTION_CALL 311
#define EXPECTED_CLOSING_PARENTHESIS_IN_FUNCTION_CALL_LINK GET_ERROR(EXPECTED_CLOSING_PARENTHESIS_IN_FUNCTION_CALL)

#define EXPECTED_COMMA_IN_FUNCTION_CALL 312
#define EXPECTED_COMMA_IN_FUNCTION_CALL_LINK GET_ERROR(EXPECTED_COMMA_IN_FUNCTION_CALL)

#define EXPECTED_CLOSING_PARENTHESIS 313
#define EXPECTED_CLOSING_PARENTHESIS_LINK GET_ERROR(EXPECTED_CLOSING_PARENTHESIS)

#define INVALID_CONVERSION 314
#define INVALID_CONVERSION_LINK GET_ERROR(INVALID_CONVERSION)

#define TYPE_NOT_DEFINED 315
#define TYPE_NOT_DEFINED_LINK GET_ERROR(TYPE_NOT_DEFINED)

#define EXPRESSION_IN_PARENTHESIS_NOT_ALLOWED 316
#define EXPRESSION_IN_PARENTHESIS_NOT_ALLOWED_LINK GET_ERROR(EXPRESSION_IN_PARENTHESIS_NOT_ALLOWED)

#define STANDALONE_REFFERENCE_TO_VARIABLE_NOT_ALLOWED 317
#define STANDALONE_REFFERENCE_TO_VARIABLE_NOT_ALLOWED_LINK GET_ERROR(STANDALONE_REFFERENCE_TO_VARIABLE_NOT_ALLOWED)

#define EXPECTED_SECOND_CLASS_EXPRESSION 318
#define EXPECTED_SECOND_CLASS_EXPRESSION_LINK GET_ERROR(EXPECTED_SECOND_CLASS_EXPRESSION)

#define UNKNOWN_TYPE_IN_ASSIGNMENT 319
#define UNKNOWN_TYPE_IN_ASSIGNMENT_LINK GET_ERROR(UNKNOWN_TYPE_IN_ASSIGNMENT)

#define UNKNOWN_FIRST_CLASS_IDENTIFIER 320
#define UNKNOWN_FIRST_CLASS_IDENTIFIER_LINK GET_ERROR(UNKNOWN_FIRST_CLASS_IDENTIFIER)

void throw_error(int err_code, Lexer state);
void throw_error(int err_code, string line, int line_number, string path);
void throw_error(int err_code, Parser state);
void throw_type_error(int err_code, Type expected, Type was, Parser state);
void throw_compiler_error(int err_code);
void print_error_location(Lexer state);
void print_error_location(Parser state);
template<typename T> void print_std_error(int err_code, string err_link, string err_text, T state);

#endif // MIK_ERRORS_H
