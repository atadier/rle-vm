#include <iostream>
#include <fstream>
#include <cstring>
#include <format>
#include <regex>

#include "argh.h"
#include "token.hpp"

using namespace std;

string display_token(string value) {
    return regex_replace(value, regex("\n"), "\\n");
}

void dump_tokenizer(Tokenizer tokens) {
    map<TokenType, std::string> tokenNames = {
        {TokenType::IDENTIFIER, "Identifier"},
        {TokenType::NUMERIC, "Numeric"},
        {TokenType::NEWLINE, "Newline"},
        {TokenType::HASH, "Hash"},
        {TokenType::COMMA, "Comma"},
        {TokenType::COLON, "Colon"},
        {TokenType::UNKNOWN, "Unknown"}
    };

    cout << "\033[90m[line: col] Token\033[0m" << endl;
    while (Token* tok = tokens.next()) {
        string posFormat = format("[\033[93m{:4d}\033[0m:\033[93m{:4d}\033[0m] ", tok->span.start.line, tok->span.start.column);
        cout << posFormat << tokenNames[tok->type] << ": \033[36m" << display_token(tok->value) << "\033[0m" << endl;
    }
}

int run(string input_filename) {
    ifstream in(input_filename);

    if (errno) {
        cerr << "could not open file '" << input_filename << "': " << strerror(errno);
        return 1;
    }

    Tokenizer tokenizer(&in);
    dump_tokenizer(tokenizer);
    return 0;
}

int show_help(string program_name) {
   cout << "tokenizer: Debugging tools for rle-vm" << endl;
   cout << "\nUsage: " << program_name << " <file>" << endl;
   cout << "\nOptions:" << endl;
   cout << "\t-h, --help        Show this help message" << endl;
   return 0;
}

int main(int argc, char** argv) {
    argh::parser args(argc, argv);

    if (args[{ "-h", "--help" }])
        return show_help(args[0]);

    string filename = args[1];
    if (filename == "") {
        cerr << "error: no input file provided" << endl;
        cerr << "use --help option for program help" << endl;
        return 1;
    }

    return run(filename);
}
