// nob.cpp
#define NOB_IMPLEMENTATION
#include "nob.h"

#define CC "clang++"
#define COMPILE_FLAGS   "-Iinclude",\
                        "-Wall",\
                        "-Wextra",\
                        "-Ipreprocessor/include",\
                        "-Ilexer/include",\
                        "-Ierrors/include",\
                        "-Iparser/include",\
                        "-Iutils/include",\
                        "-std=c++17"

#define OBJS_UTILS          "./build/utils.o",\
                            "./build/debug.o"
#define OBJS_PREPROCESSOR   "./build/preprocessor.o"
#define OBJS_LEXER          "./build/lexer.o"
#define OBJS_ERROR          "./build/errors.o"
#define OBJS_PARSER         "./build/AST.o",\
                            "./build/parser.o",\
                            "./build/second_class_parser.o",\
                            "./build/variable_reassignment.o",\
                            "./build/variable_assignment_parser.o"
#define OBJS                OBJS_UTILS,\
                            OBJS_PREPROCESSOR,\
                            OBJS_LEXER, OBJS_ERROR,\
                            OBJS_PARSER,\
                            "./build/main.o"

#define DEBUG "" // set to "-D DEBUG" for debugging

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    Nob_Cmd utils_utils_cmd = {0};
    Nob_Cmd utils_debug_cmd = {0};
    // compile each file
    // #UTILS#
    nob_cmd_append(&utils_utils_cmd, CC, DEBUG, COMPILE_FLAGS, "-c", "./utils/utils.cpp", "-o", "./build/utils.o");
    nob_cmd_append(&utils_debug_cmd, CC, DEBUG, COMPILE_FLAGS, "-c", "./utils/debug.cpp", "-o", "./build/debug.o");

    Nob_Cmd preprocessor_preprocessor_cmd = {0};
    // #PREPROCESSOR#
    nob_cmd_append(&preprocessor_preprocessor_cmd, CC, DEBUG, COMPILE_FLAGS, "-c", "./preprocessor/preprocessor.cpp", "-o", "./build/preprocessor.o");

    Nob_Cmd lexer_lexer_cmd = {0};
    // #LEXER# 
    nob_cmd_append(&lexer_lexer_cmd, CC, DEBUG, COMPILE_FLAGS, "-c", "./lexer/lexer.cpp", "-o", "./build/lexer.o");

    Nob_Cmd error_error_cmd = {0};
    // #ERROR# 
    nob_cmd_append(&error_error_cmd, CC, DEBUG, COMPILE_FLAGS, "-c", "./errors/errors.cpp", "-o", "./build/errors.o");

    Nob_Cmd parser_AST_cmd = {0};
    Nob_Cmd parser_parser_cmd = {0};
    Nob_Cmd parser_second_class_parser_cmd = {0};
    Nob_Cmd parser_variable_assignment_cmd = {0};
    Nob_Cmd parser_variable_reassignment_cmd = {0};
    // #PARSER# 
    nob_cmd_append(&parser_AST_cmd, CC, DEBUG, COMPILE_FLAGS, "-c", "./parser/AST.cpp", "-o", "./build/AST.o");
    nob_cmd_append(&parser_parser_cmd, CC, DEBUG, COMPILE_FLAGS, "-c", "./parser/parser.cpp", "-o", "./build/parser.o");
    nob_cmd_append(&parser_second_class_parser_cmd, CC, DEBUG, COMPILE_FLAGS, "-c", "./parser/second_class_parser.cpp", "-o", "./build/second_class_parser.o");
    nob_cmd_append(&parser_variable_assignment_cmd, CC, DEBUG, COMPILE_FLAGS, "-c", "./parser/variable_assignment_parser.cpp", "-o", "./build/variable_assignment_parser.o");
    nob_cmd_append(&parser_variable_reassignment_cmd, CC, DEBUG, COMPILE_FLAGS, "-c", "./parser/variable_reassignment.cpp", "-o", "./build/variable_reassignment.o");

    Nob_Cmd main_cmd = {0};
    // #MAIN# 
    nob_cmd_append(&main_cmd, CC, DEBUG, COMPILE_FLAGS, "-c", "./main.cpp", "-o", "./build/main.o");

    Nob_Cmd final_cmd = {0};
    // final command
    nob_cmd_append(&final_cmd, CC, DEBUG, COMPILE_FLAGS, OBJS, "-o", "mic");

    // exec
    nob_cmd_run_sync(utils_utils_cmd);
    nob_cmd_run_sync(utils_debug_cmd);
    nob_cmd_run_sync(preprocessor_preprocessor_cmd);
    nob_cmd_run_sync(lexer_lexer_cmd);
    nob_cmd_run_sync(error_error_cmd);
    nob_cmd_run_sync(parser_AST_cmd);
    nob_cmd_run_sync(parser_parser_cmd);
    nob_cmd_run_sync(parser_second_class_parser_cmd);
    nob_cmd_run_sync(parser_variable_assignment_cmd);
    nob_cmd_run_sync(parser_variable_reassignment_cmd);
    nob_cmd_run_sync(main_cmd);
    nob_cmd_run_sync(final_cmd);

    return 0;
}
