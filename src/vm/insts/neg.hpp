#pragma once
#include "../instruction.hpp"

class NegInstruction: public Instruction
{

public:
    static constexpr auto definition = InstructionDefinition("neg");
    explicit NegInstruction(Argument arguments[3]): Instruction(definition, arguments) {

    }

    void execute(Vm* machine) override {
        const int val = machine->pop();
        machine->push(-val);
        machine->pc++;
    };
};
