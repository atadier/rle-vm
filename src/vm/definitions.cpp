#include "definitions.hpp"
#include "insts/halt.hpp"
#include "insts/loadc.hpp"
#include "insts/leq.hpp"
#include "insts/mul.hpp"

Instruction* init_instruction_am(const string& mnemonic, Argument arguments[3]) {
    if (mnemonic == "halt") return new HaltInstruction(arguments);
    if (mnemonic == "loadc") return new LoadcInstruction(arguments);
    if (mnemonic == "leq") return new LeqInstruction(arguments);
    if (mnemonic == "mul") return new MulInstruction(arguments);
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
    if (mnemonic == "halt") return HaltInstruction::definition;
    if (mnemonic == "loadc") return LoadcInstruction::definition;
    if (mnemonic == "leq") return LeqInstruction::definition;
    if (mnemonic == "mul") return MulInstruction::definition;
    return InstructionDefinition("");
}

InstructionDefinition get_definition_nz(const string& mnemonic) {
    return InstructionDefinition("");
}

InstructionDefinition get_definition(const string& mnemonic) {
    if (mnemonic.at(0) < 0x6E) return get_definition_am(mnemonic);
    return get_definition_nz(mnemonic);
}
