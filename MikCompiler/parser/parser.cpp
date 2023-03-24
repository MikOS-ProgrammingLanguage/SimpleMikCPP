#include <AST.hpp>
#include <parser.hpp>
#include <lexer.hpp>

Parser::Parser(vector<Token> tokens, string& preprocessed_code, AST& result) {
    // implement standart built-ins
    this->FUNCTIONS["puts"] = Function();
}
