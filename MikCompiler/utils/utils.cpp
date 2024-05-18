#include <utils.hpp>

vector<string> type_names;
vector<string> struct_types;
map<string, int> token_value_to_type;
map<int, string> type_to_token_value;

void init_utils() {
    type_names = vector<string>{"int", "flt", "str", "chr", "bool", "void"};

    struct_types = vector<string>(0);

    token_value_to_type["int"] = TYPE_INT;
    token_value_to_type["flt"] = TYPE_FLOAT;
    token_value_to_type["str"] = TYPE_STRING;
    token_value_to_type["chr"] = TYPE_CHAR;
    token_value_to_type["bool"] = TYPE_BOOL;
    token_value_to_type["void"] = TYPE_VOID;

    type_to_token_value[TYPE_INT] = "int";
    type_to_token_value[TYPE_FLOAT] = "flt";
    type_to_token_value[TYPE_STRING] = "str";
    type_to_token_value[TYPE_CHAR] = "chr";
    type_to_token_value[TYPE_BOOL] = "bool";
    type_to_token_value[TYPE_VOID] = "void";
}

