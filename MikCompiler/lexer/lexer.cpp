#include <algorithm>
#include <debug.hpp>
#include <errors.hpp>
#include <lexer.hpp>

Lexer::Lexer(string text) {
    this->text = text;
    this->current_index = -1;
    this->tokens = vector<Token>(0);
    this->positions_in_files.push(pair<string, int>("", 0));
    this->advance();
}

void Lexer::advance() {
    this->current_index++;
    this->current_character = (this->current_index) >= this->text.size()
                                  ? '\0'
                                  : this->text[this->current_index];
}

void Lexer::lex_string_token() {
    int start_index = this->current_index;
    string res = "";

    this->advance(); // skip over "
    for (; this->current_character != '\0' && this->current_character != '"';
         this->advance())
        res += this->current_character;

    // check if string was terminated
    if (this->current_character != '"') {
        // prepare tokens for error this->current_index = start_index;
        this->current_index = start_index;
        this->current_character = this->text[this->current_index];

        throw_error(UNTERMINATED_STRING, *this);
    } else
        this->tokens.push_back(Token{
            .file_name = this->positions_in_files.top().first,
            .line_number = this->positions_in_files.top().second,
            .idx = this->current_index,
            .token_type = TT_STRING_LITERAL,
            .value = res,
        });
}

void Lexer::lex_id_token() {
    string res = "";

    // check if characters within legal characters for any ID and append
    for (; this->current_character != '\0' &&
           ((find(LEGAL_CHARACTERS_IN_ID.begin(), LEGAL_CHARACTERS_IN_ID.end(),
                  this->current_character) != LEGAL_CHARACTERS_IN_ID.end()) ||
            (find(LEGAL_CHARACTERS_IN_NUMBER.begin(),
                  LEGAL_CHARACTERS_IN_NUMBER.end(), this->current_character) !=
             LEGAL_CHARACTERS_IN_NUMBER.end()));
         this->advance())
        res += this->current_character;

    this->tokens.push_back(Token{
        .file_name = this->positions_in_files.top().first,
        .line_number = this->positions_in_files.top().second,
        .idx = this->current_index,
        .token_type = TT_ID,
        .value = res,
    });
    this->current_index--;
}

void Lexer::lex_number_token(bool hex_prefix = false, bool bin_prefix = false) {
    string res = "";
    bool decimal_point_occured = false;
    int token_type = TT_INT;

    if (hex_prefix) {
        // hex number
        // check if characters within legal characters for any hex number and
        // append
        for (; this->current_character != '\0' &&
               ((find(LEGAL_HEXADECIMAL_CHARACTERS.begin(),
                      LEGAL_HEXADECIMAL_CHARACTERS.end(),
                      this->current_character) !=
                 LEGAL_HEXADECIMAL_CHARACTERS.end()) ||
                this->current_character == '.');
             this->advance()) {
            if (this->current_character == '.')
                throw_error(UNEXPECTED_DECIMAL_POINT, *this);
            res += this->current_character;
        }

        // convert to base 10 literal and back to string
        size_t i;
        res = to_string(stoi(res, &i, 16));
    } else if (bin_prefix) {
        // check if characters within legal characters for any binary number and
        // append
        for (; this->current_character != '\0' &&
               ((find(LEGAL_BINARY_CHARACTERS.begin(),
                      LEGAL_BINARY_CHARACTERS.end(), this->current_character) !=
                 LEGAL_BINARY_CHARACTERS.end()) ||
                this->current_character == '.');
             this->advance()) {
            if (this->current_character == '.')
                throw_error(UNEXPECTED_DECIMAL_POINT, *this);
            res += this->current_character;
        }

        // convert to base 10 literal and back to string
        size_t i;
        res = to_string(stoi(res, &i, 2));
    } else {
        // check if characters within legal characters for any base 10 number
        // and append
        for (; this->current_character != '\0' &&
               ((find(LEGAL_CHARACTERS_IN_NUMBER.begin(),
                      LEGAL_CHARACTERS_IN_NUMBER.end(),
                      this->current_character) !=
                 LEGAL_CHARACTERS_IN_NUMBER.end()) ||
                this->current_character == '.');
             this->advance()) {
            if (this->current_character == '.') {
                if (decimal_point_occured)
                    throw_error(UNEXPECTED_DECIMAL_POINT, *this);
                else {
                    token_type = TT_FLOAT;
                    decimal_point_occured = true;
                }
            }
            res += this->current_character;
        }
    }

    this->tokens.push_back(Token{
        .file_name = this->positions_in_files.top().first,
        .line_number = this->positions_in_files.top().second,
        .idx = this->current_index,
        .token_type = token_type,
        .value = res,
    });
    this->current_index--;
}

