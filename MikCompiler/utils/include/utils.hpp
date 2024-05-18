#ifndef MIK_UTILS_H

#include <vector>
#include <iostream>
#include <map>
#include "AST.hpp"

#define MTRX(a, b) (pair<int, int>(a, b))

using namespace std;

extern vector<string> type_names;
extern vector<string> struct_types;
extern map<string, int> token_value_to_type;
extern map<int, string> type_to_token_value;

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
#define BASE_TYPE_INVALID(a, b) (Type(TYPE_INVALID, "", MTRX(a,b)))
#define BASE_TYPE_STRING(a, b) Type(TYPE_STRING, "", MTRX(a,b))
#define BASE_TYPE_FLOAT(a, b)Type(TYPE_FLOAT, "", MTRX(a,b))
#define BASE_TYPE_INT(a, b) Type(TYPE_INT, "", MTRX(a,b))
#define BASE_TYPE_CHAR(a, b) Type(TYPE_CHAR, "", MTRX(a,b))
#define BASE_TYPE_BOOL(a, b) Type(TYPE_BOOL, "", MTRX(a,b))
#define BASE_TYPE_VOID(a, b) Type(TYPE_VOID, "", MTRX(a,b))

void init_utils();
#endif // MIK_UTILS_H
