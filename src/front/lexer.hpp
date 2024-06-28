#pragma once
#include <utility>

#include "token.hpp"
#include "module.hpp"

using namespace std;

class Lexer {
private:
    Tokenizer _tokens;

    Instruction* parse_toplevel(const string* label = nullptr);
    Instruction* parse_arguments(const string& mnemonic, size_t lineno);

public:
    explicit Lexer(Tokenizer  tokens) : _tokens(std::move(tokens)) {};

    Module* build_module();
};
