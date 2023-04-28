#include <experimental/bits/fs_fwd.h>
#include <utils.hpp>
#include <preprocessor.hpp>
#include <lexer.hpp>
#include <parser.hpp>

int main(void) {
    init_utils();

    string text = "int i = 10 int x = i+5";
    AST result(vector<FirstClass>(0));

    Preprocessor preprocessor(text, "./main.mik");
    Lexer lexer(text);
    auto a = lexer.lex();
    Parser parser(a.first, a.second, text, result);
}
