#include <errors.hpp>
#include <string>

// Accumulates the line on which the error occured and prints this line with additional information about the location
void print_error_location(Lexer state) {
    string whitespace_buffer = string(to_string(state.positions_in_files.top().second).size(), ' ');
    string line_to_print;

    // get line_to_print
    // iterate back from the current character
    int char_idx = state.current_index;
    for (char c = state.text[state.current_index]; c != '\n' && state.current_index >= 0; state.current_index--) c = state.text[state.current_index];


    if (state.text[state.current_index+1] == '\n') {
        state.current_index+=2;
        state.current_character = state.text[state.current_index];
    } else {
        state.current_index++;
        state.current_character = state.text[state.current_index];
    }

    for (;state.current_index < state.text.size() && state.current_character != '\n'; state.current_character = state.text[++state.current_index]) {
        if (char_idx == state.current_index) line_to_print += RED;

        line_to_print += state.current_character;

        if (char_idx == state.current_index) line_to_print += DEFAULT;
    }

    cout << "\r" << BLUE << "\tIn: " << state.positions_in_files.top().first << "\n\t" << whitespace_buffer << " |\n\t" << to_string(state.positions_in_files.top().second) << " | " << DEFAULT << line_to_print << "\n\t" << BLUE << whitespace_buffer << " | " << endl;
}

void print_error_location(Parser state) {
    string whitespace_buffer = string(state.current_token.line_number, ' ');
    string line_to_print;
    state.current_token.idx--;

    // get line_to_print
    // iterate back from the current character
    int char_idx = state.current_token.idx;
    char current_char;
    for (char c = state.text[state.current_token.idx]; c != '\n' && state.current_token.idx >= 0; state.current_token.idx-- ) c = state.text[state.current_token.idx];
    
    if (state.text[state.current_token.idx+1] == '\n') {
        state.current_token.idx+=2;
        current_char = state.text[state.current_token.idx];
    } else {
        state.current_token.idx++;
        current_char = state.text[state.current_token.idx];
    }

    for (; state.current_token.idx < state.text.size() && current_char != '\n'; current_char = state.text[++state.current_token.idx]) {
        if (char_idx == state.current_token.idx) line_to_print += RED;

        line_to_print += current_char;

        if (char_idx == state.current_token.idx) line_to_print += DEFAULT;
    }

    cout << "\r" << BLUE << "\tIn: " << state.current_token.file_name << "\n\t" << whitespace_buffer << " |\n\t" << to_string(state.current_token.line_number) << " | " << DEFAULT << line_to_print << "\n\t" << BLUE << whitespace_buffer << " | " << endl;
}

void print_error_location(string line, int line_number, string path) {
    string whitespace_buffer = string(to_string(line_number).size(), ' ');
    cout << "\r" << BLUE << "\tIn: " << path << "\n\t" << whitespace_buffer << " |\n\t" << to_string(line_number) << " | " << RED << line << "\n\t" << whitespace_buffer << " | " << endl;
}

void throw_error(int err_code, string line, int line_number, string path) {
    switch (err_code) {
        case ERROR_OPENING_YOINKED_FILE:
            {
                cout << RED << "\n\r[ERROR " << to_string(ERROR_OPENING_YOINKED_FILE) << "] An error occured while trying to open a yoinked file. It may not exist:\n";
                print_error_location(line, line_number, path);
                cout << GREEN << "\nRead more about this error: " << ERROR_OPENING_YOINKED_FILE << "\n" << DEFAULT << endl;
                exit(-1);
            } break;
    }
}

