#include <experimental/bits/fs_fwd.h>
#include <preprocessor.hpp>
#include <lexer.hpp>
#include <parser.hpp>

int main(void) {
    string text = "0 123456 0.5 9.5 0b111 0xFF 0b1F011\n\"Hello world!\"@file(\"hello.mik\")\n 'ab'\n@fend";
    Preprocessor p(text, "./main.mik");
    Lexer l(text);
    vector<Token> t = l.lex();

}
