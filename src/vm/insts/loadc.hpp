#pragma once

#include "../instruction.hpp"

class LoadcInstruction: public Instruction
{
    int qValue;

public:
    static constexpr auto definition = InstructionDefinition("loadc", Number);
    explicit LoadcInstruction(Argument arguments[3]): Instruction(definition, arguments) {
        qValue = arguments[0].get_numeric();
    }

    void execute(Vm* machine) override {
        machine->push(qValue);
        machine->pc++;
    };
};
