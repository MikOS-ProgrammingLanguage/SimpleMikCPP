#ifndef MIK_PARSER_H

#include <vector>
#include <map>
#include <AST.hpp>
#include <lexer.hpp>

class Parser {
    private:
        map<string, Function> FUNCTIONS;

        vector<FirstClass> parse_until(int token);

    public:
        Parser(vector<Token> tokens, string& preprocessed_code, AST& result);
};


#endif //  MIK_PARSER_H
#define MIK_PARSER_H

