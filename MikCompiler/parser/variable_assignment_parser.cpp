#include "errors.hpp"
#include "lexer.hpp"
#include <AST.hpp>
#include <algorithm>
#include <debug.hpp>
#include <parser.hpp>
#include <utils.hpp>

Type convert_token_to_type(Token t) {
    // if type isnt invalid
    if (find(type_names.begin(), type_names.end(), t.value) !=
        type_names.end()) {
        return Type(token_value_to_type_enum[t.value], "", DIM(1));
    } else {
        return Type(TYPE_INVALID, t.value, DIM(1));
    }
}

/* An assigned variable will look like:
    <type> name               = <expression>
    <type> name[][]...
    <type> name[<expression>]

all of those can be followed by:
    ... name ...{roll, <expression_lower_bound>, <expression_upper_bound>} =
<expression>
    ... name ...{keep, <expression_lower_bound>, <expression_upper_bound>} =
<expression> on arrays this will simply apply to all variables in that array
*/
VariableAssignment Parser::parse_variable_assignment() {
    int current_line = this->current_token.line_number;
    VariableAssignment result = VariableAssignment();

    result.type = convert_token_to_type(this->current_token);
    debug(to_string(result.type.base_type));
    this->advance();

    // Name ID expected
    if (this->current_token.token_type != TT_ID) {
        throw_error(EXPECTED_VARIABLE_NAME_AFTER_TYPE, *this);
    }
    result.name = current_token.value;
    debug(result.name);
    this->advance();
    // check availablility
    if (find(this->variable_names.begin(), this->variable_names.end(),
             result.name) != this->variable_names.end() ||
        find(keywords.begin(), keywords.end(), result.name) != keywords.end()) {
        throw_error(VARIABLE_NAME_TAKEN_OR_KEYWORD, *this);
    }

    // append name to existing variable names
    this->variable_names.push_back(result.name); 

    // Array with n dimensions,
    // or a bound
    if (this->current_token.token_type != TT_ASSIGNMENT &&
        this->current_token.token_type != TT_OPENING_BRACKET &&
        this->current_token.token_type != TT_OPENING_BRACE) {
        throw_error(
            EXPECTED_BOUND_OR_ARRAY_DEFINITION_OR_ASSIGNMENT_AFTER_VARIABLE_NAME,
            *this);
    }

    // Array #TODO#
    if (this->current_token.token_type == TT_OPENING_BRACKET) {
        this->advance();
    }

    // check for custom guard #TODO#

    // Check for bound #TODO#
    if (this->current_token.token_type == TT_OPENING_BRACE) {
        // builtin guards only work on numbers
        if (result.type.base_type != TYPE_INT &&
            result.type.base_type != TYPE_FLOAT) {
            throw_error(BUILTIN_GUARDS_TYPE_MISSMATCH, *this);
        }
        this->advance();
        result.is_bounded = true;
    }

    // Check for assignment operator
    if (this->current_token.token_type != TT_ASSIGNMENT) {
        result.is_declared = true;
        this->advance();
        return result;
    }
    debug("Hit assignment");
    this->advance();

    // expression for assignment with given type (have to be on the same line)
    result.assigned_expression = this->parse_second_class(result.type);
    
    if (this->current_token.line_number == current_line) {
      throw_error(EXPECTED_NEWLINE_BEFORE_NEW_FIRST_CLASS_EXPRESSION, *this);
    }

    return result;
}
