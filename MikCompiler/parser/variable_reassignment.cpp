#include "lexer.hpp"
#include <AST.hpp>
#include <parser.hpp>
#include <errors.hpp>
#include <debug.hpp>


VariableAlteration Parser::parse_variable_alteration() {
    // Note name. Type is not needed, as it can be infferred by name
    VariableAlteration result = VariableAlteration();
    result.name = this->current_token.value;
    this->advance();

    // Check for equal sign
    if (this->current_token.token_type != TT_ASSIGNMENT && this->current_token.token_type != TT_MINUS_EQUALS && this->current_token.token_type != TT_PLUS_EQUALS && this->current_token.token_type != TT_TIMES_EQUALS && this->current_token.token_type != TT_OVER_EQUALS) {
        // Expected =, +=, -=, *=, or \=
        throw_error(STANDALONE_REFFERENCE_TO_VARIABLE_NOT_ALLOWED, *this);
    }

    // Denote sign
    result.reassignment_type = this->current_token;
    this->advance();

    // Parse expression with expected type 
    result.reassigned_expression = this->parse_second_class(this->VARIABLES[result.name].type);

    return result;
}

