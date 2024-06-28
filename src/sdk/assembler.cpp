#include <iostream>
#include <fstream>
#include <cstring>
#include <format>
#include <regex>

#include "argh.h"
#include "token.hpp"
#include "lexer.hpp"
#include "../vm/module.hpp"

using namespace std;

void display_module(const Module& mod) {
    cout << "Module" << endl;
    cout << "instructions:" << endl;
    for (const Instruction& instruction : mod._instructions) {
        cout << "\t" << instruction.definition.mnemonic;

        if (instruction.arg1.type != None)
            cout << " " << instruction.arg1.display_value();
        if (instruction.arg2.type != None)
            cout << ", " << instruction.arg2.display_value();
        if (instruction.arg3.type != None)
            cout << ", " << instruction.arg3.display_value();
        cout << endl;
    }
}

int run(const string& input_filename) {
    ifstream in(input_filename);

    if (errno) {
        cerr << "could not open file '" << input_filename << "': " << strerror(errno);
        return 1;
    }

    Tokenizer tokenizer(&in);
    Lexer lexer(tokenizer);
    Module module = *lexer.build_module();
    display_module(module);
    return 0;
}

int show_help(const string& program_name) {
   cout << "assembler: Generate AST from given program sources" << endl;
   cout << "\nUsage: " << program_name << " <file>" << endl;
   cout << "\nOptions:" << endl;
   cout << "\t-h, --help        Show this help message" << endl;
   return 0;
}

int main(int argc, char** argv) {
    argh::parser args(argc, argv);

    if (args[{ "-h", "--help" }])
        return show_help(args[0]);

    const string& filename = args[1];
    if (filename.empty()) {
        cerr << "error: no input file provided" << endl;
        cerr << "use --help option for program help" << endl;
        return 1;
    }

    return run(filename);
}
