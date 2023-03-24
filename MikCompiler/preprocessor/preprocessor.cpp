#include <iostream>
#include <errors.hpp>
#include <sstream>
#include <preprocessor.hpp>
#include <fstream>

Preprocessor::Preprocessor(string &_source_file, fs::path source_path) {
    preprocess(_source_file, source_path);
    _source_file = this->result;
}

/*
- append @file directive
- append path to included to prevent multiple includes
- change current working directory to the one of the current file
- search file for includes 
- preprocess those includes as well
*/
void Preprocessor::preprocess(string file_contents, fs::path file_path) {
    int ln_number = 0;
    string org_path = file_path.string();
    this->result += "@file(\"" + file_path.string() + "\")";
    file_path = fs::absolute(file_path);

    // if the specified path is just a file name, prepend "./"
    if (std::count(file_path.string().begin(), file_path.string().end(), '/') == 0) {
        file_path = fs::path("./" + file_path.string());
    }

    // remove file name from file path
    file_path = file_path.string().substr(0, file_path.string().find_last_of('/'));
    this->included_file_paths.push_back(fs::absolute(file_path));
    fs::current_path(file_path); // set cwd

    // iterate over each line in the file
    istringstream contents;
    contents.str(file_contents);
    for (string line; getline(contents, line);) {
        ln_number++;

        if (regex_match(line, valid_local_include_regexp)) {
            // get file name and check wether it exists, then call preprocess 
            int idx = 0;
            for (; line[idx] != '<'; idx++);

            string f_name = "";
            for (idx++; line[idx] != '>'; idx++) f_name += line[idx];

            fs::path f_path(f_name);

            ifstream file(f_name);
            if (file) {
                // exists
                string file_contents = "";
                for (string line = ""; getline(file, line);) file_contents += line;

                this->preprocess(file_contents, f_path);
            } else {
                throw_error(ERROR_OPENING_YOINKED_FILE, line, ln_number, org_path);
            }
        } else if (regex_match(line, valid_pkg_include_regex)) {
            cout << "not implemented" << endl;
        } else {
            this->result += line + "\n";
        }
    }

    this->result += "@fend";
}
