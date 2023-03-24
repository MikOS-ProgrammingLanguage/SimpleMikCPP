#include <map>
#ifndef MIK_AST_H

#include <iostream>
#include <vector>

using namespace std;

// Types of all different nodes to identify them
enum {
    NT_AST,
};

/* OTHER */
class Type {
    public:
        int base_type; // built-in types
        string CustomType; // like structs, etc...
};

// First class object interface
class FirstClass {
    public:
        int type;
};

// Second class object interface
class SecondClass {
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
class Assignment : public FirstClass {
};

// function like: mikf f(int x) -> int {return x*x}
class Function : public FirstClass {
    public:
        bool declared;
        string function_name;
        pair<vector<Assignment>, vector<Type> > arguments; // arguments to the function represented by the code snippet defining it and it's type respectively
        Type return_type;
        AST body;
        vector<int> behavioural_descriptors;
        map<string, Assignment> internaly_known_variables;
        map<string, Function> internaly_known_functions;
        map<string, Struct> internaly_known_structs;

        // construct all at once
        Function(bool _declared, string _function_name, pair<vector<Assignment>, vector<Type> > _arguments
                , Type _return_type, AST _body, vector<int> _behavioural_descriptors
                , map<string, Assignment> _internaly_known_variables, map<string, Function> _internaly_known_functions
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
