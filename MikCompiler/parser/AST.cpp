#include <AST.hpp>
#include <utility>
#include <utils.hpp>
#include <valarray>

// Type
Type::Type(int _base_type, string _custom_type, pair<int, int> _dimensions) {
    this->base_type = _base_type;
    this->custom_type = _custom_type;
    this->dimensions = _dimensions;
}

bool operator==(const Type &lhs, const Type &rhs) {
    return (lhs.dimensions.first==rhs.dimensions.first) && (lhs.dimensions.second == rhs.dimensions.second) && (lhs.base_type == rhs.base_type) && (lhs.custom_type == rhs.custom_type);

}

bool operator!=(const Type& lhs, const Type& rhs) {
    return!(lhs==rhs);
}

bool operator>=(const Type& lhs, const Type& rhs) {
    return (lhs.dimensions==rhs.dimensions) && (lhs.dimensions.second == rhs.dimensions.second) && (lhs.base_type >= rhs.base_type) && (lhs.custom_type == rhs.custom_type);
}

bool operator>(const Type& lhs, const Type& rhs) {
    return (lhs.dimensions==rhs.dimensions) && (lhs.dimensions.second == rhs.dimensions.second) && (lhs.base_type > rhs.base_type) && (lhs.custom_type == rhs.custom_type);
}

bool operator<=(const Type& lhs, const Type& rhs) {
    return (lhs.dimensions==rhs.dimensions) && (lhs.dimensions.second == rhs.dimensions.second) && (lhs.base_type <= rhs.base_type) && (lhs.custom_type == rhs.custom_type);
}

// VariableAssignment
VariableAssignment::VariableAssignment() : type(BASE_TYPE_INVALID(1,1)) {
    this->is_declared = false;
    this->is_bounded = false;
}

// AST
AST::AST(vector<FirstClass> _nodes) {
    this->type = NT_AST;
    this->nodes = _nodes;
}

// Function
Function::Function(bool _declared, string _function_name,
                   pair<vector<VariableAssignment>, vector<Type>> _arguments,
                   Type _return_type, AST _body,
                   vector<int> _behavioural_descriptors,
                   map<string, VariableAssignment> _internaly_known_variables,
                   map<string, Function> _internaly_known_functions,
                   map<string, Struct> _internaly_known_structs)
    : return_type(_return_type), body(_body.nodes) {
    this->declared = _declared;
    this->function_name = _function_name;
    this->arguments = _arguments;
    this->return_type = _return_type;
    this->body = _body;
    this->behavioural_descriptors = _behavioural_descriptors;
    this->internaly_known_variables = _internaly_known_variables;
    this->internaly_known_functions = _internaly_known_functions;
    this->internaly_known_structs = _internaly_known_structs;
}

Function::Function() : return_type(BASE_TYPE_INVALID(1,1)), body(vector<FirstClass>()) {}

// Second Class
// Binary Operation
BinaryOperation::BinaryOperation(SecondClass left_branch, Token op,
                                 SecondClass right_branch) {
    this->left_branch = left_branch;
    this->op = op;
    this->right_branch = right_branch;
}

// Direct Literal
DirectLiteral::DirectLiteral(int prefix, Type type, string value) : type(type) {
    this->prefix = prefix;
    this->type = type;
    this->value = value;
}

