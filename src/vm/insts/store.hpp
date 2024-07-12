#pragma once

#include <format>

#include "../instruction.hpp"

class StoreInstruction: public Instruction
{
public:
    static constexpr auto definition = InstructionDefinition("store");
    explicit StoreInstruction(Argument arguments[3]): Instruction(definition, arguments) {

    }

    void execute(Vm* machine) override {
        const int ptr = machine->pop();
        if (ptr <= 0 || ptr >= VM_STACK_SIZE)
            throw runtime_error(std::format("trap: attempted to store to stack value {}", ptr));
        machine->stack[ptr] = machine->peek();
        machine->pc++;
    };
};
