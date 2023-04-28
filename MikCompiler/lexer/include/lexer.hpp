#ifndef MIK_LEXER_H
#define MIK_LEXER_H

#include <vector>
#include <iostream>
#include <stack>

using namespace std;

// All valid tokens
enum {
    // Bitwise operators
    TT_BITWISE_AND,    // b&
    TT_BITWISE_OR,     // b|
    TT_BITWISE_XOR,    // ^
    TT_BITWISE_NOT,    // b!
    TT_LEFT_BITSHIFT,  // <<
    TT_RIGHT_BITSHIFT, // >>

    // Boolean operators
    TT_LESS_THAN,             // <
    TT_GREATER_THAN,          // >
    TT_LESS_THAN_OR_EQUAL,    // <=
    TT_GREATER_THAN_OR_EQUAL, // >=
    TT_AND,                   // &&
    TT_OR,                    // ||
    TT_NOT,                   // !
    TT_NOT_EQUAL,             // !=
    TT_EQUAL,                 // ==

    // Numerical operators
    TT_PLUS,     // +
    TT_MINUS,    // -
    TT_ASTERISK, // *
    TT_SLASH,    // /
    TT_PERCENT,  // %
    
    // Assignment operators
    TT_ASSIGNMENT,   // =
    TT_PLUS_EQUALS,  // *=
    TT_MINUS_EQUALS, // -=
    TT_TIMES_EQUALS, // *=
    TT_OVER_EQUALS,  // /=

    // Numbers
    TT_INT,
    TT_FLOAT,

    // Parenthesis
    TT_OPENING_PARENTHESIS, // (
    TT_CLOSING_PARENTHESIS, // )
    TT_OPENING_BRACKET,     // [
    TT_CLOSING_BRACKET,     // ]
    TT_OPENING_BRACE,       // {
    TT_CLOSING_BRACE,       // }

    // Other
    TT_COMMA,          // ,
    TT_ARROW,          // ->
    TT_DOT,            // .
    TT_ID,
    TT_STRING_LITERAL, // "<sting>"
    TT_ASCII_LITERAL,  // '<char>'
    TT_END_OF_FILE,    // Marks the end of the input file
    
    // Compiler directives
    TT_ATTRIBUTE, // @attribute(<attr>) for structs
};

// All characters allowed in an identifier
const static vector<char> LEGAL_CHARACTERS_IN_ID = { 'a'
                                                   , 'b'
                                                   , 'c'
                                                   , 'd'
                                                   , 'e'
                                                   , 'f'
                                                   , 'g'
                                                   , 'h'
                                                   , 'i'
                                                   , 'j'
                                                   , 'k'
                                                   , 'l'
                                                   , 'm'
                                                   , 'n'
                                                   , 'o'
                                                   , 'p'
                                                   , 'q'
                                                   , 'r'
                                                   , 's'
                                                   , 't'
                                                   , 'u'
                                                   , 'v'
                                                   , 'w'
                                                   , 'x'
                                                   , 'y'
                                                   , 'z'
                                                   , 'A'
                                                   , 'B'
                                                   , 'C'
                                                   , 'D'
                                                   , 'E'
                                                   , 'F'
                                                   , 'G'
                                                   , 'H'
                                                   , 'I'
                                                   , 'J'
                                                   , 'K'
                                                   , 'L'
                                                   , 'M'
                                                   , 'N'
                                                   , 'O'
                                                   , 'P'
                                                   , 'Q'
                                                   , 'R'
                                                   , 'S'
                                                   , 'T'
                                                   , 'U'
                                                   , 'V'
                                                   , 'W'
                                                   , 'X'
                                                   , 'Y'
                                                   , 'Z'
                                                   , '_' };

// All characters allowed in a number literal
const static vector<char> LEGAL_CHARACTERS_IN_NUMBER = { '0'
                                                       , '1'
                                                       , '2'
                                                       , '3'
                                                       , '4'
                                                       , '5'
                                                       , '6'
                                                       , '7'
                                                       , '8'
                                                       , '9' };

// All letters allowed in a hexadecimal number
const static vector<char> LEGAL_HEXADECIMAL_CHARACTERS = { 'a'
                                                         , 'b'
                                                         , 'c'
                                                         , 'd'
                                                         , 'e'
                                                         , 'f'
                                                         , 'A'
                                                         , 'B'
                                                         , 'C'
                                                         , 'D'
                                                         , 'E'
                                                         , 'F'
                                                         , '0'
                                                         , '1'
                                                         , '2'
                                                         , '3'
                                                         , '4'
                                                         , '5'
                                                         , '6'
                                                         , '7'
                                                         , '8'
                                                         , '9' };

const static vector<char> LEGAL_BINARY_CHARACTERS = { '0', '1' };

// Token struct generated by lexer for each token
struct Token {
    string file_name;
    int line_number;
    int idx;
    int token_type;
    string value;
    int imm_value;
};

// Lexer class
class Lexer {
    public:
        Lexer(string text);
        pair<vector<Token>, stack<pair<string, int> > > lex(void);

        vector<Token> tokens;

        int current_index;
        char current_character;
        string text;

        // The stack is  used to track the location in different files
        stack<pair<string, int> > positions_in_files; // <File_Name, Line>

    private:
        // Specific declarations for methods used within lex
        void advance();          // advances to the next character
        void lex_string_token(); // returns a token for a string if found
        void lex_id_token();     // returns a token for a id if found
        void lex_number_token(bool hex_prefix, bool bin_prefix); // returns a token for a number if found
};

#endif // MIK_LEXER_H
