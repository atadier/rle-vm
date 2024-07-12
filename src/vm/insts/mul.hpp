#pragma once
#include "../instruction.hpp"

class MulInstruction: public Instruction
{

public:
    static constexpr auto definition = InstructionDefinition("mul");
    explicit MulInstruction(Argument arguments[3]): Instruction(definition, arguments) {

    }

    void execute(Vm* machine) override {
        const int v2 = machine->pop();
        const int v1 = machine->pop();
        machine->push(v1 * v2);
        machine->pc++;
    };
};
