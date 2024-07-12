#pragma once
#include "../instruction.hpp"
#include "../vm.hpp"

class HaltInstruction: public Instruction
{

public:
    static constexpr auto definition = InstructionDefinition("halt");
    explicit HaltInstruction(Argument arguments[3]): Instruction(definition, arguments) {
    }

    void execute(Vm* machine) override {
        machine->flags |= 0x1;
    };
};
