#ifndef MIK_UTILS_H

#include <vector>
#include <iostream>
#include <map>

using namespace std;

extern vector<string> type_names;
extern vector<string> struct_types;
extern map<string, int> token_value_to_type;

// Type constants
enum types {
    TYPE_INVALID,
    TYPE_INT,
    TYPE_STRING,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_BOOL,
    TYPE_VOID
};

// Behavioural descriptor constants
enum behavioural_descriptors {
    DESCRIPTOR_NORET,
};

void init_utils();

#endif // MIK_UTILS_H
