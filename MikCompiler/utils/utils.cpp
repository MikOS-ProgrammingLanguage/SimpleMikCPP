#include <utils.hpp>

vector<string> type_names;
vector<string> struct_types;
map<string, int> token_value_to_type;

void init_utils() {
    type_names = vector<string>{
        "int",
        "flt",
        "str",
        "chr",
        "bool",
        "void"
    };
    
    struct_types = vector<string>(0);

    token_value_to_type["int"] = TYPE_INT;
    token_value_to_type["flt"] = TYPE_FLOAT;
    token_value_to_type["str"] = TYPE_STRING;
    token_value_to_type["chr"] = TYPE_STRING;
    token_value_to_type["bool"] = TYPE_BOOL;
    token_value_to_type["void"] = TYPE_VOID;
}
