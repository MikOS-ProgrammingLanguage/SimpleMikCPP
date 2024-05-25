#include <experimental/bits/fs_fwd.h>
#include <string>
#include <utils.hpp>
#include <preprocessor.hpp>
#include <lexer.hpp>
#include <parser.hpp>

int main(int argc, char** argv) {
    if (argc == 0) {
        cout << "Usage:" << endl;
    }
    string filepath = argv[1];
    ifstream file(filepath);


    string file_contents = "";
    if (file) {
        for (string line = ""; getline(file, line);)
            file_contents += line;
    } else {
        cout << "file does not exist" << endl;
    }

    init_utils();

    string text = "int i = (0.5) -> int";
    //file_contents = text;
    AST result(vector<FirstClass>(0));

    Preprocessor preprocessor(file_contents, filepath);
    Lexer lexer(file_contents);
    auto a = lexer.lex();
    for (auto i : a.first) {
        cout << i.value << endl;
    }
    Parser parser(a.first, a.second, text, result);
}
