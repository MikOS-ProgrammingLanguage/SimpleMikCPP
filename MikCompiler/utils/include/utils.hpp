#ifndef MIK_UTILS_H

#include <vector>
#include <iostream>
#include <map>
#include "AST.hpp"

#define DIM(...) (vector<int>({__VA_ARGS__}))

using namespace std;

#define PREFIX_MINUS 1
#define PREFIX_NOT 2
#define PREFIX_BITWISE_NOT 3

extern vector<string> keywords;
extern vector<string> type_names;
extern vector<string> struct_types;
extern map<string, int> token_value_to_type_enum;
extern map<int, string> enum_type_to_token_value;
extern map<string, Type> token_value_to_type;
extern map<pair<Type, Type>, SecondClassFunctionCall> typecast_functions;

// Type constants (ordered s.t. if any types a and b, where a is the governing type fullfill b<=a, then b can be converted to a)
enum types {
    TYPE_INVALID,
    TYPE_STRING,
    TYPE_FLOAT,
    TYPE_INT,
    TYPE_CHAR,
    TYPE_BOOL,
    TYPE_VOID
};

// Behavioural descriptor constants
enum behavioural_descriptors {
    DESCRIPTOR_NORET,
};

// Base types as type
#define BASE_TYPE_INVALID(...) Type(TYPE_INVALID, "", DIM(__VA_ARGS__))
#define BASE_TYPE_STRING(...) Type(TYPE_STRING, "", DIM(__VA_ARGS__))
#define BASE_TYPE_FLOAT(...) Type(TYPE_FLOAT, "", DIM(__VA_ARGS__))
#define BASE_TYPE_INT(...) Type(TYPE_INT, "", DIM(__VA_ARGS__))
#define BASE_TYPE_CHAR(...) Type(TYPE_CHAR, "", DIM(__VA_ARGS__))
#define BASE_TYPE_BOOL(...) Type(TYPE_BOOL, "", DIM(__VA_ARGS__))
#define BASE_TYPE_VOID(...) Type(TYPE_VOID, "", DIM(__VA_ARGS__))

void init_utils();
#endif // MIK_UTILS_H
