#ifndef MIK_PREPROCESSOR_H
#define MIK_PREPROCESSOR_H

#include <fstream>
#include <regex>
#include <string>
#include <experimental/filesystem>

using namespace std;
namespace fs = experimental::filesystem;

const static regex valid_local_include_regexp("^(#yoink){1}( )*(<){1}(.)+(>){1}$");
const static regex valid_pkg_include_regex("^(#yoink-pkg){1}( )*(<){1}(.)+(>){1}$");

class Preprocessor {
    public:
        Preprocessor(string &_source_file, fs::path source_path);

    private:
        string result;
        vector<string> included_file_paths;
        vector<string> included_pkgs;

        void preprocess(string file_contents, fs::path file_path);
};

#endif // MIK_PREPROCESSOR_H

