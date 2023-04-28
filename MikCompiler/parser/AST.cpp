#include <AST.hpp>
#include <utils.hpp>

// Type
Type::Type(int _base_type, string _custom_type, int _dimensions) {
    this->base_type = _base_type;
    this->custom_type = _custom_type;
    this->dimensions = _dimensions;
}

// VariableAssignment
VariableAssignment::VariableAssignment() : type(Type(TYPE_INVALID, "", 0)) {
    this->is_declared = false;
    this->is_bounded  = false;
}

// AST
AST::AST(vector<FirstClass> _nodes) {
    this->type = NT_AST;
    this->nodes = _nodes;
}

// Function
Function::Function(bool _declared, string _function_name, pair<vector<VariableAssignment>, vector<Type> > _arguments
                , Type _return_type, AST _body, vector<int> _behavioural_descriptors
                , map<string, VariableAssignment> _internaly_known_variables, map<string, Function> _internaly_known_functions
                , map<string, Struct> _internaly_known_structs) : return_type(_return_type), body(_body.nodes)  {
    this->declared                  = _declared;
    this->function_name             = _function_name;
    this->arguments                 = _arguments;
    this->return_type               = _return_type;
    this->body                      = _body;
    this->behavioural_descriptors   = _behavioural_descriptors;
    this->internaly_known_variables = _internaly_known_variables;
    this->internaly_known_functions = _internaly_known_functions;
    this->internaly_known_structs   = _internaly_known_structs;
}

Function::Function() : return_type(-1, "", 0), body(vector<FirstClass>()) {}
