#pragma once
#include "token.hpp"
#include "module.hpp"

using namespace std;

class Lexer {
private:
    Tokenizer _tokens;

    Instruction* parse_toplevel(const string* label = nullptr);
    Instruction* parse_arguments(const string& mnemonic);

public:
    Lexer(const Tokenizer& tokens) : _tokens(tokens) {};

    Module* build_module();
};
