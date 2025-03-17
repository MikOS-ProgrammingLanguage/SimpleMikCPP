#include "utils.hpp"
#include <errors.hpp>
#include <iostream>
#include <string>

// Accumulates the line on which the error occured and prints this line with
// additional information about the location
void print_error_location(Lexer state) {
    string whitespace_buffer =
        string(to_string(state.positions_in_files.top().second).size(), ' ');
    string line_to_print;

    // get line_to_print
    // iterate back from the current character
    int char_idx = state.current_index;
    for (char c = state.text[state.current_index];
         c != '\n' && state.current_index >= 0; state.current_index--)
        c = state.text[state.current_index];

    if (state.text[state.current_index + 1] == '\n') {
        state.current_index += 2;
        state.current_character = state.text[state.current_index];
    } else {
        state.current_index++;
        state.current_character = state.text[state.current_index];
    }

    for (; state.current_index < state.text.size() &&
           state.current_character != '\n';
         state.current_character = state.text[++state.current_index]) {
        if (char_idx == state.current_index)
            line_to_print += RED;

        line_to_print += state.current_character;

        if (char_idx == state.current_index)
            line_to_print += DEFAULT;
    }

    cout << "\r" << BLUE << "\tIn: " << state.positions_in_files.top().first
         << "\n\t" << whitespace_buffer << " |\n\t"
         << to_string(state.positions_in_files.top().second) << " | " << DEFAULT
         << line_to_print << "\n\t" << BLUE << whitespace_buffer << " | "
         << endl;
}

void print_error_location(Parser state) {
    string whitespace_buffer = string(state.current_token.line_number, ' ');
    string line_to_print;
    state.current_token.idx--;

    // get line_to_print
    // iterate back from the current character
    int char_idx = state.current_token.idx;
    char current_char;
    for (char c = state.text[state.current_token.idx];
         c != '\n' && state.current_token.idx >= 0; state.current_token.idx--)
        c = state.text[state.current_token.idx];

    if (state.text[state.current_token.idx + 1] == '\n') {
        state.current_token.idx += 2;
        current_char = state.text[state.current_token.idx];
    } else {
        state.current_token.idx++;
        current_char = state.text[state.current_token.idx];
    }

    for (; state.current_token.idx < state.text.size() && current_char != '\n';
         current_char = state.text[++state.current_token.idx]) {
        if (char_idx == state.current_token.idx)
            line_to_print += RED;

        line_to_print += current_char;

        if (char_idx == state.current_token.idx)
            line_to_print += DEFAULT;
    }

    cout << "\r" << BLUE << "\tIn: " << state.current_token.file_name << "\n\t"
         << whitespace_buffer << " |\n\t"
         << to_string(state.current_token.line_number) << " | " << DEFAULT
         << line_to_print << "\n\t" << BLUE << whitespace_buffer << " | "
         << endl;
}

void print_error_location(string line, int line_number, string path) {
    string whitespace_buffer = string(to_string(line_number).size(), ' ');
    cout << "\r" << BLUE << "\tIn: " << path << "\n\t" << whitespace_buffer
         << " |\n\t" << to_string(line_number) << " | " << RED << line << "\n\t"
         << whitespace_buffer << " | " << endl;
}

template <typename T>
void print_std_error(int err_code, string err_link, string err_text, T state) {
    cout << RED << "\n\r[ERROR " << to_string(err_code) << "] " << err_text
         << ":\n";
    print_error_location(state);
    cout << GREEN << "\nRead more about this error: " << err_link << "\n"
         << DEFAULT << endl;
    exit(-1);
}

void throw_error(int err_code, string line, int line_number, string path) {
    switch (err_code) {
    case ERROR_OPENING_YOINKED_FILE: {
        cout
            << RED << "\n\r[ERROR " << to_string(ERROR_OPENING_YOINKED_FILE)
            << "] An error occured while trying to open a yoinked file. It may "
               "not exist:\n";
        print_error_location(line, line_number, path);
        cout << GREEN
             << "\nRead more about this error: " << ERROR_OPENING_YOINKED_FILE
             << "\n"
             << DEFAULT << endl;
        exit(-1);
    } break;
    }
}

