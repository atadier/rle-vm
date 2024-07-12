#pragma once

#include <format>

#include "../instruction.hpp"

class LoadInstruction: public Instruction
{
public:
    static constexpr auto definition = InstructionDefinition("load");
    explicit LoadInstruction(Argument arguments[3]): Instruction(definition, arguments) {

    }

    void execute(Vm* machine) override {
        const int ptr = machine->pop();
        if (ptr <= 0 || ptr >= VM_STACK_SIZE)
            throw runtime_error(std::format("trap: attempted to load stack value {}", ptr));
        machine->push(machine->stack[ptr]);
        machine->pc++;
    };
};
