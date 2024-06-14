#pragma once
#include "token.hpp"

class Lexer {
private:
    Tokenizer _tokens;

public:
    Lexer(Tokenizer tokens) : _tokens(tokens) {};

    void build_module();
};