void throw_error(int err_code, Lexer state) {
    switch (err_code) {
        case UNEXPECTED_TOKEN:
            {
                cout << RED << "\n\r[ERROR " << to_string(UNEXPECTED_TOKEN) << "] An unexpected token (" << state.current_character << ") was found:\n" << endl;
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << UNEXPECTED_TOKEN_LINK << "\n" <<DEFAULT << endl;
                exit(-1);
            } break;
        
        case UNTERMINATED_MULTILINE_COMMENT:
            {
                cout << RED << "\n\r[ERROR " << to_string(UNTERMINATED_MULTILINE_COMMENT) << "] A multiline comment was started but never terminated:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << UNTERMINATED_MULTILINE_COMMENT_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            } break;

        case UNTERMINATED_STRING:
            {
                cout << RED << "\n\r[ERROR " << to_string(UNTERMINATED_STRING) << "] A string was started but not terminated:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << UNTERMINATED_STRING_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            } break;

        case UNEXPECTED_DECIMAL_POINT:
            {
                cout << RED << "\n\r[ERROR " << to_string(UNEXPECTED_DECIMAL_POINT) << "] An unexpected decimal point was found:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << UNEXPECTED_DECIMAL_POINT_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            } break;

        case HEX_LITERAL_EXPECTED:
            {
                cout << RED << "\n\r[ERROR " << to_string(HEX_LITERAL_EXPECTED) << "] A hex literal was expected after 0x:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << HEX_LITERAL_EXPECTED_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            }

        case BIN_LITERAL_EXPECTED:
            {
                cout << RED << "\n\r[ERROR " << to_string(BIN_LITERAL_EXPECTED) << "] A binary literal was expected after 0b:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << BIN_LITERAL_EXPECTED_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            }
        
        case UNTERMINATED_CHARACTER_LITERAL:
            {
                cout << RED << "\n\r[ERROR " << to_string(UNTERMINATED_CHARACTER_LITERAL) << "] A character literal was started but never ended:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << UNTERMINATED_CHARACTER_LITERAL_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            } break;

        case INVALID_COMPILER_DIRECTIVE:
            {
                cout << RED << "\n\r[ERROR " << to_string(INVALID_COMPILER_DIRECTIVE) << "] An invalid compiler directive (" << state.tokens[state.tokens.size()-1].value << ") was found:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << INVALID_COMPILER_DIRECTIVE_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            } break;
        
        case CLOSING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE:
            {
                cout << RED << "\n\r[ERROR " << to_string(CLOSING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE) << "] A closing parenthesis was expected in the @file compiler directive:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << CLOSING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            } break;

        case OPENING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE:
            {
                cout << RED << "\n\r[ERROR " << to_string(OPENING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE) << "] An opening parenthesis was expected in the @file compiler directive:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << OPENING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            } break;
    }
}

void throw_error(int err_code, Parser state) {
    switch (err_code) {
        case EXPECTED_IDENTIFIER_FOR_FIRST_CLASS_EXPRESSION:
            {
                cout << RED << "\n\r[ERROR " << to_string(EXPECTED_IDENTIFIER_FOR_FIRST_CLASS_EXPRESSION) << "] An identifier is expected in a first class expression:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << EXPECTED_IDENTIFIER_FOR_FIRST_CLASS_EXPRESSION_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            } break;
        case EXPECTED_VARIABLE_NAME_AFTER_TYPE:
            {
                cout << RED << "\n\r[ERROR " << to_string(EXPECTED_VARIABLE_NAME_AFTER_TYPE) << " A name was expected after a type in the definition/declaration of a variable:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << EXPECTED_VARIABLE_NAME_AFTER_TYPE_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            } break;
        case EXPECTED_BOUND_OR_ARRAY_DEFINITION_OR_ASSIGNMENT_AFTER_VARIABLE_NAME:
            {
                cout << RED << "\n\r[ERROR " << to_string(EXPECTED_BOUND_OR_ARRAY_DEFINITION_OR_ASSIGNMENT_AFTER_VARIABLE_NAME) << "A boundary ({}), array ([]), or assignment (=) was expected after a variable name in the definition/declaration of a variable:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << EXPECTED_BOUND_OR_ARRAY_DEFINITION_OR_ASSIGNMENT_AFTER_VARIABLE_NAME_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            } break;
        case EXPECTED_NEWLINE_BEFORE_NEW_FIRST_CLASS_EXPRESSION:
            {
                cout << RED << "\n\r[ERROR " << to_string(EXPECTED_NEWLINE_BEFORE_NEW_FIRST_CLASS_EXPRESSION) << " A new line was expected after the end of a first class expression:\n";
                print_error_location(state);
                cout << GREEN << "\nRead more about this error: " << EXPECTED_NEWLINE_BEFORE_NEW_FIRST_CLASS_EXPRESSION_LINK << "\n" << DEFAULT << endl;
                exit(-1);
            } break;
    }
}
