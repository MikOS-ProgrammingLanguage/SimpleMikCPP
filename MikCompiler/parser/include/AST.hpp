#include <map>
#ifndef MIK_AST_H

#include <iostream>
#include <vector>

using namespace std;

// Types of all different nodes to identify them
enum {
    NT_AST,
};

// First class object interface
class FirstClass {
    public:
        int type;
};

// Second class object interface
class SecondClass {
};

/* OTHER */
class Type {
    public:
        Type(int _base_type, string _cutsom_type, int _dimensions);
        int base_type; // built-in types
        int dimensions; // dimensions for arrays (0 is for no arrays)
        string custom_type; // like structs, etc...
};

class Boundary : public SecondClass {
    public:
        bool option;
        SecondClass lower_bound;
        SecondClass upper_bound;
};

/* FIRST CLASS */
// General AST
class AST : public FirstClass {
    public:
        bool ast;
        AST(vector<FirstClass> _nodes);
        vector<FirstClass> nodes;
};

// Struct
class Struct : public FirstClass {
};

// If statement
class If : public FirstClass {
};

// while statement
class While : public FirstClass {
};

// return statement
class Return : public FirstClass {
};

// re-assignment of a variable or in general variable alteration
class VariableAlteration : public FirstClass {
};

// Assignment (Here the same node as for array assignments)
class VariableAssignment : public FirstClass {
    public:
        VariableAssignment();

        bool is_declared;
        bool is_bounded;

        string name;
        Type type;
        SecondClass assigned_expression;
        vector<SecondClass> array_length_expressions;
        Boundary bound;
};

// function like: mikf f(int x) -> int {return x*x}
class Function : public FirstClass {
    public:
        bool declared;
        string function_name;
        pair<vector<VariableAssignment>, vector<Type> > arguments; // arguments to the function represented by the code snippet defining it and it's type respectively
        Type return_type;
        AST body;
        vector<int> behavioural_descriptors;
        map<string, VariableAssignment> internaly_known_variables;
        map<string, Function> internaly_known_functions;
        map<string, Struct> internaly_known_structs;

        // construct all at once
        Function(bool _declared, string _function_name, pair<vector<VariableAssignment>, vector<Type> > _arguments
                , Type _return_type, AST _body, vector<int> _behavioural_descriptors
                , map<string, VariableAssignment> _internaly_known_variables, map<string, Function> _internaly_known_functions
                , map<string, Struct> _internaly_known_structs);
        Function(); // construct later on
};

// first class function call like: kill()
class FirstClassFunctionCall : public FirstClass {
};


/* SECOND CLASS */
// Binary operation like x + y
class BinaryOperation : public SecondClass {
};

// Mathematical factor, like x, y, 5, i, etc...
class MathematicalFactor : public SecondClass {
};

// Direct literal like 5, 'A'. Not like x, y, z
class DirectLiteral : public SecondClass {
};

// use variable
class UseVariable : public SecondClass {
};

// Typecast like: int(0.5)
class TypeCast : public SecondClass {
};


#endif // MIK_AST_H
#define MIK_AST_H
