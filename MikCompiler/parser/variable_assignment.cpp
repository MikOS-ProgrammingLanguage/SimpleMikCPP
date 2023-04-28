#include "errors.hpp"
#include "lexer.hpp"
#include <AST.hpp>
#include <algorithm>
#include <debug.hpp>
#include <parser.hpp>
#include <utils.hpp>

Type convert_token_to_type(Token t) {
  if (find(type_names.begin(), type_names.end(), t.value) != type_names.end()) {
    return Type(token_value_to_type[t.value], "", 0);
  } else {
    return Type(TYPE_INVALID, t.value, 0);
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
  VariableAssignment result = VariableAssignment();

  result.type = convert_token_to_type(this->current_token);
  this->advance();

  // Name ID expected
  if (this->current_token.token_type != TT_ID) {
    throw_error(EXPECTED_VARIABLE_NAME_AFTER_TYPE, *this);
  }
  result.name = current_token.value;
  this->advance();

  // Array with n dimensions,
  // or a bound
  if (this->current_token.token_type != TT_ASSIGNMENT &&
      this->current_token.token_type != TT_OPENING_BRACKET &&
      this->current_token.token_type != TT_OPENING_BRACE) {
    throw_error(
        EXPECTED_BOUND_OR_ARRAY_DEFINITION_OR_ASSIGNMENT_AFTER_VARIABLE_NAME,
        *this);
  }

  // Array
  if (this->current_token.token_type == TT_OPENING_BRACKET) {
    this->advance();
  }

  // Check for bound
  if (this->current_token.token_type == TT_OPENING_BRACE) {
    this->advance();
    result.is_bounded = true;
  }

  // Check for assignment operator
  if (this->current_token.token_type != TT_ASSIGNMENT) {
    result.is_declared = true;
    this->advance();
    return result;
  }
  this->advance();

  // expression for assignment with given type (have to be on the same line)
  result.assigned_expression = this->parse_second_class(result.type);

  return result;
}