void throw_error(int err_code, Lexer state) {
    string s;
    switch (err_code) {
    case UNEXPECTED_TOKEN: {
        s = "An unexpected token (" + string(1, state.current_character) +
            ") was found";
        print_std_error(UNEXPECTED_TOKEN, UNEXPECTED_TOKEN_LINK, s, state);
    } break;

    case UNTERMINATED_MULTILINE_COMMENT: {
        s = "A multiline comment was started but never terminated";
        print_std_error(UNTERMINATED_MULTILINE_COMMENT,
                        UNTERMINATED_MULTILINE_COMMENT_LINK, s, state);
    } break;

    case UNTERMINATED_STRING: {
        s = "A string was started but never terminated";
        print_std_error(UNTERMINATED_STRING, UNTERMINATED_STRING_LINK, s,
                        state);
    } break;

    case UNEXPECTED_DECIMAL_POINT: {
        s = "An unexpected decimal point was found";
        print_std_error(UNEXPECTED_DECIMAL_POINT, UNEXPECTED_DECIMAL_POINT_LINK,
                        s, state);
    } break;

    case HEX_LITERAL_EXPECTED: {
        s = "A hex literal was expected after 0x but not found";
        print_std_error(HEX_LITERAL_EXPECTED, HEX_LITERAL_EXPECTED_LINK, s,
                        state);
    }

    case BIN_LITERAL_EXPECTED: {
        s = "A binary literal was expected after 0b but not found";
        print_std_error(BIN_LITERAL_EXPECTED, BIN_LITERAL_EXPECTED_LINK, s,
                        state);
    }

    case UNTERMINATED_CHARACTER_LITERAL: {
        s = "A character literal was started but never terminated";
        print_std_error(UNTERMINATED_CHARACTER_LITERAL,
                        UNTERMINATED_CHARACTER_LITERAL_LINK, s, state);
    } break;

    case INVALID_COMPILER_DIRECTIVE: {
        s = "An invalid compiler directive (" +
            state.tokens[state.tokens.size() - 1].value + ") was found";
        print_std_error(INVALID_COMPILER_DIRECTIVE,
                        INVALID_COMPILER_DIRECTIVE_LINK, s, state);
    } break;

    case CLOSING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE: {
        s = "A closing parenthesis was expected in the @file compiler "
            "directive";
        print_std_error(
            CLOSING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE,
            CLOSING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE_LINK, s,
            state);
    } break;

    case OPENING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE: {
        s = "An opening parenthesis was expected in the @file copmpiler "
            "directive";
        print_std_error(
            OPENING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE,
            OPENING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE_LINK, s,
            state);
    } break;
    }
}

void throw_error(int err_code, Parser state) {
    string s;
    switch (err_code) {
    case EXPECTED_IDENTIFIER_FOR_FIRST_CLASS_EXPRESSION: {
        s = "An indentifier is expected in a first class expression";
        print_std_error(EXPECTED_IDENTIFIER_FOR_FIRST_CLASS_EXPRESSION,
                        EXPECTED_IDENTIFIER_FOR_FIRST_CLASS_EXPRESSION_LINK, s,
                        state);
    } break;
    case EXPECTED_VARIABLE_NAME_AFTER_TYPE: {
        s = "A variable name was expected after a type in the "
            "definition/declaration of a variable";
        print_std_error(EXPECTED_VARIABLE_NAME_AFTER_TYPE,
                        EXPECTED_VARIABLE_NAME_AFTER_TYPE_LINK, s, state);
    } break;
    case EXPECTED_BOUND_OR_ARRAY_DEFINITION_OR_ASSIGNMENT_AFTER_VARIABLE_NAME: {
        s = "A boundary ({}), array ([]), or assignment (=) was expected after "
            "a variable name in the definition/declaration of a variable";
        print_std_error(
            EXPECTED_BOUND_OR_ARRAY_DEFINITION_OR_ASSIGNMENT_AFTER_VARIABLE_NAME,
            EXPECTED_BOUND_OR_ARRAY_DEFINITION_OR_ASSIGNMENT_AFTER_VARIABLE_NAME_LINK,
            s, state);
    } break;
    case EXPECTED_NEWLINE_BEFORE_NEW_FIRST_CLASS_EXPRESSION: {
        s = "A new line was expected after the end of a first class expression";
        print_std_error(EXPECTED_NEWLINE_BEFORE_NEW_FIRST_CLASS_EXPRESSION,
                        EXPECTED_NEWLINE_BEFORE_NEW_FIRST_CLASS_EXPRESSION_LINK,
                        s, state);
    } break;
    case EXPEXTED_EXPRESSION_AFTER_OPERATION_IN_ASSIGNMENT: {
        s = "An expression was expected after an operation in an assignment";
        print_std_error(EXPEXTED_EXPRESSION_AFTER_OPERATION_IN_ASSIGNMENT,
                        EXPEXTED_EXPRESSION_AFTER_OPERATION_IN_ASSIGNMENT_LINK,
                        s, state);
    } break;
    case VARIABLE_NAME_TAKEN_OR_KEYWORD: {
        s = "Variable name already taken or a keyword. The variable name you "
            "tried to assign is either taken or a builtin keyword";
        print_std_error(VARIABLE_NAME_TAKEN_OR_KEYWORD,
                        VARIABLE_NAME_TAKEN_OR_KEYWORD_LINK, s, state);
    } break;
    case BUILTIN_GUARDS_TYPE_MISSMATCH: {
        s = "Builtin guard conditions only work on either float or int";
        print_std_error(BUILTIN_GUARDS_TYPE_MISSMATCH,
                        BUILTIN_GUARDS_TYPE_MISSMATCH_LINK, s, state);
    } break;
    case EXPECTED_OPENING_PARENTHESIS_IN_FUNCTION_CALL: {
        s = "Expected opening parenthesis in function call, but none found";
        print_std_error(EXPECTED_OPENING_PARENTHESIS_IN_FUNCTION_CALL,
                        EXPECTED_OPENING_PARENTHESIS_IN_FUNCTION_CALL_LINK, s,
                        state);
    } break;
    case EXPECTED_CLOSING_PARENTHESIS_IN_FUNCTION_CALL: {
        s = "Expected closing parenthesis at the end of function call, but "
            "none found";
        print_std_error(EXPECTED_CLOSING_PARENTHESIS_IN_FUNCTION_CALL,
                        EXPECTED_CLOSING_PARENTHESIS_IN_FUNCTION_CALL_LINK, s,
                        state);
    } break;
    case EXPECTED_COMMA_IN_FUNCTION_CALL: {
        s = "Arguments in function call need to be seperated by commas, was "
            "not the case";
        print_std_error(EXPECTED_COMMA_IN_FUNCTION_CALL,
                        EXPECTED_COMMA_IN_FUNCTION_CALL_LINK, s, state);
    } break;
    case EXPECTED_CLOSING_PARENTHESIS: {
        s = "Expected a closing parenthesis in expression surrounded with parenthesis";
        print_std_error(EXPECTED_CLOSING_PARENTHESIS, EXPECTED_CLOSING_PARENTHESIS_LINK, s, state);
    } break;
    case STANDALONE_REFFERENCE_TO_VARIABLE_NOT_ALLOWED: {
        s = "Found a stand-alone refference to a variable. Did you mean to re-assign it?";
        print_std_error(STANDALONE_REFFERENCE_TO_VARIABLE_NOT_ALLOWED, STANDALONE_REFFERENCE_TO_VARIABLE_NOT_ALLOWED_LINK, s, state);
    } break;
    }
}

