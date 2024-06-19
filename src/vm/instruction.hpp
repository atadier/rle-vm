#pragma once
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

struct Instruction {
    string mnemonic;

    explicit Instruction(string mnemonic) : mnemonic(move(mnemonic)) {};
    virtual void execute() { throw runtime_error("instruction not implemented!"); }
    virtual ~Instruction() = default;
};
