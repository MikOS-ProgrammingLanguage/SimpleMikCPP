#include "errors.hpp"
#include "lexer.hpp"
#include "utils.hpp"
#include <AST.hpp>
#include <bits/stdc++.h>
#include <ios>
#include <parser.hpp>
#include <string>
#include <vector>
#include <debug.hpp>

using namespace std;

SecondClass Parser::parse_second_class(Type expected_type) {
    return this->binary_operation(2, vector<int>({TT_AND, TT_OR}),
                                  expected_type);
}

SecondClass Parser::binary_operation(int type_of_operation,
                                     vector<int> operators_for_operation,
                                     Type expected_type) {
    // (Factor) | expr@(Factor OP Factor) | expr@(expr OP Factor) | expr@(expr
    // OP expr)
    SecondClass left_branch;
    int expression_line = this->positions_in_files.top().second;

    // What type of expression is being parsed?
    switch (type_of_operation) {
    case 2:
        left_branch = this->parse_sub_expression(expected_type);
        break;
    case 1:
        left_branch = this->parse_term(expected_type);
        break;
    case 0:
        left_branch = this->parse_factor(expected_type);
        break;
    }

    while (find(operators_for_operation.begin(), operators_for_operation.end(),
                this->current_token.token_type) !=
               operators_for_operation.end() &&
           expression_line == this->positions_in_files.top().second) {
        // Next expected token is an operator
        Token operator_token = this->current_token;
        this->advance();

        // Nothing found after operator
        if (expression_line != this->positions_in_files.top().second || this->current_token.token_type==TT_END_OF_FILE) {
            // set position back
            this->token_pos--;
            this->current_token = this->tokens[this->token_pos];
            throw_error(EXPEXTED_EXPRESSION_AFTER_OPERATION_IN_ASSIGNMENT,
                        *this);
        }

        SecondClass right_branch;
        switch (type_of_operation) {
        case 2:
            right_branch = this->parse_sub_expression(expected_type);
            break;
        case 1:
            right_branch = this->parse_term(expected_type);
            break;
        case 0:
            right_branch = this->parse_factor(expected_type);
            break;
        }

        // right branch is appended to left branch with operator
        left_branch =
            BinaryOperation(left_branch, operator_token, right_branch);
    }

    return left_branch;
}

SecondClass Parser::parse_sub_expression(Type expected_type) {
    return this->binary_operation(
        1,
        vector<int>({TT_PLUS, TT_MINUS, TT_LEFT_BITSHIFT, TT_RIGHT_BITSHIFT,
                     TT_BITWISE_AND, TT_BITWISE_OR, TT_BITWISE_XOR, TT_EQUAL,
                     TT_NOT_EQUAL, TT_LESS_THAN, TT_LESS_THAN_OR_EQUAL,
                     TT_GREATER_THAN, TT_GREATER_THAN_OR_EQUAL}),
        expected_type);
}

SecondClass Parser::parse_term(Type expected_type) {
    return this->binary_operation(
        0, vector<int>({TT_ASTERISK, TT_SLASH, TT_BITWISE_NOT}), expected_type);
}

SecondClass Parser::parse_factor(Type expected_type) {
    /* Factors can either be:
     * constants
           * strings ("a")
           * chars ('c')
           * ints (5)
           * floats (0.5)
     * variables
           * single (a)
           * array (a[0])
     * calls
           * function call (foo() / foo(a,b,...)) 
     * typecasts
           * (<expr>) -> <type>: Expressions have to be in parenthesis
     * parenthesis
          * (<expr>)

     Factors may be prefixed by either
     * -
     * !
     * b!
     */ 
    int prefix = 0;
    if (this->current_token.token_type == TT_MINUS) {
        prefix = 1;
    } else if (this->current_token.token_type == TT_NOT) {
        prefix = 2;
    } else if (this->current_token.token_type == TT_BITWISE_NOT) {
        prefix = 3;
    }

    switch (this->current_token.token_type) {
        // Constants
        case TT_STRING_LITERAL: {
            // expected_type and TYPE(STRING) are not consistent
            debug(to_string(expected_type.base_type));
            if(expected_type>BASE_TYPE_STRING(1,1)) { 
                throw_type_error(BASE_TYPES_NOT_CONSISTENT, expected_type, BASE_TYPE_STRING(1,1), *this);
            }
            DirectLiteral ret(prefix, BASE_TYPE_STRING(1,1), current_token.value);
            this->advance();
            return ret;
        } break;
        case TT_ASCII_LITERAL: {
        
        } break;
        case TT_INT: {

        } break;
        case TT_FLOAT: {

        } break;

        // Variables
        case TT_ID: {

        } break;
        // Calls
        // Parenthesis/Typecasts
    }

    // remove later!
    this->advance();
    //remove later!
    return SecondClass();
}
