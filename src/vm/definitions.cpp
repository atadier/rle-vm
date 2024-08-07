#include "definitions.hpp"
#include "vm.hpp"
#include "insts/add.hpp"
#include "insts/halt.hpp"
#include "insts/jump.hpp"
#include "insts/jumpz.hpp"
#include "insts/load.hpp"
#include "insts/loadc.hpp"
#include "insts/leq.hpp"
#include "insts/mul.hpp"
#include "insts/neg.hpp"
#include "insts/pop.hpp"
#include "insts/store.hpp"

Instruction* init_instruction_am(const string& mnemonic, Argument arguments[3]) {
    if (mnemonic == "add") return new AddInstruction(arguments);
    if (mnemonic == "halt") return new HaltInstruction(arguments);
    if (mnemonic == "jump") return new JumpInstruction(arguments);
    if (mnemonic == "jumpz") return new JumpzInstruction(arguments);
    if (mnemonic == "load") return new LoadInstruction(arguments);
    if (mnemonic == "loadc") return new LoadcInstruction(arguments);
    if (mnemonic == "leq") return new LeqInstruction(arguments);
    if (mnemonic == "mul") return new MulInstruction(arguments);
    return nullptr;
}

Instruction* init_instruction_nz(const string& mnemonic, Argument arguments[3]) {
    if (mnemonic == "neg") return new NegInstruction(arguments);
    if (mnemonic == "pop") return new PopInstruction(arguments);
    if (mnemonic == "store") return new StoreInstruction(arguments);
    return nullptr;
}

Instruction* init_instruction(const string& mnemonic, Argument arguments[3]) {
    if (mnemonic.at(0) < 0x6E) return init_instruction_am(mnemonic, arguments);
    return init_instruction_nz(mnemonic, arguments);
}

InstructionDefinition get_definition_am(const string& mnemonic) {
    if (mnemonic == "add") return AddInstruction::definition;
    if (mnemonic == "halt") return HaltInstruction::definition;
    if (mnemonic == "jump") return JumpInstruction::definition;
    if (mnemonic == "jumpz") return JumpzInstruction::definition;
    if (mnemonic == "load") return LoadInstruction::definition;
    if (mnemonic == "loadc") return LoadcInstruction::definition;
    if (mnemonic == "leq") return LeqInstruction::definition;
    if (mnemonic == "mul") return MulInstruction::definition;
    return InstructionDefinition("");
}

InstructionDefinition get_definition_nz(const string& mnemonic) {
    if (mnemonic == "neg") return NegInstruction::definition;
    if (mnemonic == "pop") return PopInstruction::definition;
    if (mnemonic == "store") return StoreInstruction::definition;
    return InstructionDefinition("");
}

InstructionDefinition get_definition(const string& mnemonic) {
    if (mnemonic.at(0) < 0x6E) return get_definition_am(mnemonic);
    return get_definition_nz(mnemonic);
}
