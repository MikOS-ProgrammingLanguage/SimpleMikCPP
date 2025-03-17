#ifndef MIK_PARSER_H

#include <vector>
#include <map>
#include <AST.hpp>
#include <lexer.hpp>

class Parser {
    private:
        Type factor_type;
        bool dont_allow_parenthesis;

        vector<FirstClass> parse_until(int token);
        VariableAssignment parse_variable_assignment();
        VariableAlteration parse_variable_alteration();

        SecondClass        parse_second_class(Type expected_type);
        SecondClass binary_operation(int type_of_operation, vector<int>operators_for_operation, Type expected_type); // Type of operation is used to distinguish between 3 different types of operation: 0=factor, 1=term, 2=sub_expression
        SecondClass parse_sub_expression(Type expected_type);
        SecondClass parse_term(Type expected_type);
        SecondClass parse_factor(Type expected_type);
        void type_compare(Type expected_type, Type is, int prefix); // throws error if types are not consistent with one another

        void init_builtins();
        void advance();

    public:
        Parser(vector<Token> _tokens, stack<pair<string, int> > &_file_info, string &_text, AST& result);

        // The stack is  used to track the location in different files
        stack<pair<string, int> > &positions_in_files; // <File_Name, Line>
        
        int token_pos;
        Token current_token;

        map<string, Function> FUNCTIONS;
        vector<string> function_names;

        map<string, VariableAssignment> VARIABLES;
        vector<string> variable_names;

        vector<Token> tokens;
        string &text;
};


#endif //  MIK_PARSER_H
#define MIK_PARSER_H

