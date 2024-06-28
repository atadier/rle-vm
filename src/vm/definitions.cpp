#include "definitions.hpp"
#include "insts/add.hpp"

Instruction* init_instruction_am(const string& mnemonic, Argument arguments[3]) {
    if (mnemonic == "add") {
        return new AddInstruction(arguments);
    }
    return nullptr;
}

Instruction* init_instruction_nz(const string& mnemonic, Argument arguments[3]) {
    return nullptr;
}

Instruction* init_instruction(const string& mnemonic, Argument arguments[3]) {
    if (mnemonic.at(0) < 0x6E) return init_instruction_am(mnemonic, arguments);
    return init_instruction_nz(mnemonic, arguments);
}

InstructionDefinition get_definition_am(const string& mnemonic) {
    if (mnemonic == "add") {
        return AddInstruction::definition;
    }
    return InstructionDefinition("");
}

InstructionDefinition get_definition_nz(const string& mnemonic) {
    return InstructionDefinition("");
}

InstructionDefinition get_definition(const string& mnemonic) {
    if (mnemonic.at(0) < 0x6E) return get_definition_am(mnemonic);
    return get_definition_nz(mnemonic);
}