void throw_compiler_error(int err_code) {
    switch (err_code) {
    case COMPILER_ERROR: {
        cout << RED << "[ERROR " << to_string(err_code)
             << "] INTERNAL COMPILER_ERROR, please visit: "
             << COMPILER_ERROR_LINK << DEFAULT << endl;
    }
    }
}

void throw_type_error(int err_code, Type expected, Type was, Parser state) {
    string expected_dimension="(";
    string was_dimension="(";

    for (auto i : expected.dimensions) {
        expected_dimension += to_string(i) += " x ";
    }
    expected_dimension.erase(expected_dimension.end() - 3,
                             expected_dimension.end());
    expected_dimension += ")";

    for (auto i : was.dimensions) {
        was_dimension += to_string(i) += " x ";
    }
    was_dimension.erase(was_dimension.end() - 3, was_dimension.end());
    was_dimension += ")";

    string was_type_name = (was.base_type == 0)
                               ? was.custom_type
                               : enum_type_to_token_value[was.base_type];
    string expected_type_name = (expected.base_type == 0)
                                    ? expected.custom_type
                                    : enum_type_to_token_value[expected.base_type];

    string s;
    switch (err_code) {
    case TYPES_NOT_CONSISTENT: {
        s = "Types " + expected_type_name + expected_dimension +
            " and " + was_type_name + was_dimension +
            " are not consistent! (one can not be unexplicitly cast into the "
            "other)";
        print_std_error(TYPES_NOT_CONSISTENT, TYPES_NOT_CONSISTENT_LINK, s,
                        state);
    } break;
    case PREFIX_NOT_DEFINED_FOR_TYPE: {
        s = "Prefix not defined for type: " + was_type_name;
        print_std_error(PREFIX_NOT_DEFINED_FOR_TYPE,
                        PREFIX_NOT_DEFINED_FOR_TYPE_LINK, s, state);
    } break;
    case INVALID_CONVERSION: {
        s = "There does not exist a conversion function from " + expected_type_name + expected_dimension + " to " + was_type_name + was_dimension;
        print_std_error(INVALID_CONVERSION, INVALID_CONVERSION_LINK, s, state);
    } break;
    case TYPE_NOT_DEFINED: {
        s = "Type: " + was_type_name+was_dimension + "is not defined";
        print_std_error(TYPE_NOT_DEFINED, TYPE_NOT_DEFINED_LINK, s, state);
    } break;
    }
}
