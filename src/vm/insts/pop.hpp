#pragma once

#include <format>

#include "../instruction.hpp"

class PopInstruction: public Instruction
{
public:
    static constexpr auto definition = InstructionDefinition("pop");
    explicit PopInstruction(Argument arguments[3]): Instruction(definition, arguments) {

    }

    void execute(Vm* machine) override {
        machine->pop();
        machine->pc++;
    };
};
