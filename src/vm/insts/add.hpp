#pragma once
#include "../instruction.hpp"

class AddInstruction: public Instruction
{
public:
    static constexpr auto definition = InstructionDefinition("add", Register, Number);
    explicit AddInstruction(Argument arguments[3]): Instruction(definition, arguments) {

    }

    void execute() override;
};
