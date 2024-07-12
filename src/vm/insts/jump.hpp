#pragma once

#include <format>

#include "../instruction.hpp"

class JumpInstruction: public Instruction
{
    int address;

public:
    static constexpr auto definition = InstructionDefinition("jump", Number);
    explicit JumpInstruction(Argument arguments[3]): Instruction(definition, arguments) {
        address = arguments[0].get_numeric();
    }

    void execute(Vm* machine) override {
        if (address < 0 || address >= machine->module->instructions.size())
            throw runtime_error(std::format("trap: invalid jump address: ", address));
        machine->pc = address;
    };
};