pair<vector<Token>, stack<pair<string, int>>> Lexer::lex(void) {
    while (this->current_character != '\0') {
        // Analyze each character
        switch (current_character) {
        // skip whitespaces
        case ' ':
            break;
        case '\t':
            break;
        case '\n': {
            // increase line number on \n
            this->positions_in_files.top().second++;
        } break;

        // Operators
        case '<': {
            this->advance();

            if (current_character == '=')
                // <=
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_LESS_THAN_OR_EQUAL,
                });
            else if (current_character == '<')
                // <<
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_LEFT_BITSHIFT,
                });
            else {
                // <
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_LESS_THAN,
                });

                this->current_index--;
            }
        } break;

        case '>': {
            this->advance();

            if (current_character == '=')
                // >=
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_GREATER_THAN_OR_EQUAL,
                });
            else if (current_character == '<')
                // >>
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_RIGHT_BITSHIFT,
                });
            else {
                // >
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_GREATER_THAN,
                });

                this->current_index--;
            }
        } break;

        case '=': {
            this->advance();

            if (current_character == '=')
                // ==
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_EQUAL,
                });
            else {
                // =
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_ASSIGNMENT,
                });

                this->current_index--;
            }
        } break;

        case '&': {
            this->advance();

            if (this->current_character == '&')
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_AND,
                });
            else
                throw_error(UNEXPECTED_TOKEN, *this);
        } break;

        case '!': {
            this->advance();

            if (this->current_character == '=')
                // !=
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_NOT_EQUAL,
                });
            else {
                // !
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_NOT,
                });

                this->current_index--;
            }
        } break;

        case '|': {
            this->advance();

            if (this->current_character == '|')
                // ||
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_OR,
                });
            else
                throw_error(UNEXPECTED_TOKEN, *this);
        } break;
        case '+': {
            this->advance();

            if (current_character == '=')
                // +=
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_PLUS_EQUALS,
                });
            else {
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_PLUS,
                    .value = "+",
                });

                this->current_index--;
            }
        } break;

        case '-': {
            this->advance();

            if (current_character == '=')
                // -=
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_MINUS_EQUALS,
                });
            else if (current_character == '>')
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .token_type = TT_ARROW,
                });
            else {
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_MINUS,
                });

                this->current_index--;
            }
        } break;

        case '*': {
            this->advance();

            if (current_character == '=')
                // *=
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_TIMES_EQUALS,
                });
            else {
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_ASTERISK,
                });

                this->current_index--;
            }
        } break;

        case '/': {
            this->advance();

            if (current_character == '=')
                // /=
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_OVER_EQUALS,
                });
            else if (current_character == '/') {
                // //
                while (this->current_character != '\n' &&
                       this->current_character != '\0') {
                    this->advance();
                }

                this->current_index--;
            } else if (current_character == '*') {
                // /*
                this->advance();

                while (current_character != '\0') {
                    if (current_character == '*') {
                        this->advance();
                        if (current_character == '/') {
                            // */
                            this->advance();
                            break;
                        }
                    } else if (current_character == '\n')
                        this->positions_in_files.top().second++;
                    advance();
                }

                if (current_character == '\0')
                    throw_error(UNTERMINATED_MULTILINE_COMMENT, *this);

            } else {
                this->tokens.push_back(Token{
                    .file_name = this->positions_in_files.top().first,
                    .line_number = this->positions_in_files.top().second,
                    .idx = this->current_index,
                    .token_type = TT_SLASH,
                });

                this->current_index--;
            }
        } break;

        case '%': {
            this->tokens.push_back(Token{
                .file_name = this->positions_in_files.top().first,
                .line_number = this->positions_in_files.top().second,
                .idx = this->current_index,
                .token_type = TT_PERCENT,
            });
        } break;

        case ',': {
            this->tokens.push_back(Token{
                .file_name = this->positions_in_files.top().first,
                .line_number = this->positions_in_files.top().second,
                .idx = this->current_index,
                .token_type = TT_COMMA,
            });
        } break;

        case '.': {
            this->tokens.push_back(Token{
                .file_name = this->positions_in_files.top().first,
                .line_number = this->positions_in_files.top().second,
                .idx = this->current_index,
                .token_type = TT_DOT,
            });
        } break;

        case '^': {
            this->tokens.push_back(Token{
                .file_name = this->positions_in_files.top().first,
                .line_number = this->positions_in_files.top().second,
                .idx = this->current_index,
                .token_type = TT_BITWISE_XOR,
            });
        } break;

        case '(': {
            this->tokens.push_back(Token{
                .file_name = this->positions_in_files.top().first,
                .line_number = this->positions_in_files.top().second,
                .idx = this->current_index,
                .token_type = TT_OPENING_PARENTHESIS,
            });
        } break;

        case ')': {
            this->tokens.push_back(Token{
                .file_name = this->positions_in_files.top().first,
                .line_number = this->positions_in_files.top().second,
                .idx = this->current_index,
                .token_type = TT_CLOSING_PARENTHESIS,
            });
        } break;

        case '[': {
            this->tokens.push_back(Token{
                .file_name = this->positions_in_files.top().first,
                .line_number = this->positions_in_files.top().second,
                .idx = this->current_index,
                .token_type = TT_OPENING_BRACKET,
            });
        } break;

        case ']': {
            this->tokens.push_back(Token{
                .file_name = this->positions_in_files.top().first,
                .line_number = this->positions_in_files.top().second,
                .idx = this->current_index,
                .token_type = TT_CLOSING_BRACKET,
            });
        } break;

        case '{': {
            this->tokens.push_back(Token{
                .file_name = this->positions_in_files.top().first,
                .line_number = this->positions_in_files.top().second,
                .idx = this->current_index,
                .token_type = TT_OPENING_BRACE,
            });
        } break;

        case '}': {
            this->tokens.push_back(Token{
                .file_name = this->positions_in_files.top().first,
                .line_number = this->positions_in_files.top().second,
                .idx = this->current_index,
                .token_type = TT_CLOSING_BRACE,
            });
        } break;

        case '@': {
            // Implement different compiler directives
            /*
             - @file("f_path")
             - @fend
             - @attr(<attr>)
            */

            this->advance();

            // get the next ID. This should be either file or attr
            this->lex_id_token();
            if (this->tokens[this->tokens.size() - 1].value == "file") {
                // remove token
                this->tokens.pop_back();
                this->advance();

                if (this->current_character == '(') {
                    this->advance();
                    this->lex_string_token();
                    this->advance();

                    // push new file to the positions stack. Will be popped if
                    // @fend occurs
                    this->positions_in_files.push(pair<string, int>(
                        this->tokens[this->tokens.size() - 1].value, 1));
                    this->tokens.pop_back();

                    if (this->current_character != ')') {
                        throw_error(
                            CLOSING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE,
                            *this);
                    }
                } else {
                    throw_error(
                        OPENING_PARENTHESIS_EXPECTED_IN_FILE_COMPILER_DIRECTIVE,
                        *this);
                }
            } else if (this->tokens[this->tokens.size() - 1].value == "fend") {
                // remove token
                this->tokens.pop_back();
                this->positions_in_files.pop();
            } else if (this->tokens[this->tokens.size() - 1].value == "attr") {
                // remove token
                this->tokens.pop_back();
            } else {
                throw_error(INVALID_COMPILER_DIRECTIVE, *this);
            }

        } break;

        case '"': {
            this->lex_string_token();
        } break;

        case '\'': {
            this->advance();
            this->tokens.push_back(Token{
                .file_name = this->positions_in_files.top().first,
                .line_number = this->positions_in_files.top().second,
                .idx = this->current_index,
                .token_type = TT_ASCII_LITERAL,
                .value = string(1, this->current_character),
            });

            this->advance();
            if (current_character != '\'') {
                this->current_index--;
                this->current_character = this->text[this->current_index];
                throw_error(UNTERMINATED_CHARACTER_LITERAL, *this);
            }
        } break;

        // check for number with prefix
        case '0': {
            this->advance();

            if (this->current_character == 'x') {
                // hex
                this->advance();

                // has to have at least one hex character after 0x
                if (find(LEGAL_HEXADECIMAL_CHARACTERS.begin(),
                         LEGAL_HEXADECIMAL_CHARACTERS.end(),
                         this->current_character) ==
                    LEGAL_HEXADECIMAL_CHARACTERS.end()) {
                    this->current_index--;
                    this->current_character = 'x';
                    throw_error(HEX_LITERAL_EXPECTED, *this);
                }

                this->lex_number_token(true, false);
            } else if (this->current_character == 'b') {
                // bin
                this->advance();

                // has to have at least one bin character after 0b
                if (find(LEGAL_BINARY_CHARACTERS.begin(),
                         LEGAL_BINARY_CHARACTERS.end(),
                         this->current_character) ==
                    LEGAL_BINARY_CHARACTERS.end()) {
                    this->current_index--;
                    this->current_character = 'b';
                    throw_error(BIN_LITERAL_EXPECTED, *this);
                }

                this->lex_number_token(false, true);
            } else {
                this->current_index--;
                this->current_character = '0';
                this->lex_number_token();
            }
        } break;

        default: {
            if ((find(LEGAL_CHARACTERS_IN_ID.begin(),
                      LEGAL_CHARACTERS_IN_ID.end(), this->current_character) !=
                 LEGAL_CHARACTERS_IN_ID.end())) {
                // ID
                this->lex_id_token();
            } else if ((find(LEGAL_CHARACTERS_IN_NUMBER.begin(),
                             LEGAL_CHARACTERS_IN_NUMBER.end(),
                             this->current_character) !=
                        LEGAL_CHARACTERS_IN_NUMBER.end())) {
                // Number
                this->lex_number_token();
            } else
                throw_error(UNEXPECTED_TOKEN, *this);
        } break;
        }
        this->advance();
    }

    return pair<vector<Token>, stack<pair<string, int>>>(
        this->tokens, this->positions_in_files);
}
