#include "errors.hpp"
#include "lexer.hpp"
#include "utils.hpp"
#include <AST.hpp>
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <debug.hpp>
#include <ios>
#include <parser.hpp>
#include <string>
#include <vector>

using namespace std;

void Parser::type_compare(Type expected_type, Type is, int prefix) {
    // if expected type is invalid type, then the factor_type is set and no error is thrown
    if (expected_type.base_type == TYPE_INVALID && expected_type.custom_type == "") {
        this->factor_type = is;
    } else if (expected_type > is) {
        // expected_type and TYPE(STRING) are not consistent
        throw_type_error(TYPES_NOT_CONSISTENT, expected_type,
                         BASE_TYPE_STRING(1), *this);
    }

    // for arrays, prefixes are applied elementwise
    // if there is no prefix, the next steps are unnecessary
    if (prefix == 0)
        return;

    // Type is custom or string => cant have builtin prefixes
    if (is.base_type == 0 || is.base_type == TYPE_STRING)
        throw_type_error(PREFIX_NOT_DEFINED_FOR_TYPE, expected_type, is, *this);

    // Character can only be prefixed by b! (bitwise not)
    if (is.base_type == TYPE_CHAR && prefix != PREFIX_BITWISE_NOT)
        throw_type_error(PREFIX_NOT_DEFINED_FOR_TYPE, expected_type, is, *this);

    // int and float can't have ! (logical not) (needs to be cast to bool first)
    if ((is.base_type == TYPE_INT || is.base_type == TYPE_FLOAT) &&
        prefix == PREFIX_NOT)
        throw_type_error(PREFIX_NOT_DEFINED_FOR_TYPE, expected_type, is, *this);
}

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
        if (expression_line != this->positions_in_files.top().second ||
            this->current_token.token_type == TT_END_OF_FILE) {
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
           * (<factor>) -> <type>: Expressions have to be in parenthesis
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
        this->advance();
    } else if (this->current_token.token_type == TT_NOT) {
        prefix = 2;
        this->advance();
    } else if (this->current_token.token_type == TT_BITWISE_NOT) {
        prefix = 3;
        this->advance();
    }

    // if token is base type
    if (this->current_token.token_type >= TT_INT &&
        this->current_token.token_type <= TT_ASCII_LITERAL) {
        Type is = BASE_TYPE_INVALID(1);

        switch (this->current_token.token_type) {
        case TT_STRING_LITERAL: {
            is = BASE_TYPE_STRING(1);
        } break;
        case TT_ASCII_LITERAL: {
            is = BASE_TYPE_CHAR(1);
        } break;
        case TT_INT: {
            is = BASE_TYPE_INT(1);
        } break;
        case TT_FLOAT: {
            is = BASE_TYPE_FLOAT(1);
        } break;
        }

        this->type_compare(expected_type, is, prefix);
        SecondClass ret;

        // if type needs to be cast unexplicitly, this is done here #TODO#
        if (expected_type < is) {
            ret = TypeCast(BASE_TYPE_STRING(1), expected_type,
                           SecondClassFunctionCall(), DirectLiteral(prefix, is, current_token.value));
        } else {
            ret =
                DirectLiteral(prefix, is, current_token.value);
        }
        this->advance();
        return ret;
    }

    // if token is either a single variable, array access, or function call
    if (this->current_token.token_type == TT_ID) {
        // Variable or Function
        if (find(this->variable_names.begin(), this->variable_names.end(),
                 this->current_token.value) != this->variable_names.end()) {
            UseVariable res(this->VARIABLES[this->current_token.value], prefix);
            this->type_compare(expected_type, res.variable.type, prefix);
            this->advance();
            return res;
        } else if (find(this->function_names.begin(),
                        this->function_names.end(),
                        this->current_token.value) !=
                   this->function_names.end()) {
            // identify function, compare result type of function to expected
            // type, then get argument, each argument has it's own expected type
            SecondClassFunctionCall res(
                this->FUNCTIONS[this->current_token.value], prefix);
            this->type_compare(expected_type, res.function.return_type, prefix);
            this->advance();

            // is name followed by parenthesis
            if (this->current_token.token_type != TT_OPENING_PARENTHESIS) {
                throw_error(EXPECTED_OPENING_PARENTHESIS_IN_FUNCTION_CALL,
                            *this);
            }
            this->advance();

            // parse arguments
            for (int i = 0; i < res.function.arguments.first.size(); ++i) {
                // expected type = i
                // 1. get expression
                // 2. check for coma (except for last argument)

                res.arguments.push_back(
                    this->parse_second_class(res.function.arguments.second[i]));
                // if there should still be a comma, but isn't
                if (this->current_token.token_type != TT_COMMA &&
                    i != res.function.arguments.first.size() - 1) {
                    throw_error(EXPECTED_COMMA_IN_FUNCTION_CALL, *this);
                }

                if (i != res.function.arguments.first.size() - 1)
                    this->advance();
            }

            // check for closing parenthesis
            if (this->current_token.token_type != TT_CLOSING_PARENTHESIS) {
                throw_error(EXPECTED_CLOSING_PARENTHESIS_IN_FUNCTION_CALL,
                            *this);
            }
            this->advance();
            return res;
        } else {
            throw_error(UNKNOWN_IDENTIFIER_IN_EXPRESSION, *this);
        }
    }

    // Parenthesis/Typecasts
    if (this->current_token.token_type == TT_OPENING_PARENTHESIS) {
        this->advance();

        int pos = this->token_pos;
        // the current token position is noted, then the expression within
        // parenthesis is evaluated, then, wether it's a typecast or not is
        // checked. If so, the type is determined, and the current token
        // position and current token are set to the noted value, now expr is
        // evaluated again, this time with the type cast to.
        SecondClass type_cast_expr = this->parse_second_class(BASE_TYPE_INVALID(1));

        if (this->current_token.token_type != TT_CLOSING_PARENTHESIS) {
            throw_error(EXPECTED_CLOSING_PARENTHESIS, *this);
        }
        this->advance();

        // typecast
        if (this->current_token.token_type == TT_ARROW) {
            TypeCast res = TypeCast(BASE_TYPE_INVALID(1), BASE_TYPE_INVALID(1),
                         SecondClassFunctionCall(), SecondClass());
            this->advance();

            // valid type
            if (this->current_token.token_type == TT_ID &&
                find(type_names.begin(), type_names.end(),
                     this->current_token.value) != type_names.end()) {
                res.to = token_value_to_type[this->current_token.value];
                this->type_compare(expected_type, res.to, prefix);

                // perform expr again
                this->token_pos = pos-1;
                this->advance(); // reload beginning token
                
                // parse factor and determine type
                this->dont_allow_parenthesis = true;
                res.expression = this->parse_factor(BASE_TYPE_INVALID(1));
                res.from = this->factor_type;
                this->dont_allow_parenthesis = false;

                // determine conversion function and wether the conversion is valid
                if (typecast_functions.find(pair<Type, Type>(res.from, res.to)) == typecast_functions.end()) {
                    throw_type_error(INVALID_CONVERSION, res.from, res.to, *this);
                }
                res.typecast_function  = typecast_functions[pair<Type, Type>(res.from, res.to)];

                if (this->current_token.token_type != TT_CLOSING_PARENTHESIS) {
                    throw_error(EXPECTED_CLOSING_PARENTHESIS, *this);
                }
                this->advance();

                return res;
            } else {
                // invalid type
                throw_type_error(TYPE_NOT_DEFINED, BASE_TYPE_INVALID(1), Type(0, this->current_token.value, DIM(1)), *this);
            }
        } else {
            // if this is even allowed
            if (this->dont_allow_parenthesis) {
                this->token_pos = pos-2;
                this->advance();

                throw_error(EXPRESSION_IN_PARENTHESIS_NOT_ALLOWED, *this);
            }

            // no arrow, evaluate expression normally again
            this->token_pos = pos-1;
            this->advance();
            
            SecondClass expr = this->parse_second_class(expected_type);

            if (this->current_token.token_type != TT_CLOSING_PARENTHESIS) {
                throw_error(EXPECTED_CLOSING_PARENTHESIS, *this);
            }
            this->advance();

            return expr;
        }
    }

    // something went wrong if this is reached
    throw_compiler_error(COMPILER_ERROR);
    return SecondClass();
}
