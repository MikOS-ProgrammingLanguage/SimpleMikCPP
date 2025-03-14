#ifndef MIK_LEXER_H
#define MIK_LEXER_H

#include <vector>
#include <iostream>
#include <stack>

using namespace std;

// All valid tokens
enum {
    // Bitwise operators
    TT_BITWISE_AND,    // b&, 0
    TT_BITWISE_OR,     // b|, 1
    TT_BITWISE_XOR,    // ^ , 2
    TT_BITWISE_NOT,    // b!, 3
    TT_LEFT_BITSHIFT,  // <<, 4
    TT_RIGHT_BITSHIFT, // >>, 5

    // Boolean operators
    TT_LESS_THAN,             // < , 6
    TT_GREATER_THAN,          // > , 7
    TT_LESS_THAN_OR_EQUAL,    // <=, 8
    TT_GREATER_THAN_OR_EQUAL, // >=, 9
    TT_AND,                   // &&, 10
    TT_OR,                    // ||, 11
    TT_NOT,                   // ! , 12
    TT_NOT_EQUAL,             // !=, 13
    TT_EQUAL,                 // ==, 14

    // Numerical operators
    TT_PLUS,     // +, 15
    TT_MINUS,    // -, 16
    TT_ASTERISK, // *, 17 
    TT_SLASH,    // /, 18
    TT_PERCENT,  // %, 19
    
    // Assignment operators
    TT_ASSIGNMENT,   // = , 20
    TT_PLUS_EQUALS,  // *=, 21
    TT_MINUS_EQUALS, // -=, 22
    TT_TIMES_EQUALS, // *=, 23
    TT_OVER_EQUALS,  // /=, 24

    // Builtin-Types
    TT_INT,            //          , 25
    TT_FLOAT,          //          , 26
    TT_STRING_LITERAL, // "<sting>", 27
    TT_ASCII_LITERAL,  // '<char>' , 28

    // Parenthesis
    TT_OPENING_PARENTHESIS, // (, 29
    TT_CLOSING_PARENTHESIS, // ), 30
    TT_OPENING_BRACKET,     // [, 31
    TT_CLOSING_BRACKET,     // ], 32
    TT_OPENING_BRACE,       // {, 33
    TT_CLOSING_BRACE,       // }, 34

    // Other
    TT_COMMA,          // , , 35
    TT_ARROW,          // ->, 36
    TT_DOT,            // . , 37
    TT_ID,
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
