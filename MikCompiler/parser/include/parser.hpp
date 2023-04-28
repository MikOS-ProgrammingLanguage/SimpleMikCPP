#ifndef MIK_PARSER_H

#include <vector>
#include <map>
#include <AST.hpp>
#include <lexer.hpp>

class Parser {
    private:
        vector<FirstClass> parse_until(int token);
        VariableAssignment parse_variable_assignment();
        SecondClass        parse_second_class(Type expected_type);

        void init_builtins();
        void advance();
        bool check_lines_match(int line);

    public:
        Parser(vector<Token> _tokens, stack<pair<string, int> > &_file_info, string &_text, AST& result);

        // The stack is  used to track the location in different files
        stack<pair<string, int> > &positions_in_files; // <File_Name, Line>
        
        int token_pos;
        Token current_token;

        map<string, Function> FUNCTIONS;
        vector<string> function_names;

        vector<Token> tokens;
        string &text;
};


#endif //  MIK_PARSER_H
#define MIK_PARSER_H

