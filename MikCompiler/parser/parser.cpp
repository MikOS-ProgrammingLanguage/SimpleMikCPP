#include "errors.hpp"
#include <AST.hpp>
#include <algorithm>
#include <debug.hpp>
#include <lexer.hpp>
#include <parser.hpp>
#include <utils.hpp>

void Parser::init_builtins() {
    // puts builtin
    this->FUNCTIONS["puts"] = Function();
    this->FUNCTIONS["puts"].declared = true;
    this->FUNCTIONS["puts"].function_name = "puts";
    this->FUNCTIONS["puts"].arguments =
        pair<vector<VariableAssignment>, vector<Type>>({VariableAssignment()},
                                                       {BASE_TYPE_STRING(1)});
    this->FUNCTIONS["puts"].return_type = BASE_TYPE_INT(1);
    this->FUNCTIONS["puts"].body = AST(vector<FirstClass>(0));
    this->FUNCTIONS["puts"].behavioural_descriptors =
        vector<int>{DESCRIPTOR_NORET};
    this->function_names.push_back("puts");
}

void Parser::advance() {
    this->current_token = ((this->token_pos++) < this->tokens.size() - 1)
                              ? this->tokens[this->token_pos]
                              : Token{
                                    .file_name = "",
                                    .line_number = 0,
                                    .token_type = TT_END_OF_FILE,
                                    .value = "EOF",
                                    .imm_value = 0,
                                };
    debug("CURR: " + this->current_token.value +", " + to_string(this->current_token.token_type));
}

vector<FirstClass> Parser::parse_until(int token) {
    vector<FirstClass> result(0);

    // advance until next token should happen in each branch
    for (; this->current_token.token_type != TT_END_OF_FILE &&
           this->current_token.token_type != token;) {
        // Each statement or line start has to start with an ID
        if (this->current_token.token_type != TT_ID) {
            throw_error(EXPECTED_IDENTIFIER_FOR_FIRST_CLASS_EXPRESSION, *this);
        }

        // If the ID is a type, a variable declaration or definition is expected
        if (find(type_names.begin(), type_names.end(),
                 this->current_token.value) != type_names.end() ||
            find(struct_types.begin(), struct_types.end(),
                 this->current_token.value) != struct_types.end()) {
            debug("type found (first class)");
            result.push_back(this->parse_variable_assignment()); // Some TODO left
        } 
        // Variable reassignment
        else if (find(this->variable_names.begin(), this->variable_names.end(), this->current_token.value) != this->variable_names.end()) {
            debug("variable name found. Expect variable reassignment");
            result.push_back(this->parse_variable_reassignment());
        }

        // TODO:
    }

    return result;
}

Parser::Parser(vector<Token> _tokens, stack<pair<string, int>> &_file_info,
               string &_text, AST &result)
    : positions_in_files(_file_info), text(_text) {
    this->positions_in_files = _file_info;
    this->text = _text;
    this->tokens = _tokens;
    this->token_pos = 0;
    this->current_token = this->tokens[0];
    this->function_names = vector<string>(0);

    // implement standart built-ins
    this->init_builtins();

    // Parse tokens
    result.nodes = this->parse_until(TT_END_OF_FILE); // parse until end of file
}
