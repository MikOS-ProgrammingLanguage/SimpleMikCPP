#include <utils.hpp>
#include <vector>

vector<string> keywords;
vector<string> type_names;
vector<string> struct_types;
map<string, int> token_value_to_type_enum;
map<int, string> enum_type_to_token_value;
map<string, Type> token_value_to_type;
map<pair<Type, Type>, SecondClassFunctionCall> typecast_functions;

void init_utils() {
    keywords =
        vector<string>{"int",      "flt", "str",       "chr",    "bool", "void",
                       "fnc",      "if",  "else",      "while",  "keep", "roll",
                       "typecast", "of",  "__noret__", "global", "guard"};
    type_names = vector<string>{"int", "flt", "str", "chr", "bool", "void"};

    struct_types = vector<string>(0);

    token_value_to_type_enum["int"] = TYPE_INT;
    token_value_to_type_enum["flt"] = TYPE_FLOAT;
    token_value_to_type_enum["str"] = TYPE_STRING;
    token_value_to_type_enum["chr"] = TYPE_CHAR;
    token_value_to_type_enum["bool"] = TYPE_BOOL;
    token_value_to_type_enum["void"] = TYPE_VOID;

    enum_type_to_token_value[TYPE_INT] = "int";
    enum_type_to_token_value[TYPE_FLOAT] = "flt";
    enum_type_to_token_value[TYPE_STRING] = "str";
    enum_type_to_token_value[TYPE_CHAR] = "chr";
    enum_type_to_token_value[TYPE_BOOL] = "bool";
    enum_type_to_token_value[TYPE_VOID] = "void";

    token_value_to_type["int"] = BASE_TYPE_INT(1);
    token_value_to_type["flt"] = BASE_TYPE_FLOAT(1);
    token_value_to_type["str"] = BASE_TYPE_STRING(1);
    token_value_to_type["chr"] = BASE_TYPE_CHAR(1);
    token_value_to_type["bool"] = BASE_TYPE_BOOL(1);
    token_value_to_type["void"] = BASE_TYPE_VOID(1);
}
