#pragma once
#include <stdexcept>
#include <string>
#include <utility>

#include "argument.hpp"

using namespace std;


struct InstructionDefinition
{
    string mnemonic;
    ArgumentType arg1Type = None;
    ArgumentType arg2Type = None;
    ArgumentType arg3Type = None;

    explicit constexpr InstructionDefinition(string mnemonic) : mnemonic(move(mnemonic)) {};
    constexpr InstructionDefinition(string mnemonic, const ArgumentType arg1): InstructionDefinition(move(mnemonic)) {
        arg1Type = arg1;
    };
    constexpr InstructionDefinition(string mnemonic, const ArgumentType arg1, const ArgumentType arg2): InstructionDefinition(move(mnemonic), arg1) {
        arg2Type = arg2;
    };
    constexpr InstructionDefinition(string mnemonic, const ArgumentType arg1, const ArgumentType arg2, const ArgumentType arg3): InstructionDefinition(move(mnemonic), arg1, arg2) {
        arg3Type = arg3;
    };

    [[nodiscard]] ArgumentType get_argument_type(const size_t index) const {
        if (index == 0) return arg1Type;
        if (index == 1) return arg2Type;
        if (index == 2) return arg3Type;
        throw runtime_error("get_argument_type called with invalid index " + index);
    }
};

class Instruction {
protected:
    explicit Instruction(InstructionDefinition definition, Argument arguments[3]): definition(move(definition)), arg1(arguments[0]), arg2(arguments[1]), arg3(arguments[2]) {};

public:
    const InstructionDefinition definition;
    Argument arg1;
    Argument arg2;
    Argument arg3;
    virtual void execute() { throw runtime_error("instruction not implemented!"); }
    virtual ~Instruction() = default;
};
